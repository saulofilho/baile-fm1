#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-only
"""Find the first language's strings in BAILE's interface (KAWA's FR slot, BAILE's PT): every place that holds the
text of LANG 0, with the same text in LANG 1 (EN) and LANG 2 (ES) beside it.

  python3 tools/i18n_slots.py dump  > tools/i18n_pt.json      (a template: fill "pt")
  python3 tools/i18n_slots.py apply tools/i18n_pt.json         (writes the "pt" texts into the slots)
  python3 tools/i18n_slots.py check tools/i18n_pt.json         (each "pt" no longer than the longest of the three)

What it reads (kawa_data.c, kawa_ui.c, kawa_edit.c):
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
FILES = [ROOT / "firmware" / "src" / f for f in ("kawa_data.c", "kawa_ui.c", "kawa_edit.c")]
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


def main():
    cmd = sys.argv[1]
    allslots = []
    for p in FILES:
        allslots += slots_of(p)[1]
    if cmd == "dump":
        uniq = {}
        for x in allslots:
            key = x["fr"]
            u = uniq.setdefault(key, dict(en=x["en"], es=x["es"], pt="", n=0, kinds=[]))
            u["n"] += 1
            if x["kind"] not in u["kinds"]:
                u["kinds"].append(x["kind"])
        json.dump(uniq, sys.stdout, ensure_ascii=False, indent=1)
        print(f"\n{len(allslots)} slots, {len(uniq)} distinct", file=sys.stderr)
        return
    tr = json.loads(Path(sys.argv[2]).read_text())
    if cmd == "check":
        bad = 0
        for fr, u in tr.items():
            pt = u.get("pt", "")
            lim = max(len(fr), len(u["en"] or ""), len(u["es"] or ""))
            if not pt and fr:
                print("missing:", fr); bad += 1
            elif len(pt) > lim:
                print(f"too long ({len(pt)} > {lim}): {fr!r} -> {pt!r}"); bad += 1
            elif any(ord(ch) > 126 for ch in pt):
                print("not ASCII:", pt); bad += 1
        print("check:", "ok" if not bad else f"{bad} problems")
        sys.exit(1 if bad else 0)
    if cmd == "apply":
        for p in FILES:
            s, found = slots_of(p)
            for x in sorted(found, key=lambda x: -x["at"]):
                pt = tr[x["fr"]]["pt"]
                s = s[:x["at"]] + '"' + pt + '"' + s[x["end"]:]
            p.write_text(s)
            print(p.name, len(found), "slots")


if __name__ == "__main__":
    main()
