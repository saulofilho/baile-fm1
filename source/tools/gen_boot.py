#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-only
"""BAILE's boot picture: art/boot-baile.png, 240 x 240, a mosaic of hand-painted tiles on a black floor in the six
colours of a macaw's feathers, with a black band across the middle for the title (the firmware writes it).

  python3 tools/gen_boot.py           (needs Pillow; then tools/gen_art.py makes firmware/gen/kawa_photo.h)

The look is docs/moodboard/index.html's: 16 geometric symbols (chevron, diamond, stripes, sun, spiral, zigzag...),
thick and a little crooked, as if painted. TILES lists where each tile sits; the boot lights them one by one.
"""
import math
import random
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PNG = ROOT / "art" / "boot-baile.png"
SS = 4                                   # drawn at 4x, then taken down to 240 x 240 (smooth strokes)
CELL, GAP, N = 26, 4, 8                  # 8 x 8 tiles of 26 px, 4 px of black between them
BAND = (3, 4)                            # the rows left black for the title
FLOOR = (20, 18, 16)
INK = (20, 18, 16)
COLS = [(227, 33, 43), (242, 106, 27), (255, 207, 31), (90, 174, 58), (20, 163, 168), (31, 91, 214)]
MOTIFS = ["chevron", "losango", "listrasV", "sol", "diagonal", "pontos", "espiral", "zigue",
          "quadros", "xis", "trama", "alvo", "triangulo", "listrasH", "grade", "gota"]


def tiles():
    """(x, y, motif, colour) of every tile, in the order the boot lights them: from the middle out"""
    out = []
    for r in range(N):
        if r in BAND:
            continue
        for k in range(N):
            i = r * 17 + k * 5
            out.append((2 + k * (CELL + GAP), 2 + r * (CELL + GAP), MOTIFS[i % 16], COLS[(r + k * 2) % 6]))
    return sorted(out, key=lambda t: (abs(t[0] + CELL / 2 - 120) + abs(t[1] + CELL / 2 - 120), t[1], t[0]))


def motif(d, kind, x, y, s, ink, rnd, lw):
    w = lambda: (rnd.random() - .5) * s * .04

    def L(pts):
        d.line([(x + a * s + w(), y + b * s + w()) for a, b in pts], fill=ink, width=lw, joint="curve")

    def dot(cx, cy, r):
        d.ellipse([x + (cx - r) * s, y + (cy - r) * s, x + (cx + r) * s, y + (cy + r) * s], fill=ink)

    def ring(cx, cy, r):
        d.ellipse([x + (cx - r) * s, y + (cy - r) * s, x + (cx + r) * s, y + (cy + r) * s], outline=ink, width=lw)
    m, M = .2, .8
    if kind == "chevron":
        for i in range(3):
            yy = .28 + i * .22
            L([(.2, yy), (.5, yy + .12), (.8, yy)])
    elif kind == "losango":
        L([(.5, .18), (.82, .5), (.5, .82), (.18, .5), (.5, .18)])
        d.polygon([(x + .5 * s, y + .38 * s), (x + .62 * s, y + .5 * s), (x + .5 * s, y + .62 * s), (x + .38 * s, y + .5 * s)], fill=ink)
    elif kind == "listrasV":
        for i in range(5):
            L([(.22 + i * .14, m), (.22 + i * .14, M)])
    elif kind == "sol":
        for i in range(8):
            a = i * math.pi / 4
            L([(.5, .5), (.5 + math.cos(a) * .32, .5 + math.sin(a) * .32)])
        ring(.5, .5, .34)
    elif kind == "diagonal":
        for k in (0, .2, .4):
            L([(m + k, M), (M, m + k)])
        for k in (.2, .4):
            L([(m, M - k), (M - k, m)])
    elif kind == "pontos":
        for i in range(3):
            for j in range(3):
                dot(.27 + i * .23, .27 + j * .23, .055)
    elif kind == "espiral":
        L([(.5, .5), (.6, .5), (.6, .62), (.38, .62), (.38, .38), (.72, .38), (.72, .74), (.26, .74), (.26, .26), (.8, .26)])
    elif kind == "zigue":
        for k in range(2):
            yy = .33 + k * .32
            L([(.18, yy), (.32, yy - .1), (.46, yy + .08), (.6, yy - .1), (.74, yy + .08), (.84, yy - .04)])
    elif kind == "quadros":
        for o in (.16, .29, .42):
            L([(o, o), (1 - o, o), (1 - o, 1 - o), (o, 1 - o), (o, o)])
    elif kind == "xis":
        L([(m, m), (M, M)]); L([(M, m), (m, M)]); L([(m, m), (M, m), (M, M), (m, M), (m, m)])
    elif kind == "trama":
        for i in range(4):
            dd = .2 + i * .2
            L([(m, dd), (dd, m)]); L([(dd, M), (M, dd)]); L([(m, 1 - dd), (dd, M)]); L([(1 - dd, m), (M, 1 - dd)])
    elif kind == "alvo":
        ring(.5, .5, .3); dot(.5, .5, .1)
    elif kind == "triangulo":
        L([(.5, .2), (.8, .78), (.2, .78), (.5, .2)]); L([(.5, .42), (.64, .68), (.36, .68), (.5, .42)])
    elif kind == "listrasH":
        for i in range(5):
            L([(m, .22 + i * .14), (M, .22 + i * .14)])
    elif kind == "grade":
        L([(.38, m), (.38, M)]); L([(.62, m), (.62, M)]); L([(m, .38), (M, .38)]); L([(m, .62), (M, .62)])
    elif kind == "gota":
        L([(.3, .7), (.3, .4), (.5, .25), (.7, .4), (.7, .7), (.5, .8), (.3, .7)]); dot(.5, .55, .08)


def rough_square(d, x, y, s, fill, rnd, j):
    J = lambda: (rnd.random() - .5) * j
    d.polygon([(x + J(), y + J()), (x + s / 2 + J(), y + J() * .5), (x + s + J(), y + J()), (x + s + J() * .5, y + s / 2 + J()),
               (x + s + J(), y + s + J()), (x + s / 2 + J(), y + s + J() * .5), (x + J(), y + s + J()), (x + J() * .5, y + s / 2 + J())],
              fill=fill)


def main():
    from PIL import Image, ImageDraw
    im = Image.new("RGB", (240 * SS, 240 * SS), FLOOR)
    d = ImageDraw.Draw(im)
    for n, (x, y, kind, col) in enumerate(tiles()):
        rnd = random.Random(n * 7 + 3)
        rough_square(d, x * SS, y * SS, CELL * SS, col, rnd, CELL * SS * .07)
        ink = INK
        if n % 3 == 0:                   # now and then the stroke takes a neighbour's colour, as on a feather
            ink = {COLS[2]: COLS[0], COLS[5]: COLS[2], COLS[0]: COLS[2], COLS[4]: COLS[5]}.get(col, INK)
        motif(d, kind, x * SS, y * SS, CELL * SS, ink, rnd, int(2.2 * SS))
    im = im.resize((240, 240), Image.LANCZOS)
    PNG.parent.mkdir(exist_ok=True)
    im.save(PNG)
    print("->", PNG, len(tiles()), "tiles")


if __name__ == "__main__":
    main()
