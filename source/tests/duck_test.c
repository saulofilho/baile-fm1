/* SPDX-License-Identifier: GPL-3.0-only */
/* DUCK measured (tests/run_duck_test.sh): a track with DUCK steps back when a KIT track plays its kick (keys 1, 2).
 * 0, the default and what every project of 0.3 holds, changes nothing. */
#define main kawa_host_main
#include "../firmware/src/kawa.c"
#undef main
#include <math.h>

#define DUCK_OF(t) ((&prj.snd[t].sat)[1])       /* the byte after the SAT send: 0.3's padding */
#define BASS 2u
#define KICK 4u
#define OTHER 1u
static int32_t out[512];
static int fails;
#define CHECK(c, ...) do { if (!(c)) { printf("FAIL  " __VA_ARGS__); printf("\n"); fails++; } } while (0)

static void block(void)
{
    uint32_t i;
    for (i = 0; i < 512u; i++) out[i] = 0;
    app_audio(out, 256u);
}

typedef struct { double before, low, after; double step, ownstep; } duck_t;

/* a held note on the bass, then one drum: the bass's level (its own meter, per 5.8 ms) before, lowest, and 0.5 s on */
static duck_t hit(uint32_t amt, uint32_t drum, uint32_t vol, uint32_t muted, uint32_t kickvol)
{
    duck_t d = {0, 1e9, 0, 0, 0};
    int32_t last = 0;
    uint32_t i, k;
    sq_req = 2;
    block();
    prj_new();
    for (i = 0; i < NTRK; i++) { ev_push(EV_KILL, i, 0, 0, 0, 0); prj.snd[i].p[P_VERB] = prj.snd[i].p[P_ECHO] = 0; }
    ev_push(EV_KILL, NTRK, 0, 0, 0, 0);
    prj.snd[BASS].engine = E_WAVE;
    for (i = 0; i < 8u; i++) prj.snd[BASS].p[i] = 0;
    prj.snd[BASS].p[P_SUS] = 15;
    prj.snd[BASS].p[P_ATT] = 0;
    prj.snd[BASS].p[P_PAN] = 0;
    prj.snd[BASS].p[P_FXT] = FXT_OFF;
    sound_build(BASS);
    prj.snd[KICK].p[P_VOL] = (int8_t)kickvol;
    DUCK_OF(BASS) = (uint8_t)amt;
    DUCK_OF(KICK) = (uint8_t)amt;               /* (a kit does not step back from its own kick) */
    prj.mute = muted ? 1u << KICK : 0u;
    for (i = 0; i < 300u; i++) block();         /* the tails go */
    ev_push(EV_ON, BASS, 45, 12, 0, 0);         /* 110 Hz */
    for (i = 0; i < 90u; i++) block();
    for (i = 0; i < 20u; i++) {
        block();
        if (level[BASS] > d.before) d.before = level[BASS];
        for (k = 0; k < 256u; k++) { if (fabs((double)(out[2 * k] - last)) > d.ownstep && (i || k)) d.ownstep = fabs((double)(out[2 * k] - last)); last = out[2 * k]; }
    }
    ev_push(EV_ON, KICK, drum, vol, 0, 0);
    for (i = 0; i < 86u; i++) {
        double pk;
        block();
        pk = level[BASS];
        if (i >= 1u && i < 12u) {               /* (two blocks together: a whole cycle of the note) */
            static double was;
            if (i > 1u) { double m = pk > was ? pk : was; if (m < d.low) d.low = m; }
            was = pk;
        }
        if (i >= 78u && pk > d.after) d.after = pk;
        for (k = 0; k < 256u; k++) { if (fabs((double)(out[2 * k] - last)) > d.step) d.step = fabs((double)(out[2 * k] - last)); last = out[2 * k]; }
    }
    return d;
}

static double db(double a, double b) { return 20 * log10((a + 1e-9) / (b + 1e-9)); }

int main(void)
{
    duck_t d;
    uint32_t i;
    FILE *f;
    app_init();
    d = hit(15, 1, 15, 0, 12);
    CHECK(db(d.low, d.before) <= -13.0, "1. DUCK 15: %.1f dB under the kick (want -13 or lower)", db(d.low, d.before));
    CHECK(fabs(db(d.after, d.before)) < 1.0, "2. 0.5 s later: %.1f dB off its level (want under 1)", db(d.after, d.before));
    printf("DUCK 15: %.1f dB, back to %+.1f dB\n", db(d.low, d.before), db(d.after, d.before));
    d = hit(8, 1, 15, 0, 12);
    CHECK(db(d.low, d.before) <= -3.0 && db(d.low, d.before) >= -8.0, "3. DUCK 8: %.1f dB (want -3 to -8)", db(d.low, d.before));
    printf("DUCK 8: %.1f dB\n", db(d.low, d.before));
    d = hit(15, 2, 15, 0, 12);
    CHECK(db(d.low, d.before) <= -13.0, "4. the second kick (key 2): %.1f dB", db(d.low, d.before));
    d = hit(15, 1, 5, 0, 12);
    CHECK(db(d.low, d.before) <= -1.0 && db(d.low, d.before) >= -7.0, "5. a soft kick: %.1f dB (want -1 to -7)", db(d.low, d.before));
    d = hit(0, 1, 15, 0, 12);
    CHECK(fabs(db(d.low, d.before)) < 0.6, "6. DUCK 0 moved the bass %.1f dB", db(d.low, d.before));
    d = hit(15, 3, 15, 0, 12);
    CHECK(fabs(db(d.low, d.before)) < 0.6, "7. a snare moved the bass %.1f dB", db(d.low, d.before));
    d = hit(15, 1, 15, 1, 12);
    CHECK(fabs(db(d.low, d.before)) < 0.6, "8. a muted kit moved the bass %.1f dB", db(d.low, d.before));
    d = hit(15, 1, 15, 0, 0);
    CHECK(db(d.low, d.before) <= -13.0, "9. a kit at VOL 0 still ducks (a ghost kick): %.1f dB", db(d.low, d.before));
    CHECK(d.step <= d.ownstep * 1.3 + 30, "10. a step of %.0f as it ducks (the note's own %.0f): a click", d.step, d.ownstep);
    {
        uint32_t a, b;
        hit(0, 1, 15, 0, 12);
        a = level[KICK];
        hit(15, 1, 15, 0, 12);
        b = level[KICK];
        CHECK(a == b, "11. the kit ducked under its own kick (%u, %u)", a, b);
    }
    /* the format: a project saved by the 0.3 firmware itself */
    memset(host_flash[1], 0xFF, SLOT_SIZE);
    f = fopen("tests/fixtures/volt-0.3.baile", "rb");
    CHECK(f != NULL, "12. no tests/fixtures/volt-0.3.baile");
    if (f) {
        size_t n = fread(host_flash[1], 1, SLOT_SIZE, f);
        fclose(f);
        CHECK(n == sizeof prj, "12. the project is %u bytes, 0.3's was %u", (unsigned)sizeof prj, (unsigned)n);
        CHECK(prj_load(1) == 0, "12. 0.3's project does not load");
        CHECK(prj.bpm == 128u && prj.snd[2].sat == 5u, "12. 0.3's project came back different");
        for (i = 0; i < NTRK; i++) CHECK(DUCK_OF(i) == 0u, "12. track %u of 0.3's project: DUCK %u", i + 1u, DUCK_OF(i));
        DUCK_OF(BASS) = 11;
        CHECK(prj_save(2) == 0, "13. no save");
        DUCK_OF(BASS) = 0;
        CHECK(prj_load(2) == 0 && DUCK_OF(BASS) == 11u && prj.snd[2].sat == 5u, "13. DUCK did not come back from its slot");
        sound_preset(BASS, preset_named(E_WAVE, 0));
        CHECK(DUCK_OF(BASS) == 11u, "14. another preset lost the track's DUCK");
        DUCK_OF(BASS) = 200;
        prj_sanitize();
        CHECK(DUCK_OF(BASS) == 0u, "15. a damaged DUCK is let through");
    }
    /* the panel: SENDS, KNOB 4 */
    prj_new();
    cur_trk = BASS;
    set_page(PG_SEND);
    host_enc[ENC_KNOB4] += 6;
    for (i = 0; i < 8u; i++) ui_input();
    CHECK(DUCK_OF(BASS) >= 1u && DUCK_OF(BASS) <= 15u, "16. KNOB 4 on SENDS: DUCK %u", DUCK_OF(BASS));
    printf(fails ? "duck_test: %d failed\n" : "duck_test: passed\n", fails);
    return fails != 0;
}
