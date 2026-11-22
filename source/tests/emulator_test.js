// SPDX-License-Identifier: GPL-3.0-only
/* The built emulator page (../emulator/index.html) against the firmware it carries: the page's own engine, project
 * check and sample header, run on its own WebAssembly, no browser.
 *   node tests/emulator_test.js        (after web/make_emulator.sh)
 * It is there for the seams between the page and the firmware: a magic renamed on one side only breaks saving,
 * export, import and "send to my FM-1" without any other test noticing. */
"use strict";
const fs = require("node:fs");
const path = require("node:path");

const ROOT = path.join(__dirname, "..", "..");
const read = (p) => fs.readFileSync(path.join(ROOT, p), "utf8");
const page = read("emulator/index.html"), core = read("source/firmware/src/kawa_core.c");
const take = (re, what) => { const m = re.exec(page); if (!m) throw new Error("not found in the page: " + what); return m[1]; };
const define = (name) => parseInt(new RegExp("#define " + name + " (0x[0-9A-Fa-f]+)").exec(core)[1], 16);

const wasm = new Uint8Array(Buffer.from(take(/const WASM_B64 = "([^"]+)"/, "the wasm"), "base64"));
const Engine = new Function(take(/const ENGINE_SRC = `([\s\S]*?)`;/, "the engine") + "; return KawaEngine;")();
const hasProject = new Function("const SLOT = 0x9000; return " + take(/const hasProject = (\(u8\) => \{.*\});/, "hasProject"))();
const sampleHeader = new Function("crc32", take(/(function sampleHeader\([\s\S]*?\n  \})/, "sampleHeader") + "; return sampleHeader;")(() => 0);

let failed = 0;
function check(ok, what) { console.log((ok ? "ok    " : "FAIL  ") + what); if (!ok) failed++; }

function start(boot) {
    const e = new Engine(wasm, 44100, boot), out = { stores: [], names: [] };
    e.emit = (m) => { if (m.t === "store") out.stores.push(m.data); else if (m.t === "slots") out.names = m.names; };
    const L = new Float32Array(1323), R = new Float32Array(1323);       // 30 ms, as the page polls
    const run = (ms) => { for (let t = 0; t < ms; t += 30) { e.fill(L, R); e.poll(); } };
    const tap = (id) => { e.msg({ t: "btn", id, down: 1 }); run(90); e.msg({ t: "btn", id, down: 0 }); run(400); };
    return { e, out, run, tap };
}

const a = start({ lang: 0 });
a.run(800);
a.tap(8);                       // any button: past the boot
a.tap(12);                      // PLAY: the demo stops (nothing is written while it plays)
a.tap(9);                       // SAVE: PROJECTS, on SALVAR
for (let i = 0; i < 3; i++) a.tap(1);       // OCT+: save, its slot, its name
a.run(6000);
a.e.msg({ t: "getstore" });

const store = a.out.stores[a.out.stores.length - 1];
const magic = define("PRJ_MAGIC");
const u32 = (u, o) => (u[o] | u[o + 1] << 8 | u[o + 2] << 16 | u[o + 3] << 24) >>> 0;
const saved = !!store && [0, 1, 2, 3].some((k) => u32(store, k * 0x9000) === magic);
check(saved, "the firmware saves a project into the page's store");
check(saved && hasProject(store), "the page sees that project (kept on reload, exported, imported)");

const foreign = new Uint8Array(0x9000);
foreign.set(Buffer.from("KAWA"));
check(!hasProject(foreign), "a KAWA project file is refused (BAILE does not read KAWA's)");

if (saved) {
    const b = start({ lang: 0, store });
    b.run(500);
    b.e.msg({ t: "getstore" });
    const back = b.out.stores[b.out.stores.length - 1];
    check(!!back && Buffer.compare(Buffer.from(back.subarray(0, 0x9000)), Buffer.from(store.subarray(0, 0x9000))) === 0,
        "the store given back at power-on is the one saved");
}

check(u32(sampleHeader(new Uint8Array(64), 22050, "TESTE"), 0) === define("USR_MAGIC"),
    "\"send to my FM-1\" writes the sample magic the firmware accepts");
const s = start({ lang: 0, samples: [{ data: new Uint8Array(4000).fill(0x90), name: "TESTE", rate: 22050 }] });
s.run(300);
check(s.out.names[0] === "TESTE", "a sample given to the emulator is in MY 1");

const want = fs.existsSync(path.join(ROOT, "source", "VERSION")) ? read("source/VERSION").trim() : "(no source/VERSION)";
check(take(/id="beta-badge">([^<]*) BETA/, "the badge") === want, "the page's version is source/VERSION (" + want + ")");

console.log(failed ? "emulator_test: " + failed + " failed" : "emulator_test: passed");
process.exit(failed ? 1 : 0);
