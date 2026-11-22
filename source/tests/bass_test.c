/* SPDX-License-Identifier: GPL-3.0-only */
/* GRAVE+ measured (tests/run_bass_test.sh): tones through the live bus alone, so nothing else is in the figures.
 * A small speaker plays nothing of an 808's fundamental: what it plays is what is over ~200 Hz. GRAVE+ must put the
 * bass there, louder or softer with it, and cost no more headroom than 0.3's (the lows twice, the soft knee). */
#define main kawa_host_main
#include "../firmware/src/kawa.c"
#undef main
#include <math.h>

#define FS_HZ 44100.0
#define NF 44096u                               /* a second, in whole chunks */
#define FROM 22048u                             /* measured once settled */
static int32_t inl[NF], inr[NF], ol[NF], or_[NF], refl[NF];
static int fails;
#define CHECK(c, ...) do { if (!(c)) { printf("FAIL  " __VA_ARGS__); printf("\n"); fails++; } } while (0)

static void tone(double hz, double amp, double ramp, int right)
{
    uint32_t i;
    for (i = 0; i < NF; i++) {
        double g = ramp > 0 && i < ramp ? i / ramp : 1.0;
        inl[i] = (int32_t)lrint(amp * g * sin(2 * M_PI * hz * i / FS_HZ));
        inr[i] = right ? inl[i] : 0;
    }
}

static void bus(uint32_t on_from, uint32_t on_to)   /* held from on_from to on_to */
{
    int32_t e[CHUNK];
    uint32_t i, k;
    lfx_on = 0;
    for (k = 0; k < 400u; k++) {                /* what the last tone left: gone */
        int32_t a[CHUNK] = {0}, b[CHUNK] = {0};
        fx_live(a, b, e);
    }
    for (i = 0; i < NF; i += CHUNK) {
        for (k = 0; k < CHUNK; k++) { ol[i + k] = inl[i + k]; or_[i + k] = inr[i + k]; e[k] = 0; }
        lfx_on = i >= on_from && i < on_to ? 1u << LF_BASS : 0u;
        fx_live(ol + i, or_ + i, e);
    }
}

static void ref03(void)                         /* 0.3's GRAVE+ */
{
    int32_t lo = 0;
    uint32_t i;
    for (i = 0; i < NF; i++) {
        lo += ((inl[i] - lo) * 560) >> 15;
        refl[i] = sat(inl[i] + lo);
    }
}

static double rms_over(const int32_t *x, double hz)     /* over hz (24 dB an octave); hz 0: all of it */
{
    double w = 2 * M_PI * hz / FS_HZ, c = cos(w), al = sin(w) / sqrt(2.0), a0 = 1 + al, s = 0, m1[4] = {0}, m2[4] = {0};
    uint32_t i, k;
    for (i = 0; i < NF; i++) {
        double v = x[i];
        for (k = 0; hz > 0 && k < 2u; k++) {
            double y = ((1 + c) / 2 * (v - 2 * m1[2 * k] + m2[2 * k]) + 2 * c * m1[2 * k + 1] - (1 - al) * m2[2 * k + 1]) / a0;
            m2[2 * k] = m1[2 * k]; m1[2 * k] = v;
            m2[2 * k + 1] = m1[2 * k + 1]; m1[2 * k + 1] = y;
            v = y;
        }
        if (i >= FROM) s += v * v;
    }
    return sqrt(s / (NF - FROM));
}

static double peak(const int32_t *x, uint32_t from)
{
    double p = 0;
    uint32_t i;
    for (i = from; i < NF; i++) if (fabs((double)x[i]) > p) p = fabs((double)x[i]);
    return p;
}

static double db(double a, double b) { return 20 * log10((a + 1e-9) / (b + 1e-9)); }

int main(void)
{
    static const double HZ[] = {41.2, 49.0, 55.0, 65.4, 82.4}, AMP[] = {3000, 8000, 16000, 28000};
    uint32_t h, a, i;
    app_init();
    printf("   Hz  level   on a small speaker: GRAVE+  0.3     peak / 0.3's\n");
    for (h = 0; h < 5u; h++)
        for (a = 0; a < 4u; a++) {
            double in, now, was, pk;
            tone(HZ[h], AMP[a], 0, 1);
            bus(0, NF);
            ref03();
            in = rms_over(inl, 0);
            now = db(rms_over(ol, 200), in);
            was = db(rms_over(refl, 200), in);
            pk = db(peak(ol, FROM), peak(refl, FROM));
            printf("%5.1f %6.0f  %19.1f dB %6.1f dB %+6.2f dB\n", HZ[h], AMP[a], now, was, pk);
            CHECK(now >= -21.0, "1. %.1f Hz at %.0f: %.1f dB on a small speaker (want -21 or more, under the bass)", HZ[h], AMP[a], now);
            CHECK(pk <= 0.3, "2. %.1f Hz at %.0f: the peak %+.2f dB over 0.3's (want +0.3 or less)", HZ[h], AMP[a], pk);
            {
                double dc = 0, w, ws = 0;      /* (under a Hann window: no half period counted as DC) */
                for (i = FROM; i < NF; i++) { w = 1 - cos(2 * M_PI * (i - FROM) / (NF - FROM)); dc += w * ol[i]; ws += w; }
                dc = fabs(dc / ws);
                CHECK(dc < AMP[a] * 0.03 + 8, "3. %.1f Hz at %.0f: DC %.0f", HZ[h], AMP[a], dc);
            }
        }
    tone(3000, 8000, 0, 1);
    bus(0, NF);
    CHECK(fabs(db(rms_over(ol, 0), rms_over(inl, 0))) < 0.5, "4. 3 kHz moved by %.2f dB (want 0.5 or less)",
          db(rms_over(ol, 0), rms_over(inl, 0)));
    tone(55, 12000, 0, 0);
    bus(0, NF);
    CHECK(peak(or_, 0) < 4, "5. bass on the left only: %.0f on the right", peak(or_, 0));
    tone(55, 12000, 0, 1);
    {
        double steady = 0, jump = 0;
        bus(0, NF);
        for (i = FROM; i < NF; i++) if (fabs((double)(ol[i] - ol[i - 1])) > steady) steady = fabs((double)(ol[i] - ol[i - 1]));
        bus(11200, 30000u & ~(CHUNK - 1u));     /* (pressed and let go on the loud of the wave) */
        for (i = 8000; i < NF; i++) if (fabs((double)(ol[i] - ol[i - 1])) > jump) jump = fabs((double)(ol[i] - ol[i - 1]));
        CHECK(jump <= steady * 1.6 + 40, "6. press and release: a step of %.0f (the wave's own %.0f): a click", jump, steady);
        for (i = 34000; i < NF && ol[i] == inl[i]; i++) ;
        CHECK(i == NF, "7. let go: not back to the dry sound within 0.1 s");
    }
    printf(fails ? "bass_test: %d failed\n" : "bass_test: passed\n", fails);
    return fails != 0;
}
