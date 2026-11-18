/* SPDX-License-Identifier: GPL-3.0-only */
/* KAWA's project format on this computer (tests/run_format_test.sh): projects saved by KAWA 0.2 (format 4,
 * tests/fixtures/, written by the 0.2 firmware's own prj_save) load into format 5 as they were, a damaged one
 * is refused, and a format-5 project with every new field comes back from its slot byte for byte. */
#define main kawa_host_main
#include "../firmware/src/kawa.c"
#undef main

static int fails;
#define CHECK(c, ...) do { if (!(c)) { printf("FAIL  " __VA_ARGS__); printf("\n"); fails++; } } while (0)

/* KAWA's demo, "KAWA QUEST", as KAWA 0.2 saved it in tests/fixtures/demo-v4.kawa (BAILE has its own demo) */
static void kawa_quest(void)
{
    uint32_t p, r;
    prj_new();
    sound_preset(T1, preset_named(E_PULSE, 1));  /* (KAWA's new project: LEAD 25, NES BASS, HI-HAT) */
    sound_preset(T3, preset_named(E_WAVE, 0));
    sound_preset(T4, preset_named(E_NOISE, 0));
    prj.bpm = 120;                              /* (the demo and a new song both start at 120) */
    memcpy(prj.name, "KAWA QUEST", 11);
    prj.root = 0;                               /* C major (the dungeon and the boss are A minor: the same notes) */
    prj.scale = 1;
    sound_preset(T2, preset_named(E_FM, 11));   /* KALIMBA */
    sound_preset(T5, preset_named(E_KIT, 6));
    sound_preset(T6, preset_named(E_SAMPLE, 3));
    prj.snd[T1].p[P_ECHO] = 3;
    prj.snd[T2].p[P_ECHO] = 7;
    prj.snd[T2].p[P_VERB] = 6;
    prj.snd[T2].p[P_VOL] = 11;
    prj.snd[T4].p[P_VOL] = 10;
    prj.snd[T6].p[P_VOL] = 13;
    prj.snd[T1].p[P_VERB] = 3;
    for (p = 0; p < 7u; p++)
        prj.pat[p].len = 32;
    /* P1, P2: the overworld */
    lane(0, T1, "C5 . E5 G5 . E5 C6 . A5 . G5 . E5 . D5 . F5 . A5 . G5 E5 . C5 D5 . E5 . C5 . x .", 12);
    lane(1, T1, "E5 . G5 A5 . G5 E5 . D5 . E5 D5 C5 . A4 . B4 . C5 D5 . E5 G5 . F5 . E5 D5 C5 . . x", 12);
    lane(0, T3, "C3 . C4 . G3 . C4 . A2 . A3 . E3 . A3 . F2 . F3 . C3 . F3 . G2 . G3 . D3 . G3 .", 13);
    lane(1, T3, "A2 . A3 . E3 . A3 . F2 . F3 . C3 . F3 . G2 . G3 . D3 . G3 . C3 . C4 . G3 . C4 .", 13);
    for (p = 0; p < 2u; p++) {
        static const uint8_t CH[2][4] = {{72, 69, 65, 67}, {69, 65, 67, 72}};   /* roots: C Am F G / Am F G C */
        static const uint8_t MN[2][4] = {{0, 1, 0, 0}, {1, 0, 0, 0}};
        for (r = 0; r < 32u; r += 8u) {
            put(p, r + 2u, T2, CH[p][r / 8u], 9, FX_ARP, MN[p][r / 8u]);
            put(p, r + 6u, T2, CH[p][r / 8u], 7, FX_ARP, MN[p][r / 8u]);
        }
        lane(p, T4, ". . 96 . . . 96 96 . . 96 . . . 96 . . . 96 . . . 96 96 . . 96 . . 96 96 96", 9);
        lane(p, T5, "1 . . . 3 . . 1 1 . 1 . 3 . . . 1 . . . 3 . . 1 1 . 1 . 3 . 3 3", 13);
    }
    put(1, 4, T2, 96, 8, 0, 0);                 /* a counter-melody on the kalimba, between the chords */
    put(1, 12, T2, 100, 8, 0, 0);
    put(1, 20, T2, 98, 8, 0, 0);
    put(1, 28, T2, 103, 8, 0, 0);
    fx_at(1, 28, T1, FX_VIB, 6);
    fx_at(0, 6, T1, FX_GLIDE, 4);
    /* P3, P4: the dungeon (A minor, a 16th ostinato on the kalimba, drops of water) */
    lane(2, T2, "A4 E5 C5 E5 A4 E5 C5 E5 A#4 F5 D5 F5 A#4 F5 D5 F5 A4 E5 C5 E5 A4 E5 C5 E5 G#4 E5 B4 E5 G#4 E5 B4 E5", 8);
    lane(3, T2, "D5 A5 F5 A5 D5 A5 F5 A5 A4 E5 C5 E5 A4 E5 C5 E5 A#4 F5 D5 F5 A#4 F5 D5 F5 G#4 E5 B4 E5 G#4 E5 B4 E5", 8);
    lane(2, T3, "A2 . . . . . . . A#2 . . . . . . . A2 . . . . . . . E2 . . . . . . .", 12);
    lane(3, T3, "D3 . . . . . . . A2 . . . . . . . A#2 . . . . . . . E2 . . . . . . .", 12);
    lane(2, T1, ". . . . . . A6 x . . . . . . . . . . . . . . E6 x . . . . . . . .", 6);
    lane(3, T1, "E5 . . . . . F5 . E5 . . . D5 . . . C5 . . . B4 . . . G#4 . . . . . x .", 11);
    fx_at(3, 24, T1, FX_VIB, 7);
    fx_at(3, 6, T1, FX_GLIDE, 6);
    lane(2, T5, "1 . . . . . . . . . . . . . . . 1 . . . . . . . . . . . . . . .", 10);
    lane(3, T5, "1 . . . . . . . 4 . 1 . . . . . 1 . . . . . . . 4 . 1 . . . 4 4", 11);
    lane(3, T4, "96 . 96 . 96 . 96 . 96 . 96 . 96 . 96 . 96 . 96 . 96 . 96 . 96 . 96 . 96 . 96 96", 5);
    fx_at(3, 30, T5, FX_ROLL, 2);
    /* P5, P6: the boss (breakcore: the break chopped, kicks, a riff in harmonic minor) */
    lane(4, T6, "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 1 2 1 2 5 6 7 8 3 4 11 12 13 13 15 16", 13);
    lane(5, T6, "1 2 5 6 3 4 7 7 9 10 13 14 11 12 16 16 1 . 1 2 5 5 7 8 9 9 11 12 13 14 15 16", 13);
    fx_at(4, 29, T6, FX_ROLL, 1);
    fx_at(4, 31, T6, FX_ROLL, 3);
    fx_at(5, 8, T6, FX_REV, 0);
    fx_at(5, 14, T6, FX_ROLL, 2);
    fx_at(5, 20, T6, FX_PITCH, -5);
    fx_at(5, 31, T6, FX_ROLL, 5);
    lane(4, T5, "1 . . . 1 . . . 1 . . . 1 . 1 . 1 . . . 1 . . . 1 . . . 1 . 1 1", 15);
    lane(5, T5, "1 . . 1 1 . . . 1 . . 1 1 . 1 . 1 . . 1 1 . . . 1 . 1 . 1 1 1 1", 15);
    fx_at(5, 30, T5, FX_ROLL, 3);
    lane(4, T3, "A2 . A2 A3 . A2 C3 . G2 . G2 G3 . G2 A#2 . F2 . F2 F3 . F2 A2 . E2 . E2 E3 . G#2 B2 .", 14);
    lane(5, T3, "A2 . A2 A3 . A2 C3 . G2 . G2 G3 . G2 A#2 . F2 . F2 F3 . F2 A2 . E2 E3 E2 E3 G#2 G#3 B2 B3", 14);
    lane(4, T1, "A5 . . C6 . . B5 . G#5 . A5 . E5 . . . F5 . . E5 . . D5 . C5 . . . B4 . G#4 .", 12);
    lane(5, T1, "A5 . . . . . . . A#5 . . . . . . . A5 . . . . . . . G#5 . . . . . . .", 12);
    fx_at(4, 24, T1, FX_GLIDE, 5);
    fx_at(5, 0, T1, FX_ARP, 1);                 /* chip arpeggios: Am, Bb, Am, E dim */
    fx_at(5, 8, T1, FX_ARP, 0);
    fx_at(5, 16, T1, FX_ARP, 1);
    fx_at(5, 24, T1, FX_ARP, 8);
    lane(4, T2, "A4 . . . . . . . G4 . . . . . . . F4 . . . . . . . E4 . . . . . . .", 7);
    for (r = 0; r < 32u; r += 8u) fx_at(4, r, T2, FX_ARP, r ? 0 : 1);   /* Am G F E */
    lane(4, T4, "96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96", 6);
    lane(5, T4, "96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96 96", 7);
    fx_at(5, 15, T4, FX_ROLL, 2);
    for (r = 12; r < 16u; r++) prj.pat[5].live[r] = LF_LOOP32 + 1u;   /* live effects, recorded */
    prj.pat[5].live[30] = prj.pat[5].live[31] = LF_LOOP64 + 1u;
    for (r = 24; r < 30u; r++) prj.pat[5].live[r] = LF_LPF + 1u;
    /* P7: the victory */
    lane(6, T1, "G4 C5 E5 G5 C6 . . . . . . . A#5 . C6 . D6 . . . E6 . . . . . . . x . . .", 13);
    fx_at(6, 4, T1, FX_VIB, 4);
    fx_at(6, 20, T1, FX_VIB, 6);
    lane(6, T2, "C5 . . . . . . . F4 . . . A#4 . . . C5 . . . . . . . C7 . G6 . E6 . C6 .", 8);
    fx_at(6, 0, T2, FX_ARP, 0);
    fx_at(6, 8, T2, FX_ARP, 0);
    fx_at(6, 12, T2, FX_ARP, 0);
    fx_at(6, 16, T2, FX_ARP, 0);
    lane(6, T3, "C3 . C4 . C3 . C4 . F2 . F3 . A#2 . A#3 . C3 . . . . . . . . . . . x . . .", 13);
    lane(6, T5, "9 . . . 3 . . . 1 . . . 3 . 3 3 9 . . . . . . . . . . . . . . .", 14);
    fx_at(6, 15, T5, FX_ROLL, 3);
    {
        static const song_t SONG[7] = {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 1}};
        memcpy(prj.song, SONG, sizeof SONG);
        prj.song_len = 7;
    }
    prj.mode = 1;
    brushes_reset();
}


static int slot_from(uint32_t k, const char *path)
{
    FILE *f = fopen(path, "rb");
    size_t n;
    if (!f) { printf("FAIL  cannot open %s\n", path); fails++; return -1; }
    memset(host_flash[k], 0xFF, SLOT_SIZE);
    n = fread(host_flash[k], 1, SLOT_SIZE, f);
    fclose(f);
    {   /* BAILE: the fixtures were saved by KAWA ("KAWA" magic), which BAILE never reads; give them BAILE's magic
         * and their CRC again, so the format 4 -> 5 conversion is still tested */
        uint32_t h[2], body, crc;
        memcpy(h, host_flash[k], 8);
        if (h[0] == 0x4157414Bu) {
            h[0] = PRJ_MAGIC;
            memcpy(host_flash[k], h, 4);
            body = prj_body(h[1]);
            crc = ~crc_step(0xFFFFFFFFu, host_flash[k], body);
            memcpy(host_flash[k] + body, &crc, 4);
        }
    }
    return (int)n;
}

static void v5_defaults_check(const char *what)
{
    uint32_t t, i;
    for (t = 0; t < NTRK; t++) {
        CHECK(!prj.tbl[t].on && prj.tbl[t].speed == 6u && prj.tbl[t].len == 4u, "%s: track %u's table not off", what, t + 1u);
        CHECK(prj.sed[t].start == 0u && prj.sed[t].end == 65535u && prj.sed[t].gain == 256u && !prj.sed[t].manual &&
              !prj.sed[t].rev && !prj.sed[t].norm, "%s: track %u's sample edit not whole", what, t + 1u);
        for (i = 0; i < 16u; i++)
            CHECK(prj.sed[t].sl[i] == i * 4096u, "%s: track %u's slice %u not even", what, t + 1u, i + 1u);
    }
    CHECK(!prj.grv.on, "%s: the groove is on", what);
}

int main(void)
{
    static project_t want;
    uint32_t p, r, t, k;
    int n;
    /* 1. the demo, saved by 0.2 */
    n = slot_from(1, "tests/fixtures/demo-v4.kawa");
    CHECK(n == 26248, "demo-v4: %d bytes, not 26248", n);
    CHECK(slot_valid(1, 0) == 4, "demo-v4: not seen as format 4");
    kawa_quest();
    want = prj;
    want.bpm = 160;                             /* (the demo saved by 0.2 ran at 160; the demo now opens at 120) */
    prj_new();
    CHECK(prj_load(1) == 0, "demo-v4: refused");
    CHECK(prj.version == PRJ_VERSION, "demo-v4: still format %u", prj.version);
    CHECK(!memcmp(prj.name, want.name, 16), "demo-v4: the name");
    CHECK(prj.bpm == want.bpm && prj.song_len == want.song_len &&
          !memcmp(prj.song, want.song, want.song_len * sizeof prj.song[0]), "demo-v4: the song");
    CHECK(!memcmp(prj.snd, want.snd, sizeof prj.snd) && !memcmp(prj.fmp, want.fmp, sizeof prj.fmp), "demo-v4: the sounds");
    CHECK(!memcmp(prj.pat, want.pat, sizeof prj.pat), "demo-v4: the patterns are not the demo's");
    v5_defaults_check("demo-v4");
    printf("1. the demo saved by KAWA 0.2 loads as it was: %s\n", fails ? "NO" : "ok");
    /* 2. every trick and value of 0.2, on every track */
    n = slot_from(2, "tests/fixtures/tricks-v4.kawa");
    CHECK(prj_load(2) == 0, "tricks-v4: refused");
    for (r = 0, k = 0; r < NROW; r++)
        for (t = 0; t < NTRK; t++, k++) {
            const cell_t *c = &prj.pat[r % NPAT].c[r][t];
            uint32_t fx = k % 16u, note = k % 3u ? 40u + k % 60u : (k % 2u ? NOTE_OFF : 0u);
            int32_t fxv = clampi((int32_t)(k % 31u) - 15, FXD[fx].lo, FXD[fx].hi);
            CHECK(c->note == note && c->vol == 1u + k % 15u && c->fx == fx && (int8_t)c->fxv == fxv && !c->fx2 && !c->fxv2,
                  "tricks-v4: pattern %u row %u track %u: %u %u %u %d %u, want %u %u %u %d", r % NPAT + 1u, r + 1u, t + 1u,
                  c->note, c->vol, c->fx, (int8_t)c->fxv, c->fx2, note, 1u + k % 15u, fx, fxv);
        }
    for (p = 0; p < NPAT; p++)
        CHECK(prj.pat[p].len == 1u + p % 32u && prj.pat[p].live[p % NROW] == 1u + p, "tricks-v4: pattern %u's length, LIVE",
              p + 1u);
    v5_defaults_check("tricks-v4");
    printf("2. every 0.2 trick and value, every track, the LIVE lanes and lengths: %s\n", fails ? "NO" : "ok");
    /* 3. a damaged 0.2 project is refused (the CRC) */
    host_flash[2][700] ^= 0x10u;
    CHECK(slot_valid(2, 0) == 0 && prj_load(2) != 0, "tricks-v4 damaged: loaded");
    printf("3. a damaged 0.2 project is refused: %s\n", fails ? "NO" : "ok");
    /* 4. format 5 round trip: the second column, the tables, the sample edits, the groove */
    prj_demo();
    prj.pat[3].c[5][2].fx2 = FX_HOP;
    prj.pat[3].c[5][2].fxv2 = 7;
    prj.pat[4].c[31][5].fx2 = FX_END;
    prj.pat[0].c[0][0].fx2 = FX_VIB;
    prj.pat[0].c[0][0].fxv2 = 9;
    for (t = 0; t < NTRK; t++) {
        prj.tbl[t].on = 1;
        prj.tbl[t].speed = (uint8_t)(1u + t * 3u);
        prj.tbl[t].len = (uint8_t)(3u + t);
        prj.tbl[t].loop = (uint8_t)(t % 3u);
        for (k = 0; k < NTSTEP; k++) {
            prj.tbl[t].s[k].tr = (int8_t)((int32_t)(k * 3u % 25u) - 12);
            prj.tbl[t].s[k].vol = (uint8_t)(k % 16u);
            prj.tbl[t].s[k].fx = (uint8_t)(k % TB_N);
            prj.tbl[t].s[k].fxv = (int8_t)clampi((int32_t)k - 7, TBD[k % TB_N].lo, TBD[k % TB_N].hi);
        }
    }
    prj.sed[5].start = 4000;
    prj.sed[5].end = 60000;
    prj.sed[5].manual = 1;
    for (k = 0; k < 16u; k++) prj.sed[5].sl[k] = (uint16_t)(4000u + k * 3500u);
    prj.sed[5].rev = 1;
    prj.sed[5].norm = 1;
    prj.sed[5].gain = 700;
    prj.grv.on = 1;
    prj.grv.len = 3;
    prj.grv.tick[0] = 8; prj.grv.tick[1] = 4; prj.grv.tick[2] = 6;
    prj_sanitize();
    sed_normalise(5);
    CHECK(prj_save(3) == 0, "v5: the save failed");
    want = prj;                                 /* (as saved: its slot, its CRC) */
    CHECK(slot_valid(3, 0) == 5, "v5: not seen as format 5");
    prj_new();
    CHECK(prj_load(3) == 0, "v5: refused");
    for (k = 0; k < sizeof prj && ((uint8_t *)&prj)[k] == ((uint8_t *)&want)[k]; k++)
        ;
    CHECK(k == sizeof prj, "v5: did not come back as it was (byte %u of %u)", k, (unsigned)sizeof prj);
    printf("4. format 5 (two columns, tables, sample edits, groove) comes back byte for byte: %s\n", fails ? "NO" : "ok");
    printf("sizes: cell %u B, pattern %u B, project %u B of a %u B slot\n", (unsigned)sizeof(cell_t),
           (unsigned)sizeof(pat_t), (unsigned)sizeof(project_t), SLOT_SIZE);
    if (fails) { printf("format_test: %d failures\n", fails); return 1; }
    printf("format_test: passed\n");
    return 0;
}
