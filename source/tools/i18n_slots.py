#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-only
"""Find the first language's strings in BAILE's interface (KAWA's FR slot, BAILE's PT): every place that holds the
text of LANG 0, with the same text in LANG 1 (EN) and LANG 2 (ES) beside it.

  python3 tools/i18n_slots.py dump  > tools/i18n_pt.json      (the texts as the sources have them)
  python3 tools/i18n_slots.py apply tools/i18n_pt.json         (writes the "pt" texts into the slots)
  python3 tools/i18n_slots.py check tools/i18n_pt.json         (each "pt" within its "max", every slot accounted for)

A slot is known by file, EN, ES and its rank among those with the same three: not by its text (which is what one edits)
and not by the French it replaced (two French words alike are not one Portuguese word).

What it reads (kawa_data.c, kawa_ui.c, kawa_edit.c, kawa_kg.c):
  TR(fr, en, es) and PDN(fr, en, es)                       the first argument
  NAME[LANG_N]... = { {fr...}, {en...}, {es...} }          the first group (whatever it holds)
  NAME[3][...] = { ... } (FM_PATCH_NAME)                   the same
  { "fr", "en", "es" } elsewhere (a field name[LANG_N])    the first string
  L_XXX[] = { fr x n, en x n, es x n } (K_LIST values)     the first third
"""
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
FILES = [ROOT / "firmware" / "src" / f for f in ("kawa_data.c", "kawa_ui.c", "kawa_edit.c", "kawa_kg.c")]
STR = r'"(?:[^"\\]|\\.)*"'


def tokens(s):
    """string literals (with the adjacent-literal joins), braces, commas, parentheses; comments skipped"""
    out, i, n = [], 0, len(s)
    while i < n:
        c = s[i]
        if s.startswith("/*", i):
            i = s.index("*/", i) + 2
        elif s.startswith("//", i):
            i = s.index("\n", i)
        elif c == '"':
            m = re.compile(STR).match(s, i)
            out.append(("S", m.start(), m.end()))
            i = m.end()
        elif c == "'":
            m = re.compile(r"'(?:[^'\\]|\\.)*'").match(s, i)
            i = m.end()
        elif c in "{},()":
            out.append((c, i, i + 1))
            i += 1
        else:
            i += 1
    return out


def groups(toks, start):
    """from a '{' at toks[start]: the list of its top-level elements (each a list of tokens) and the index after it"""
    depth, el, els, i = 0, [], [], start
    while True:
        t = toks[i]
        if t[0] in "{(":
            depth += 1
            if depth > 1:
                el.append(t)
        elif t[0] in "})":
            depth -= 1
            if depth == 0:
                if el:
                    els.append(el)
                return els, i + 1
            el.append(t)
        elif t[0] == "," and depth == 1:
            els.append(el)
            el = []
        else:
            el.append(t)
        i += 1


def lit(s, t):
    return s[t[1] + 1:t[2] - 1]


def slots_of(path):
    s = path.read_text()
    toks = tokens(s)
    pos = {t[1]: k for k, t in enumerate(toks)}
    found, taken = [], set()

    def add(fr, en, es, kind):
        if fr[1] in taken:
            return
        taken.add(fr[1])
        found.append(dict(file=path.name, at=fr[1], end=fr[2], fr=lit(s, fr), en=lit(s, en) if en else None,
                          es=lit(s, es) if es else None, kind=kind))

    # LANG_N tables (and FM_PATCH_NAME[3][...]): the first top-level group is LANG 0
    for m in re.finditer(r"(\w+)\s*\[\s*(LANG_N|3)\s*\]\s*(?:\[[^\]]*\])?\s*=\s*\{", s):
        if m.group(2) == "3" and m.group(1) != "FM_PATCH_NAME":
            continue
        k = pos[m.end() - 1]
        els, _ = groups(toks, k)
        assert len(els) == 3, (path.name, m.group(0), len(els))
        a, b, c = ([t for t in e if t[0] == "S"] for e in els)
        assert len(a) == len(b) == len(c), (path.name, m.group(0), len(a), len(b), len(c))
        for x, y, z in zip(a, b, c):
            add(x, y, z, "table")
        for e in els[1:]:                       # LANG 1 and 2 are not slots: never seen as triples below
            for t in e:
                if t[0] == "S":
                    taken.add(t[1])
    # TR(...) and PDN(...)
    for m in re.finditer(r"\b(TR|PDN)\s*\(", s):
        if s[m.start() - 8:m.start()].endswith("define "):
            continue
        k = pos.get(m.end() - 1)
        if k is None:
            continue
        els, _ = groups(toks, k)
        ss = [[t for t in e if t[0] == "S"] for e in els]
        if len(els) == 3 and all(len(x) == 1 for x in ss):
            add(ss[0][0], ss[1][0], ss[2][0], m.group(1))
    # K_LIST value lists: L_XXX[] = { 3 x n }
    for m in re.finditer(r"\b(L_\w+)\s*\[\s*\]\s*=\s*\{", s):
        k = pos[m.end() - 1]
        els, _ = groups(toks, k)
        ss = [t for e in els for t in e if t[0] == "S"]
        if len(ss) % 3:
            continue
        n = len(ss) // 3
        a, b, c = ss[:n], ss[n:2 * n], ss[2 * n:]
        if [lit(s, t) for t in a] == [lit(s, t) for t in b] == [lit(s, t) for t in c]:
            continue                            # the same in every language (numbers, notes)
        for x, y, z in zip(a, b, c):
            add(x, y, z, "list:" + m.group(1))
        for t in b + c:
            taken.add(t[1])
    # { "fr", "en", "es" } anywhere else: a field name[LANG_N]
    for k, t in enumerate(toks):
        if t[0] != "{":
            continue
        els, _ = groups(toks, k)
        if re.search(r"\[\s*3\s*\]\s*=\s*$", s[max(0, t[1] - 40):t[1]]):
            continue                            # a plain array of three (ENC[3]), not three languages
        if len(els) == 3 and all(len(e) == 1 and e[0][0] == "S" for e in els) and els[0][0][1] not in taken \
                and els[1][0][1] not in taken:
            add(els[0][0], els[1][0], els[2][0], "triple")
    return s, found


def keyed():
    """every slot of every file, in the order of the sources, with the key that survives a translation"""
    out = []
    for path in FILES:
        s, found = slots_of(path)
        seen = {}
        for x in sorted(found, key=lambda x: x["at"]):
            k = (path.name, x["en"], x["es"])
            seen[k] = seen.get(k, 0) + 1
            out.append((k + (seen[k],), x))
    return out


def problems(slots, rows):
    bad = []
    have, want = {k for k, _ in slots}, set(rows)
    bad += [f"not in the JSON (dump again): {k}" for k in sorted(have - want, key=str)]
    bad += [f"not in the sources (dump again): {k}" for k in sorted(want - have, key=str)]
    for k, r in rows.items():
        pt = r["pt"]
        if len(pt) > r["max"]:
            bad.append(f"too long ({len(pt)} > {r['max']}): {k} -> {pt!r}")
        if not pt.isascii() or re.search(r'(?<!\\)"|\n', pt):
            bad.append(f"not a plain ASCII text: {k} -> {pt!r}")
    return bad


def main():
    cmd = sys.argv[1] if len(sys.argv) > 1 else ""
    slots = keyed()
    if cmd == "dump":
        out = [dict(file=k[0], en=k[1], es=k[2], nth=k[3], pt=x["fr"],
                    max=max(len(x["fr"]), len(x["en"] or ""), len(x["es"] or ""))) for k, x in slots]
        print("[\n" + ",\n".join(json.dumps(r, ensure_ascii=False) for r in out) + "\n]")
        print(f"{len(out)} slots", file=sys.stderr)
        return
    if cmd not in ("check", "apply") or len(sys.argv) != 3:
        sys.exit(__doc__)
    rows = {(r["file"], r["en"], r["es"], r["nth"]): r for r in json.loads(Path(sys.argv[2]).read_text())}
    bad = problems(slots, rows)
    if bad:
        print("\n".join(bad))
        sys.exit(f"{cmd}: {len(bad)} problems, nothing written")
    if cmd == "check":
        print("check: ok,", len(slots), "slots")
        return
    for path in FILES:
        s, n = path.read_text(), 0
        mine = [(k, x) for k, x in slots if k[0] == path.name]
        for k, x in sorted(mine, key=lambda e: -e[1]["at"]):
            if rows[k]["pt"] != x["fr"]:
                s = s[:x["at"]] + '"' + rows[k]["pt"] + '"' + s[x["end"]:]
                n += 1
        if n:
            path.write_text(s)
        print(path.name, n, "changed")


if __name__ == "__main__":
    main()
