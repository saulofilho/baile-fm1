#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-only
"""BAILE's pixel art (KAWA's generator, with BAILE's mascot and boot): firmware/gen/kawa_art.h (drawn here as text) and firmware/gen/kawa_photo.h (from a PNG).

  python3 tools/gen_art.py            (needs Pillow, for the boot picture)

Icons are 8 x 8 ('#' lit), drawn by the firmware in one colour at 1x or 2x.
The mascot (16 x 16, the corner of every page) is BAILE's arara, a scarlet macaw with headphones, 16 inks
(INKS below) drawn with a palette: the headband and the cups take the colour of what is going on.
The boot picture is art/boot-baile.png (tools/gen_boot.py), 192 colours, one byte a pixel (kawa_photo.h,
about 58 KB of flash), with the corners of its tiles, which the boot lights one by one.
"""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "firmware" / "gen" / "kawa_art.h"
PHOTO_OUT = ROOT / "firmware" / "gen" / "kawa_photo.h"
BOOT_PNG = ROOT / "art" / "boot-baile.png"     # made by tools/gen_boot.py
BOOT_COLOURS = 192

ICONS = {
    # the six tracks
    "PULSE": ["........", ".###..##", ".#.#..#.", ".#.#..#.", ".#.#..#.", ".#.#..#.", "##.####.", "........"],
    "WAVE": ["........", "...#....", "..#.#...", ".#...#..", "#.....#.", ".......#", "........", "........"],
    "NOISE": ["........", ".#...#..", ".##.##.#", "#.#.#.##", "#.##.#.#", "#..#...#", "...#....", "........"],
    "KIT": ["........", ".######.", "#......#", "########", "#.#..#.#", "#......#", ".######.", "........"],
    "BREAK": ["....##..", "...##...", "..##....", ".######.", "....##..", "...##...", "..##....", ".##....."],
    # the cell tricks (FX column)
    "ARP": ["........", "......##", "......#.", "....###.", "....#...", "..###...", "..#.....", "###....."],
    "GLIDE": ["........", ".......#", "......#.", ".....#..", "...##...", ".##.....", "#.......", "........"],
    "VIB": ["........", "........", ".#...#..", "#.#.#.#.", "...#...#", "........", "........", "........"],
    "ROLL": ["........", "#.#.#.#.", "#.#.#.#.", "#.#.#.#.", "#.#.#.#.", "#.#.#.#.", "#.#.#.#.", "........"],
    "BEND": ["....#...", "...###..", "..#.#.#.", "....#...", "...#....", "..#.....", "##......", "........"],
    "DICE": [".######.", "#......#", "#.#..#.#", "#......#", "#.#..#.#", "#......#", ".######.", "........"],
    "CLOCK": ["..####..", ".#....#.", "#...#..#", "#...#..#", "#...##.#", "#......#", ".#....#.", "..####.."],
    "CUT": ["#.....#.", ".#...#..", "..#.#...", "...#....", "..#.#...", ".##.##..", "#..#..#.", ".##..##."],
    "REV": ["........", "...#...#", "..##..##", ".###.###", "..##..##", "...#...#", "........", "........"],
    "SHARP": ["..#..#..", "..#..#..", ".######.", "..#..#..", "..#..#..", ".######.", "..#..#..", "..#..#.."],
    "SHAPE": ["........", ".###....", ".#.#....", ".#.#....", ".#.#....", "##.#####", "........", "........"],
    "CRUSH": ["........", "......##", "......##", "....####", "....####", "..######", "..######", "########"],
    # live effects
    "LOOP": ["..####..", ".#....#.", "#......#", "#......#", "#..#...#", ".#.##.#.", "..####..", "...#...."],
    "UNI": ["........", ".##.##..", "#..#..#.", "#..#..#.", "#..#..#.", ".##.##..", "........", "........"],
    "UP": ["...#....", "..###...", ".#.#.#..", "...#....", "...#....", "...#....", "...#....", "........"],
    "DOWN": ["...#....", "...#....", "...#....", "...#....", ".#.#.#..", "..###...", "...#....", "........"],
    "STUT": ["........", "#.#.#.#.", "#.#.#...", "#.#.#...", "#.#.....", "#.#.....", "#.......", "........"],
    "DISC": ["..####..", ".#....#.", "#..##..#", "#.#..#.#", "#.#..#.#", "#..##..#", ".#....#.", "..####.."],
    "TRI3": ["........", "........", "#..#..#.", "#..#..#.", "........", "#..#..#.", "........", "........"],
    "AGAIN": ["..###.#.", ".#...##.", "#...###.", "#.......", "#......#", ".#....#.", "..####..", "........"],
    "ACCEL": ["........", "#..#.#.#", "#..#.#.#", "#..#.#.#", "#..#.#.#", "#..#.#.#", "#..#.#.#", "........"],
    "PIXEL": ["##..##..", "##..##..", "..##..##", "..##..##", "##..##..", "##..##..", "..##..##", "..##..##"],
    "LPF": ["........", "####....", "....#...", ".....#..", "......#.", "......#.", ".......#", "........"],
    "HPF": ["........", "....####", "...#....", "..#.....", ".#......", ".#......", "#.......", "........"],
    "TAPE": ["........", "########", "#......#", "#.#..#.#", "#......#", "#.####.#", "########", "........"],
    "DIVE": ["#.......", ".#......", "..#.....", "...#....", "....#..#", ".....#.#", "......##", "....####"],
    "GATE": ["........", "##.##.##", "##.##.##", "##.##.##", "##.##.##", "##.##.##", "........", "........"],
    "SNOW": ["...#....", ".#.#.#..", "..###...", "#######.", "..###...", ".#.#.#..", "...#....", "........"],
    "RING": ["..####..", ".#....#.", "#..##..#", "#.#..#.#", "#..##..#", ".#....#.", "..####..", "........"],
    "ECHO": ["........", "#.......", "#.#.....", "#.#.#...", "#.#.#.#.", "#.#.#.#.", "#.#.#.#.", "........"],
    "DIST": ["........", ".####...", "#....#..", "......#.", ".......#", "......#.", "#....#..", ".####..."],
    "WOB": ["........", "#......#", ".#....#.", "..#..#..", "..#..#..", ".#....#.", "#......#", "........"],
    "NOMEL": ["#....#..", ".#...##.", "..#..#.#", "...#.#..", "..###...", ".####.#.", ".###...#", "........"],
    "NOBEAT": ["#......#", ".######.", "#.#..#.#", "########", "#.#..#.#", "#..##..#", ".######.", "#......#"],
    # the magic tools
    "KNIFE": ["......##", ".....###", "....###.", "...###..", "..###...", ".#.#....", "#.#.....", ".#......"],
    "NOTE": ["...###..", "...#.##.", "...#....", "...#....", ".###....", "####....", ".##.....", "........"],
    "BASS": ["........", "...#....", "...#....", "...#....", ".###....", "####....", ".##.....", "########"],
    "EUCL": ["..#..#..", ".......#", "#.......", "........", "#......#", "........", ".#....#.", "...##..."],
    "VOL": ["........", "......#.", "....#.#.", "..#.#.#.", "#.#.#.#.", "#.#.#.#.", "#.#.#.#.", "........"],
    "X2": ["........", "#...#...", ".#.#....", "..#..##.", ".#.#...#", "#...#.#.", "....####", "........"],
    "RIGHT": ["........", "....#...", "....##..", "#######.", "....##..", "....#...", "........", "........"],
    "MIRROR": ["...#....", ".#.#.#..", "##.#.##.", "##.#.##.", "##.#.##.", ".#.#.#..", "...#....", "........"],
    "UPDN": ["...#....", "..###...", ".#.#.#..", "...#....", ".#.#.#..", "..###...", "...#....", "........"],
    "COPY": ["####....", "#..#....", "#.####..", "#.#..#..", "###..#..", "..#..#..", "..####..", "........"],
    "PASTE": ["..##....", "######..", "#....#..", "#.##.#..", "#....#..", "#.##.#..", "######..", "........"],
    "ERASE": ["........", "#.....#.", ".#...#..", "..#.#...", "...#....", "..#.#...", ".#...#..", "#.....#."],
    # engines, envelope, LFO, routing
    "FM": ["........", ".##..##.", "#..##..#", "#..##..#", "........", ".##..##.", "#..##..#", "........"],
    "SAMPLE": ["........", "...#....", "..##.#..", ".###.##.", "#######.", ".###.##.", "..##.#..", "...#...."],
    "ENV": ["........", "...#....", "..#.#...", "..#..##.", ".#.....#", ".#.....#", "#......#", "........"],
    "LFO": ["........", ".##.....", "#..#....", "#..#...#", "....#..#", "....#..#", ".....##.", "........"],
    "BPF": ["........", "...##...", "..#..#..", "..#..#..", ".#....#.", ".#....#.", "#......#", "........"],
    "TREM": ["........", "#.......", "##.#....", "####.#..", "########", "####.#..", "##.#....", "#......."],
    "VERB": ["..####..", ".#....#.", "#..##..#", "#.#..#.#", "#..##..#", ".#....#.", "..####..", "........"],
    "CLONE": ["####....", "#..#....", "#.####..", "#.#..#..", "###..#..", "..####..", "........", "........"],
    "THEME": ["..###...", ".#...#..", "#.#.#.#.", "#.....#.", "#.##..#.", ".#...#..", "..###...", "........"],
    "TARGET": ["...#....", ".#####..", "#.....#.", "#..#..#.", "#.....#.", ".#####..", "...#....", "........"],
    # small signs
    "PLAY": ["#.......", "##......", "###.....", "####....", "###.....", "##......", "#.......", "........"],
    "STOP": ["........", "######..", "######..", "######..", "######..", "######..", "........", "........"],
    "REC": ["........", "..###...", ".#####..", ".#####..", ".#####..", "..###...", "........", "........"],
    "CHAIN": ["........", "........", ".##..##.", "#..##..#", "#..##..#", ".##..##.", "........", "........"],
    "LOCK": ["..###...", ".#...#..", ".#...#..", "#######.", "###.###.", "###.###.", "#######.", "........"],
    "MUTE": ["...#....", "..##..#.", "####.#..", "####..#.", "####.#.#", "..##....", "...#....", "........"],
    "BETA": [".###....", "#...#...", "#..#....", "####....", "#...#...", "#...#...", "####....", "#......."],
}

# BAILE's mascot: an arara (a scarlet macaw) with headphones, 16 x 16, 4 bits a pixel. The inks keep KAWA's
# sixteen slots (dog_pal in kawa_ui.c gives them the macaw's colours):
INKS = ".kDGLWENPTHCcSRz"   # clear, outline, dark red, red, light red, white face, eye ring, upper beak, pupil,
#                            lower beak, headband (accent), cups, cups' rim, highlight, yellow feathers, blue / z z z
DOG16 = {
    "IDLE": [
        "......kkkk......",
        "....kkGLLGkk....",
        "...kGGGGGGGGk...",
        "..kHHHHHHHHHHk..",
        "..kGGGGGGGGGGk..",
        "CCkGWWGGGGWWGkCC",
        "CHkWEPWGGWPEWkHC",
        "CHkWWWWNNWWWWkHC",
        "CCkGWWNNNNWWGkCC",
        "..kGGNNNNNNGGk..",
        "..kDGGNTTNGGDk..",
        "..kDGGkTTkGGDk..",
        "..kRRGGkkGGRRk..",
        "...kRRRRRRRRk...",
        "....kzzzzzzk....",
        ".....kkkkkk.....",
    ],
    "BLINK": [
        "......kkkk......",
        "....kkGLLGkk....",
        "...kGGGGGGGGk...",
        "..kHHHHHHHHHHk..",
        "..kGGGGGGGGGGk..",
        "CCkGWWGGGGWWGkCC",
        "CHkWkkWGGWkkWkHC",
        "CHkWWWWNNWWWWkHC",
        "CCkGWWNNNNWWGkCC",
        "..kGGNNNNNNGGk..",
        "..kDGGNTTNGGDk..",
        "..kDGGkTTkGGDk..",
        "..kRRGGkkGGRRk..",
        "...kRRRRRRRRk...",
        "....kzzzzzzk....",
        ".....kkkkkk.....",
    ],
    "WILD": [
        "......kkkk......",
        "....kkGLLGkk....",
        "...kGGGGGGGGk...",
        "..kHHHHHHHHHHk..",
        "..kGGGGGGGGGGk..",
        "CCkGWkGGGGkWGkCC",
        "CHkWWkWGGWkWWkHC",
        "CHkWWWWNNWWWWkHC",
        "CCkGWWNNNNWWGkCC",
        "..kGGNNNNNNGGk..",
        "..kDGGNTTNGGDk..",
        "..kDGkTTTTkGDk..",
        "..kRRGGkkGGRRk..",
        "...kRRRRRRRRk...",
        "....kzzzzzzk....",
        ".....kkkkkk.....",
    ],
    "SLEEP": [
        "......kkkk...Sz.",
        "....kkGLLGkk....",
        "...kGGGGGGGGk...",
        "..kHHHHHHHHHHk..",
        "..kGGGGGGGGGGk..",
        "CCkGWWGGGGWWGkCC",
        "CHkWWWWGGWWWWkHC",
        "CHkWWWWNNWWWWkHC",
        "CCkGWWNNNNWWGkCC",
        "..kGGNNNNNNGGk..",
        "..kDGGNTTNGGDk..",
        "..kDGGNkkNGGDk..",
        "..kRRGGkkGGRRk..",
        "...kRRRRRRRRk...",
        "....kzzzzzzk....",
        ".....kkkkkk.....",
    ],
}


def main():
    names = list(ICONS)
    lines = ["/* generated by tools/gen_art.py: BAILE's icons (8 x 8) and the mascot (16 x 16, 4 bits) */",
             "#pragma once", "#include <stdint.h>",
             "enum { " + ", ".join(f"ICO_{n}" for n in names) + ", ICO_N };"]
    rows = []
    for n in names:
        img = ICONS[n]
        assert len(img) == 8 and all(len(r) == 8 for r in img), n
        rows.append("{" + ", ".join("0x%02X" % int(r.replace("#", "1").replace(".", "0"), 2) for r in img) + "}")
    lines.append("static const uint8_t ICONS[ICO_N][8] = {\n    " + ",\n    ".join(rows) + "};")
    def pack4(rows, w):
        out = []
        for r in rows:
            assert len(r) == w, r
            for x in range(0, w, 2):
                out.append(INKS.index(r[x]) | INKS.index(r[x + 1]) << 4)
        return out
    names16 = list(DOG16)
    lines.append("enum { " + ", ".join(f"DOG_{n}" for n in names16) + ", DOG_N };")
    lines.append("static const uint8_t DOG16[DOG_N][128] = {\n    " + ",\n    ".join(
        "{" + ", ".join(map(str, pack4(DOG16[n], 16))) + "}" for n in names16) + "};")
    OUT.write_text("\n".join(lines) + "\n")
    print("->", OUT, len(names), "icons,", len(names16), "mascot frames")
    photo()


def photo():
    """the boot picture: 240 x 240, BOOT_COLOURS colours (RGB565), a byte a pixel; and its tiles, which light up"""
    from PIL import Image
    import gen_boot
    im = Image.open(BOOT_PNG).convert("RGB").resize((240, 240), Image.LANCZOS)
    q = im.quantize(colors=BOOT_COLOURS, method=Image.Quantize.MEDIANCUT, dither=Image.Dither.NONE)
    flat = q.getpalette()[:3 * BOOT_COLOURS]
    rgb = [tuple(flat[i:i + 3]) for i in range(0, len(flat), 3)]
    rgb += [(0, 0, 0)] * (BOOT_COLOURS - len(rgb))
    pal = [(r >> 3) << 11 | (g >> 2) << 5 | (b >> 3) for r, g, b in rgb]
    idx = list(q.get_flattened_data() if hasattr(q, 'get_flattened_data') else q.getdata())
    tiles = [(x, y) for x, y, _, _ in gen_boot.tiles()]
    lines = ["/* generated by tools/gen_art.py from art/boot-baile.png (tools/gen_boot.py: BAILE's mosaic of tiles): the",
             " * boot picture, 240 x 240, a byte a pixel into BOOT_PAL (RGB565); BOOT_TILE: the tiles' corners, from the",
             " * middle out, which the boot lights one by one (BOOT_CELL square) */",
             "#pragma once", "#include <stdint.h>",
             f"#define BOOT_NTILE {len(tiles)}u", f"#define BOOT_CELL {gen_boot.CELL}",
             "static const uint8_t BOOT_TILE[BOOT_NTILE][2] = {" + ", ".join(f"{{{x}, {y}}}" for x, y in tiles) + "};",
             f"static const uint16_t BOOT_PAL[{BOOT_COLOURS}] = {{" + ", ".join(map(str, pal)) + "};",
             "static const uint8_t BOOT_IMG[240u * 240u] = {"]
    for y in range(240):
        lines.append("    " + ",".join(map(str, idx[y * 240:(y + 1) * 240])) + ",")
    lines.append("};")
    PHOTO_OUT.write_text("\n".join(lines) + "\n")
    print("->", PHOTO_OUT, "240 x 240,", BOOT_COLOURS, "colours,", len(tiles), "tiles")


if __name__ == "__main__":
    main()
