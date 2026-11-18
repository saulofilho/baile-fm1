/* SPDX-License-Identifier: GPL-3.0-only */
/* BAILE: the drum kits (KAWA's KIT engine, kawa_drums.c): 8 kits of Brazilian funk, 16 drums each on the 16 white
 * keys, their names and the codes the tracker shows. Included before kawa_data.c (its KIT sound lists the kits).
 * Every kit keeps key 1 a kick, 2 a second kick (the magic beat's hard one), 3 a snare, 5 a closed hat, 6 an
 * open hat (PERCUS, the Brazilian percussion: the low atabaque, the high one, the slap, the chocalho, the
 * pandeiro), so a beat survives a change of kit; the other keys are the kit's own.
 * All synthesised (no recording): the "Volt" kit is a beat in that style, not its sample */
#define NDRUM 16u
#define NKIT 8u
static const char *const L_KITS[NKIT * 3u] = {   /* (K_LIST: Portuguese, English, Spanish) */
    "VOLT", "TAMBOR", "150", "MANDELA", "BREGA", "MELODY", "TUIN", "PERCUS",
    "VOLT", "TAMBOR", "150", "MANDELA", "BREGA", "MELODY", "TUIN", "PERCUS",
    "VOLT", "TAMBOR", "150", "MANDELA", "BREGA", "MELODY", "TUIN", "PERCUS"};
static const char KIT_CODE3[NKIT][NDRUM][4] = {   /* what the tracker shows, wide (3) and narrow (2) */
    {"KIK", "BOM", "SNR", "CLP", "CHH", "OHH", "LTM", "HTM", "COW", "CLV", "RIM", "SHK", "CNG", "CRS", "MAR", "ORC"},
    {"KIK", "TUM", "CXA", "PLM", "CHH", "OHH", "TBG", "TBM", "TBA", "TSL", "ABF", "TIR", "RIM", "SHK", "COW", "PL3"},
    {"KIK", "PNC", "SNR", "CLP", "CHH", "OHH", "LTM", "HTM", "RIM", "SNP", "CRS", "MTL", "ZAP", "BLP", "COW", "RLL"},
    {"KIK", "SUB", "SNR", "CLP", "CHH", "OHH", "MTL", "MT2", "BRX", "RSW", "CRK", "ZAP", "TOM", "RIM", "GLT", "LAS"},
    {"KIK", "KK2", "SNR", "PL2", "CHH", "OHH", "TML", "TMH", "LTM", "HTM", "COW", "RIM", "SHK", "TAM", "SNP", "CRS"},
    {"KIK", "KK2", "SNR", "CLP", "CHH", "OHH", "LTM", "HTM", "RID", "CRS", "RIM", "TAM", "SHK", "COW", "CLV", "BEL"},
    {"KIK", "BOM", "SNR", "CLP", "CHH", "OHH", "SIR", "SR2", "APT", "TUI", "LAS", "TIR", "EXP", "VNL", "SCR", "SOB"},
    {"ATG", "ATA", "SLP", "SRD", "CHC", "PDR", "TMB", "CXG", "AGL", "AGH", "CUL", "CUH", "REC", "TRI", "APT", "GNZ"}};
static const char KIT_CODE2[NKIT][NDRUM][3] = {
    {"KI", "BM", "SN", "CP", "HH", "OH", "LT", "HT", "CB", "CL", "RM", "SK", "CG", "CR", "MR", "OR"},
    {"KI", "TU", "CX", "PL", "HH", "OH", "TG", "TM", "TA", "TS", "AB", "TI", "RM", "SK", "CB", "P3"},
    {"KI", "PN", "SN", "CP", "HH", "OH", "LT", "HT", "RM", "SP", "CR", "MT", "ZP", "BP", "CB", "RL"},
    {"KI", "SB", "SN", "CP", "HH", "OH", "MT", "M2", "BX", "RS", "CK", "ZP", "TM", "RM", "GL", "LZ"},
    {"KI", "K2", "SN", "P2", "HH", "OH", "TL", "TH", "LT", "HT", "CB", "RM", "SK", "TB", "SP", "CR"},
    {"KI", "K2", "SN", "CP", "HH", "OH", "LT", "HT", "RD", "CR", "RM", "TB", "SK", "CB", "CL", "BL"},
    {"KI", "BM", "SN", "CP", "HH", "OH", "SI", "S2", "AP", "TU", "LZ", "TI", "EX", "VN", "SC", "SO"},
    {"AG", "AA", "SL", "SR", "CH", "PD", "TB", "CX", "AL", "AH", "CL", "CU", "RR", "TR", "AP", "GZ"}};

typedef struct {
    uint8_t wave, note;                         /* tone A: its wave (W_*), its pitch (a MIDI note) */
    int8_t drop;                                /* semitones above the note at the hit (below if < 0) */
    uint8_t ptau, atau, tone;                   /* the drop's time (DR_STEP: when, 5.8 ms a step), the decay, level */
    uint8_t w2;                                 /* tone B: its wave | B_RING or B_FM */
    uint16_t r2;                                /* its pitch over A's, Q8 (256: the same) */
    uint8_t l2, btau;                           /* its level (FM: the index; ring: the depth), decay (0: A's) */
    uint8_t src, clk, noise, ntau;              /* the noise: N_* (| a metal tuning << 4), its clock (a MIDI note,
                                                 * 0: every frame; the metal's base; crackle: clicks / 256 frames),
                                                 * the body's level and decay */
    uint8_t filt, fnote;                        /* the filter: F_* | resonance 0..15 << 2, its cutoff (a MIDI note) */
    uint8_t click, ctau, hits, hgap;            /* the spike (through the filter), its decay, re-strikes, their gap
                                                 * (chunks of 16 frames, 0.36 ms) */
    uint8_t rise, wob, wrate;                   /* an attack (a time), a wobble (1/16 semitone) at a rate (1/4 Hz) */
    uint8_t srate, bits, drive, vol, flags;     /* the hold (SR_*), bits taken, drive, gain (128: x1), DR_* */
} drumdef_t;
enum { W_SINE, W_TRI, W_SQUARE, W_PULSE, W_PULSE12, W_SAW, W_GB4 };
enum { B_RING = 0x10, B_FM = 0x20 };
enum { N_WHITE, N_LFSR15, N_LFSR7, N_METAL, N_CRACKLE };
enum { F_OFF, F_LP, F_BP, F_HP };
enum { SR_OFF, SR_32K, SR_26K, SR_22K, SR_16K, SR_11K, SR_8K, SR_5K };
enum { DR_TFILT = 1, DR_FSWEEP = 2, DR_HTONE = 4, DR_TAIL = 8, DR_HAT = 16, DR_WRND = 32, DR_GB = 64, DR_STEP = 128 };
/* DR_TFILT the tones through the filter too; DR_FSWEEP the cutoff follows the pitch envelope; DR_HTONE a re-strike
 * strikes it all again (a flam); DR_TAIL the body waits for the last re-strike (a clap's room); DR_HAT the hats
 * choke each other; DR_WRND the wobble starts anywhere; DR_GB the Game Boy's stepped volume and pitch; DR_STEP the
 * pitch steps (drop, then the note) instead of falling */

/* a row: tone A, tone B, the noise, the filter, the spike, the modulations, the output */
#define DT(w, n, d, pt, at, l) w, n, d, pt, at, l
#define DB(w, r, l, bt) w, r, l, bt
#define DN(s, c, l, nt) s, c, l, nt
#define DF(m, q, fn) (m) | (q) << 2, fn
#define DK(l, ct, h, hg) l, ct, h, hg
#define DM(r, wb, wr) r, wb, wr
#define DO(sr, b, dr, vo, fl) sr, b, dr, vo, fl
#define T0 DT(W_SINE, 60, 0, 0, 0, 0)
#define B0 DB(W_SINE, 256, 0, 0)
#define N0 DN(N_WHITE, 0, 0, 0)
#define F0 DF(F_OFF, 0, 0)
#define K0 DK(0, 0, 0, 0)
#define M0 DM(0, 0, 0)
#define MTL(set) (N_METAL | (set) << 4)
static const drumdef_t KITS[NKIT][NDRUM] = {
    {   /* VOLT: Miami bass and the first funk carioca, an 808 at heart: a long boom, its snare and clap, metallic
         * hats, its toms, conga, cowbell and clave, maracas, a crash and the orchestra stab */
        {DT(W_SINE, 29, 5, 30, 45, 125), B0, N0, DF(F_LP, 1, 84),
         DK(40, 6, 0, 0), M0, DO(SR_OFF, 0, 2, 110, 0)},                                  /* KICK, the 808's boom */
        {DT(W_SINE, 26, 12, 26, 51, 125), B0, N0, DF(F_LP, 0, 76),
         DK(20, 6, 0, 0), M0, DO(SR_OFF, 0, 2, 80, 0)},                                   /* BOOM, longer, lower */
        {DT(W_SINE, 56, 3, 16, 24, 80), DB(W_SINE, 461, 60, 0), DN(N_WHITE, 0, 140, 30), DF(F_HP, 1, 100),
         DK(90, 8, 0, 0), M0, DO(SR_OFF, 0, 1, 128, 0)},                                  /* SNARE, 808 */
        {T0, B0, DN(N_WHITE, 0, 150, 34), DF(F_BP, 3, 86), DK(255, 10, 3, 28), M0,
         DO(SR_OFF, 0, 1, 128, DR_TAIL)},                                                 /* CLAP */
        {T0, B0, DN(MTL(0), 56, 200, 20), DF(F_HP, 1, 118), DK(40, 6, 0, 0), M0,
         DO(SR_OFF, 0, 1, 128, DR_HAT)},                                                  /* CLOSED HAT */
        {T0, B0, DN(MTL(0), 56, 190, 40), DF(F_HP, 1, 116), DK(30, 6, 0, 0), M0,
         DO(SR_OFF, 0, 1, 128, DR_HAT)},                                                  /* OPEN HAT */
        {DT(W_SINE, 43, 3, 34, 44, 120), B0, N0, DF(F_LP, 1, 84),
         DK(20, 8, 0, 0), M0, DO(SR_OFF, 0, 0, 128, 0)},                                  /* LOW TOM, 808 */
        {DT(W_SINE, 50, 3, 34, 42, 120), B0, N0, DF(F_LP, 1, 88),
         DK(20, 8, 0, 0), M0, DO(SR_OFF, 0, 0, 128, 0)},                                  /* HIGH TOM, 808 */
        {DT(W_SQUARE, 73, 0, 0, 32, 90), DB(W_SQUARE, 379, 90, 0), N0, DF(F_BP, 3, 80), K0, M0,
         DO(SR_OFF, 0, 1, 128, DR_TFILT)},                                                /* COWBELL, 808 */
        {DT(W_SINE, 99, 0, 0, 20, 130), B0, N0, F0, K0, M0, DO(SR_OFF, 0, 2, 128, 0)},  /* CLAVE */
        {DT(W_TRI, 88, 0, 0, 12, 110), DB(W_SINE, 832, 80, 10), N0, DF(F_BP, 4, 103),
         DK(80, 6, 0, 0), M0, DO(SR_OFF, 0, 4, 128, 0)},                                  /* RIM */
        {T0, B0, DN(N_WHITE, 0, 220, 24), DF(F_BP, 3, 115), K0, DM(16, 0, 0), DO(SR_OFF, 0, 0, 128, 0)},   /* SHAKER */
        {DT(W_SINE, 62, 2, 30, 36, 120), B0, N0, DF(F_LP, 1, 96),
         DK(20, 6, 0, 0), M0, DO(SR_OFF, 0, 0, 128, 0)},                                  /* CONGA, 808 */
        {T0, B0, DN(MTL(1), 69, 200, 50), DF(F_HP, 1, 112), DK(90, 16, 0, 0), M0,
         DO(SR_OFF, 0, 1, 128, 0)},                                                       /* CRASH */
        {T0, B0, DN(N_WHITE, 0, 200, 14), DF(F_HP, 2, 120), K0, M0, DO(SR_OFF, 0, 0, 128, 0)},   /* MARACAS */
        {DT(W_SAW, 60, 0, 0, 38, 100), DB(W_SAW, 384, 100, 0), DN(N_WHITE, 0, 60, 24), DF(F_LP, 1, 107), K0, M0,
         DO(SR_OFF, 0, 2, 128, DR_TFILT)},                                                /* ORCHESTRA STAB */
    },
    {   /* TAMBOR: the tamborzao, atabaques in the drum machine: a dry kick, the deep "tum", a dry snare, palms,
         * the atabaques (low, middle, high, the slap, muted), the snare shot, a rim, a shaker, a cowbell */
        {DT(W_SINE, 33, 14, 18, 34, 120), DB(W_SINE, 512, 30, 24), N0, DF(F_LP, 1, 92),
         DK(90, 8, 0, 0), M0, DO(SR_OFF, 0, 3, 110, 0)},                                  /* KICK, dry */
        {DT(W_SINE, 36, 7, 30, 42, 125), DB(W_SINE, 407, 30, 34), DN(N_WHITE, 0, 20, 26), DF(F_LP, 1, 82),
         DK(60, 10, 0, 0), M0, DO(SR_OFF, 0, 1, 96, 0)},                                  /* TUM: the deep drum */
        {DT(W_SINE, 58, 4, 16, 22, 70), DB(W_SINE, 435, 40, 0), DN(N_WHITE, 0, 160, 28), DF(F_BP, 2, 104),
         DK(160, 8, 0, 0), M0, DO(SR_OFF, 0, 3, 128, 0)},                                 /* SNARE, dry */
        {T0, B0, DN(N_WHITE, 0, 140, 30), DF(F_BP, 3, 88), DK(240, 10, 2, 24), M0,
         DO(SR_OFF, 0, 2, 128, DR_TAIL)},                                                 /* PALMS */
        {T0, B0, DN(N_WHITE, 0, 160, 20), DF(F_BP, 2, 108), DK(70, 6, 0, 0), M0,
         DO(SR_OFF, 0, 0, 128, DR_HAT)},                                                  /* CLOSED HAT, a hiss */
        {T0, B0, DN(N_WHITE, 0, 140, 36), DF(F_HP, 1, 114), K0, DM(6, 0, 0),
         DO(SR_OFF, 0, 0, 128, DR_HAT)},                                                  /* OPEN HAT */
        {DT(W_SINE, 48, 3, 28, 36, 125), DB(W_SINE, 407, 30, 28), N0, DF(F_LP, 1, 88),
         DK(60, 10, 0, 0), M0, DO(SR_OFF, 0, 2, 128, 0)},                                 /* ATABAQUE, low */
        {DT(W_SINE, 55, 3, 26, 34, 125), DB(W_SINE, 407, 30, 26), N0, DF(F_BP, 3, 95),
         DK(60, 8, 0, 0), M0, DO(SR_OFF, 0, 2, 128, 0)},                                  /* ATABAQUE, middle */
        {DT(W_SINE, 62, 2, 24, 30, 125), DB(W_SINE, 407, 30, 24), N0, DF(F_BP, 3, 100),
         DK(70, 8, 0, 0), M0, DO(SR_OFF, 0, 2, 128, 0)},                                  /* ATABAQUE, high */
        {DT(W_SINE, 60, 0, 0, 18, 70), B0, DN(N_WHITE, 0, 80, 22), DF(F_BP, 4, 101),
         DK(200, 12, 0, 0), M0, DO(SR_OFF, 0, 4, 128, 0)},                                /* ATABAQUE, slap */
        {DT(W_SINE, 57, 1, 14, 20, 110), B0, DN(N_WHITE, 0, 40, 16), DF(F_BP, 4, 96),
         DK(120, 6, 0, 0), M0, DO(SR_OFF, 0, 2, 128, 0)},                                 /* ATABAQUE, muted */
        {DT(W_SINE, 60, 12, 14, 24, 80), DB(W_SINE, 461, 50, 0), DN(N_WHITE, 0, 180, 40), DF(F_BP, 1, 106),
         DK(200, 8, 0, 0), M0, DO(SR_OFF, 0, 5, 110, 0)},                                 /* SNARE SHOT */
        {DT(W_SINE, 76, 0, 0, 14, 120), DB(W_TRI, 671, 70, 12), N0, DF(F_BP, 5, 96),
         DK(90, 6, 0, 0), M0, DO(SR_OFF, 0, 3, 128, 0)},                                  /* RIM */
        {T0, B0, DN(N_WHITE, 0, 200, 26), DF(F_BP, 3, 115), DK(0, 0, 1, 50), DM(16, 0, 0),
         DO(SR_OFF, 0, 0, 128, DR_HTONE)},                                                /* SHAKER */
        {DT(W_PULSE, 69, 0, 0, 34, 110), DB(W_SQUARE, 379, 100, 0), N0, DF(F_BP, 2, 86), DK(60, 6, 0, 0), M0,
         DO(SR_OFF, 0, 1, 128, DR_TFILT)},                                                /* COWBELL */
        {T0, B0, DN(N_WHITE, 0, 130, 33), DF(F_BP, 3, 85), DK(220, 10, 3, 22), M0,
         DO(SR_OFF, 0, 1, 128, DR_TAIL)},                                                 /* PALMS, three */
    },
    {   /* 150: the fast funk of Rio, short and hard: a punchy kick and a distorted one, a cracking snare, a clap,
         * tight hats, synth toms, a rim, a snap, a crash, a metal hit, a zap, a blip, a cowbell, a snare roll */
        {DT(W_SINE, 34, 24, 14, 32, 120), DB(W_TRI, 2048, 40, 10), N0, DF(F_LP, 1, 112),
         DK(110, 6, 0, 0), M0, DO(SR_OFF, 0, 4, 110, 0)},                                 /* KICK, short and hard */
        {DT(W_SINE, 33, 36, 14, 38, 100), DB(W_SINE, 512, 40, 24), N0, DF(F_LP, 1, 108),
         DK(90, 8, 0, 0), M0, DO(SR_OFF, 0, 7, 48, 0)},                                   /* PUNCH, distorted */
        {DT(W_SINE, 60, 5, 14, 22, 75), DB(W_SINE, 461, 55, 0), DN(N_WHITE, 0, 170, 28), DF(F_HP, 1, 104),
         DK(180, 8, 0, 0), M0, DO(SR_OFF, 0, 3, 128, 0)},                                 /* SNARE, cracking */
        {T0, B0, DN(N_WHITE, 0, 160, 28), DF(F_BP, 4, 92), DK(255, 8, 3, 20), M0,
         DO(SR_OFF, 0, 3, 128, DR_TAIL)},                                                 /* CLAP, tight */
        {T0, B0, DN(MTL(3), 74, 200, 14), DF(F_HP, 1, 120), DK(50, 6, 0, 0), M0,
         DO(SR_OFF, 0, 1, 128, DR_HAT)},                                                  /* CLOSED HAT, tight */
        {T0, B0, DN(MTL(3), 74, 190, 32), DF(F_HP, 1, 118), DK(40, 6, 0, 0), M0,
         DO(SR_OFF, 0, 1, 128, DR_HAT)},                                                  /* OPEN HAT */
        {DT(W_TRI, 45, 14, 26, 36, 115), B0, DN(N_WHITE, 0, 30, 20), DF(F_LP, 1, 96),
         DK(30, 8, 0, 0), M0, DO(SR_OFF, 0, 1, 128, 0)},                                  /* LOW TOM, synth */
        {DT(W_TRI, 52, 14, 26, 34, 115), B0, DN(N_WHITE, 0, 30, 18), DF(F_LP, 1, 99),
         DK(30, 8, 0, 0), M0, DO(SR_OFF, 0, 1, 128, 0)},                                  /* HIGH TOM, synth */
        {DT(W_SINE, 70, 0, 0, 16, 110), DB(W_SINE, 937, 60, 10), N0, DF(F_BP, 6, 91),
         DK(110, 6, 0, 0), M0, DO(SR_OFF, 0, 3, 128, 0)},                                 /* RIM */
        {T0, B0, DN(N_WHITE, 0, 50, 22), DF(F_BP, 5, 96), DK(200, 10, 1, 8), M0, DO(SR_OFF, 0, 2, 128, 0)},   /* SNAP */
        {DT(W_SQUARE, 94, 0, 0, 46, 40), DB(W_SQUARE | B_RING, 443, 128, 0), DN(N_WHITE, 0, 120, 48), DF(F_HP, 0, 105),
         DK(90, 14, 0, 0), M0, DO(SR_OFF, 0, 0, 128, DR_TFILT)},                          /* CRASH */
        {DT(W_SQUARE, 80, 0, 0, 20, 80), DB(W_SQUARE | B_RING, 443, 128, 0), N0, DF(F_BP, 4, 100),
         DK(60, 6, 0, 0), M0, DO(SR_OFF, 0, 2, 128, DR_TFILT)},                           /* METAL */
        {DT(W_SQUARE, 36, 48, 22, 30, 90), B0, N0, F0, K0, M0, DO(SR_OFF, 0, 0, 128, 0)},   /* ZAP */
        {DT(W_SINE, 72, 0, 0, 24, 110), DB(W_SINE | B_FM, 896, 110, 16), N0, F0, K0, M0,
         DO(SR_OFF, 0, 0, 128, 0)},                                                       /* BLIP */
        {DT(W_SQUARE, 76, 0, 0, 26, 90), DB(W_SQUARE, 379, 90, 0), N0, DF(F_BP, 3, 84), K0, M0,
         DO(SR_OFF, 0, 2, 128, DR_TFILT)},                                                /* COWBELL, high */
        {DT(W_SINE, 60, 3, 14, 20, 70), DB(W_SINE, 461, 50, 0), DN(N_WHITE, 0, 160, 24), DF(F_HP, 1, 104),
         DK(150, 8, 3, 40), M0, DO(SR_OFF, 0, 2, 128, DR_HTONE)},                         /* SNARE ROLL */
    },
    {   /* MANDELA: the mandelao of Sao Paulo, bare and blown out: a distorted kick, a sub, a dirty snare and
         * clap, metal hats and anvils, the "bruxaria" (a noise that swells, a sweep as if reversed), crackle, a
         * zap, a dirty tom, a rim, a glitch, a laser */
        {DT(W_SINE, 31, 24, 16, 40, 120), DB(W_SINE, 512, 40, 26), N0, DF(F_LP, 1, 104),
         DK(120, 8, 0, 0), M0, DO(SR_OFF, 0, 6, 36, 0)},                                  /* KICK, blown out */
        {DT(W_SINE, 26, 7, 34, 52, 125), B0, N0, DF(F_LP, 0, 70), K0, M0,
         DO(SR_OFF, 0, 2, 64, 0)},                                                        /* SUB */
        {DT(W_SINE, 56, 4, 18, 26, 75), DB(W_SINE, 461, 55, 0), DN(N_WHITE, 0, 160, 32), DF(F_HP, 1, 99),
         DK(140, 8, 0, 0), M0, DO(SR_OFF, 0, 6, 70, 0)},                                  /* SNARE, dirty */
        {T0, B0, DN(N_WHITE, 0, 150, 30), DF(F_BP, 3, 90), DK(255, 10, 3, 24), M0,
         DO(SR_16K, 3, 4, 110, DR_TAIL)},                                                 /* CLAP, crushed */
        {T0, B0, DN(MTL(1), 62, 200, 18), DF(F_HP, 1, 118), DK(40, 6, 0, 0), M0,
         DO(SR_OFF, 0, 3, 128, DR_HAT)},                                                  /* CLOSED HAT, metal */
        {T0, B0, DN(MTL(1), 62, 190, 38), DF(F_HP, 1, 116), DK(30, 6, 0, 0), M0,
         DO(SR_OFF, 0, 3, 128, DR_HAT)},                                                  /* OPEN HAT, metal */
        {DT(W_SQUARE, 76, 0, 0, 30, 90), DB(W_SQUARE | B_RING, 589, 128, 0), DN(MTL(2), 70, 100, 26), DF(F_BP, 5, 98),
         DK(80, 6, 0, 0), M0, DO(SR_OFF, 0, 4, 128, DR_TFILT)},                           /* ANVIL */
        {DT(W_SQUARE, 83, 0, 0, 28, 90), DB(W_SQUARE | B_RING, 589, 128, 0), DN(MTL(2), 78, 100, 24), DF(F_BP, 5, 104),
         DK(80, 6, 0, 0), M0, DO(SR_OFF, 0, 4, 128, DR_TFILT)},                           /* ANVIL, high */
        {T0, B0, DN(N_WHITE, 0, 230, 46), DF(F_BP, 6, 90), K0, DM(30, 0, 0),
         DO(SR_OFF, 0, 4, 128, 0)},                                                       /* BRUXARIA: it swells */
        {DT(W_SAW, 48, 24, 40, 46, 120), B0, N0, DF(F_LP, 4, 90), K0, DM(30, 0, 0),
         DO(SR_OFF, 0, 3, 128, DR_TFILT | DR_FSWEEP)},                                    /* SWEEP, as if reversed */
        {DT(W_SINE, 24, 0, 0, 46, 20), B0, DN(N_CRACKLE, 4, 255, 46), DF(F_BP, 2, 100), K0, M0,
         DO(SR_8K, 3, 3, 128, 0)},                                                        /* CRACKLE */
        {DT(W_SQUARE, 40, 48, 22, 30, 90), B0, N0, F0, K0, M0, DO(SR_8K, 3, 2, 128, 0)},   /* ZAP, crushed */
        {DT(W_TRI, 45, 14, 26, 36, 115), B0, DN(N_WHITE, 0, 30, 20), DF(F_LP, 1, 96),
         DK(30, 8, 0, 0), M0, DO(SR_OFF, 0, 6, 90, 0)},                                   /* TOM, dirty */
        {DT(W_TRI, 88, 0, 0, 12, 110), DB(W_SINE, 832, 80, 10), N0, DF(F_BP, 4, 103),
         DK(80, 6, 0, 0), M0, DO(SR_OFF, 0, 7, 100, 0)},                                  /* RIM, dirty */
        {T0, B0, DN(N_LFSR7, 131, 130, 26), F0, K0, M0, DO(SR_8K, 4, 2, 128, 0)},       /* GLITCH */
        {DT(W_TRI, 60, 36, 30, 38, 110), B0, N0, F0, K0, M0, DO(SR_OFF, 0, 3, 128, 0)},  /* LASER */
    },
    {   /* BREGA: the brega funk of Recife: a dry kick and a round one, a snare, palms doubled, hats, the
         * timbales, toms, a cowbell, a rim, a shaker, a tambourine, a snap, a crash */
        {DT(W_SINE, 35, 12, 16, 30, 120), DB(W_SINE, 512, 30, 20), N0, DF(F_LP, 1, 96),
         DK(110, 6, 0, 0), M0, DO(SR_OFF, 0, 2, 120, 0)},                                 /* KICK, dry */
        {DT(W_SINE, 31, 10, 22, 40, 125), DB(W_SINE, 512, 25, 30), N0, DF(F_LP, 1, 87),
         DK(70, 10, 0, 0), M0, DO(SR_OFF, 0, 2, 84, 0)},                                  /* KICK, round */
        {DT(W_SINE, 57, 3, 16, 24, 70), DB(W_SINE, 410, 40, 0), DN(N_WHITE, 0, 150, 32), DF(F_BP, 2, 98),
         DK(150, 10, 0, 0), M0, DO(SR_OFF, 0, 4, 128, 0)},                                /* SNARE */
        {T0, B0, DN(N_WHITE, 0, 140, 30), DF(F_BP, 3, 92), DK(255, 10, 1, 90), M0,
         DO(SR_OFF, 0, 1, 128, DR_TAIL)},                                                 /* PALMS, doubled */
        {DT(W_SQUARE, 105, 0, 0, 16, 25), DB(W_SQUARE | B_RING, 361, 128, 0), DN(N_WHITE, 0, 160, 18), DF(F_HP, 0, 118),
         DK(60, 8, 0, 0), M0, DO(SR_OFF, 0, 0, 128, DR_HAT | DR_TFILT)},                  /* CLOSED HAT */
        {DT(W_SQUARE, 105, 0, 0, 36, 25), DB(W_SQUARE | B_RING, 361, 128, 0), DN(N_WHITE, 0, 150, 38), DF(F_HP, 0, 117),
         DK(50, 8, 0, 0), M0, DO(SR_OFF, 0, 0, 128, DR_HAT | DR_TFILT)},                  /* OPEN HAT */
        {DT(W_SINE, 62, 1, 30, 38, 100), DB(W_SINE | B_RING, 699, 60, 30), N0, DF(F_BP, 2, 102),
         DK(120, 8, 0, 0), M0, DO(SR_OFF, 0, 1, 128, 0)},                                 /* TIMBAL, low */
        {DT(W_SINE, 67, 1, 30, 38, 100), DB(W_SINE | B_RING, 699, 60, 30), N0, DF(F_BP, 2, 107),
         DK(120, 8, 0, 0), M0, DO(SR_OFF, 0, 1, 128, 0)},                                 /* TIMBAL, high */
        {DT(W_SINE, 47, 6, 30, 36, 120), DB(W_SINE, 407, 30, 30), N0, DF(F_BP, 2, 98),
         DK(70, 8, 0, 0), M0, DO(SR_OFF, 0, 1, 128, 0)},                                  /* LOW TOM */
        {DT(W_SINE, 54, 6, 30, 34, 120), DB(W_SINE, 407, 30, 28), N0, DF(F_BP, 2, 101),
         DK(70, 8, 0, 0), M0, DO(SR_OFF, 0, 1, 128, 0)},                                  /* HIGH TOM */
        {DT(W_PULSE, 66, 0, 0, 30, 110), DB(W_SQUARE, 379, 100, 0), N0, DF(F_BP, 2, 84), DK(60, 6, 0, 0), M0,
         DO(SR_OFF, 0, 1, 128, DR_TFILT)},                                                /* COWBELL */
        {DT(W_SINE, 56, 2, 18, 28, 80), DB(W_SINE, 691, 70, 30), DN(N_WHITE, 0, 90, 32), DF(F_BP, 2, 104),
         DK(150, 10, 0, 0), M0, DO(SR_OFF, 0, 4, 128, 0)},                                /* RIMSHOT */
        {T0, B0, DN(N_WHITE, 0, 190, 24), DF(F_HP, 2, 113), K0, DM(18, 0, 0), DO(SR_OFF, 0, 0, 128, 0)},      /* SHAKER */
        {T0, B0, DN(MTL(2), 86, 180, 40), DF(F_HP, 1, 112), DK(120, 10, 2, 30), M0,
         DO(SR_OFF, 0, 0, 128, 0)},                                                       /* TAMBOURINE */
        {T0, B0, DN(N_WHITE, 0, 40, 22), DF(F_BP, 5, 94), DK(220, 10, 1, 6), M0, DO(SR_OFF, 0, 2, 128, 0)},   /* SNAP */
        {DT(W_SQUARE, 92, 0, 0, 44, 30), DB(W_SQUARE | B_RING, 443, 128, 0), DN(N_WHITE, 0, 120, 46), DF(F_BP, 0, 110),
         DK(70, 14, 0, 0), M0, DO(SR_OFF, 0, 1, 128, DR_TFILT)},                          /* CRASH, dark */
    },
    {   /* MELODY: the funk melody of the 2000s, a clean drum machine, bright: kicks, a snare and clap, hats,
         * toms, a ride, a crash, a rim, a tambourine, a shaker, a cowbell, a clave, a bell */
        {DT(W_SINE, 34, 19, 18, 36, 115), DB(W_SINE, 768, 30, 20), N0, DF(F_BP, 2, 103),
         DK(110, 8, 0, 0), M0, DO(SR_32K, 2, 2, 128, 0)},                                 /* KICK */
        {DT(W_SINE, 38, 16, 14, 30, 125), DB(W_SINE, 1024, 30, 14), N0, DF(F_BP, 2, 108),
         DK(140, 6, 0, 0), M0, DO(SR_32K, 2, 1, 110, 0)},                                /* KICK, short and bright */
        {DT(W_SINE, 59, 5, 16, 24, 70), DB(W_SINE, 435, 40, 0), DN(N_WHITE, 0, 170, 32), DF(F_HP, 1, 105),
         DK(150, 8, 0, 0), M0, DO(SR_32K, 2, 2, 128, 0)},                                 /* SNARE */
        {T0, B0, DN(N_WHITE, 0, 140, 32), DF(F_BP, 2, 90), DK(230, 10, 2, 24), M0,
         DO(SR_32K, 2, 1, 128, DR_TAIL)},                                                 /* CLAP */
        {DT(W_SQUARE, 101, 0, 0, 16, 20), DB(W_SQUARE | B_RING, 379, 128, 0), DN(N_WHITE, 0, 120, 21), DF(F_BP, 1, 116),
         DK(60, 8, 0, 0), M0, DO(SR_32K, 3, 0, 128, DR_HAT | DR_TFILT)},                  /* CLOSED HAT */
        {DT(W_SQUARE, 101, 0, 0, 34, 20), DB(W_SQUARE | B_RING, 379, 128, 0), DN(N_WHITE, 0, 120, 37), DF(F_BP, 1, 115),
         DK(50, 8, 0, 0), M0, DO(SR_32K, 3, 0, 128, DR_HAT | DR_TFILT)},                  /* OPEN HAT */
        {DT(W_SINE, 41, 1, 40, 50, 115), DB(W_SINE, 384, 50, 46), N0, DF(F_LP, 1, 72),
         DK(50, 12, 0, 0), DM(4, 0, 0), DO(SR_32K, 2, 0, 128, 0)},                        /* LOW TOM, deep */
        {DT(W_SINE, 48, 1, 40, 48, 115), DB(W_SINE, 384, 50, 44), N0, DF(F_LP, 1, 76),
         DK(50, 12, 0, 0), DM(4, 0, 0), DO(SR_32K, 2, 0, 128, 0)},                        /* HIGH TOM */
        {DT(W_SINE, 100, 0, 0, 44, 30), DB(W_SINE | B_FM, 361, 60, 34), DN(MTL(3), 74, 170, 48), DF(F_BP, 3, 112),
         DK(40, 8, 0, 0), M0, DO(SR_OFF, 0, 0, 128, 0)},                                  /* RIDE */
        {DT(W_SQUARE, 94, 0, 0, 46, 40), DB(W_SQUARE | B_RING, 443, 128, 0), DN(N_WHITE, 0, 120, 48), DF(F_HP, 0, 105),
         DK(90, 14, 0, 0), M0, DO(SR_32K, 2, 0, 128, DR_TFILT)},                          /* CRASH */
        {DT(W_SINE, 74, 0, 0, 14, 110), DB(W_SINE, 742, 40, 10), N0, DF(F_BP, 4, 93),
         DK(40, 6, 0, 0), M0, DO(SR_32K, 2, 2, 128, 0)},                                  /* RIM */
        {T0, B0, DN(MTL(2), 84, 140, 34), DF(F_HP, 1, 112), DK(90, 12, 2, 40), M0,
         DO(SR_32K, 2, 0, 128, 0)},                                                       /* TAMBOURINE */
        {T0, B0, DN(N_WHITE, 0, 200, 28), DF(F_BP, 2, 107), K0, DM(20, 0, 0), DO(SR_32K, 2, 0, 128, 0)},      /* SHAKER */
        {DT(W_SQUARE, 70, 0, 0, 28, 90), DB(W_SQUARE, 379, 90, 0), N0, DF(F_BP, 3, 78), K0, M0,
         DO(SR_32K, 2, 1, 128, DR_TFILT)},                                                /* COWBELL */
        {DT(W_SINE, 96, 0, 0, 20, 130), DB(W_SINE, 351, 20, 18), N0, F0, K0, M0, DO(SR_32K, 2, 1, 128, 0)},   /* CLAVE */
        {DT(W_SINE, 96, 0, 0, 46, 90), DB(W_SINE | B_FM, 896, 70, 30), N0, F0, K0, M0,
         DO(SR_32K, 2, 0, 128, 0)},                                                       /* BELL */
    },
    {   /* TUIN: the effects of the baile: kicks, a snare, a clap and hats, then the sirens, the whistle, the
         * "tuin" (a pitch that falls), a laser, the shot, an explosion, vinyl, a scratch, a noise that rises */
        {DT(W_SINE, 32, 20, 16, 36, 120), DB(W_TRI, 1536, 40, 12), N0, DF(F_LP, 1, 104),
         DK(130, 6, 0, 0), M0, DO(SR_OFF, 0, 2, 92, 0)},                                  /* KICK, with a click */
        {DT(W_SINE, 28, 18, 30, 52, 125), DB(W_SINE, 512, 20, 40), DN(N_WHITE, 0, 30, 30), DF(F_LP, 1, 78),
         DK(60, 10, 0, 0), M0, DO(SR_OFF, 0, 2, 76, 0)},                                  /* BOOM, deep */
        {DT(W_SINE, 55, 6, 18, 28, 80), DB(W_SINE, 461, 50, 0), DN(N_WHITE, 0, 170, 36), DF(F_BP, 1, 102),
         DK(170, 8, 0, 0), M0, DO(SR_OFF, 0, 4, 120, 0)},                                 /* SNARE */
        {T0, B0, DN(N_WHITE, 0, 130, 36), DF(F_BP, 2, 82), DK(230, 10, 3, 30), M0,
         DO(SR_OFF, 0, 2, 128, DR_TAIL)},                                                 /* CLAP, wide */
        {T0, B0, DN(N_LFSR15, 0, 140, 18), DF(F_HP, 1, 116), DK(40, 6, 0, 0), M0,
         DO(SR_OFF, 0, 1, 128, DR_HAT)},                                                  /* CLOSED HAT */
        {T0, B0, DN(N_LFSR15, 0, 130, 38), DF(F_HP, 1, 114), DK(30, 6, 0, 0), M0,
         DO(SR_OFF, 0, 1, 128, DR_HAT)},                                                  /* OPEN HAT */
        {DT(W_TRI, 72, -12, 40, 50, 110), B0, N0, F0, K0, DM(22, 112, 20), DO(SR_OFF, 0, 0, 128, 0)},   /* SIREN */
        {DT(W_SQUARE, 74, -12, 44, 50, 90), B0, N0, DF(F_LP, 2, 100), K0, DM(10, 64, 12),
         DO(SR_OFF, 0, 1, 128, DR_TFILT)},                                                /* SIREN, square */
        {DT(W_SINE, 98, 0, 0, 36, 120), B0, N0, F0, K0, DM(4, 24, 120), DO(SR_OFF, 0, 0, 110, 0)},   /* WHISTLE */
        {DT(W_SINE, 60, 36, 34, 36, 120), B0, N0, F0, K0, M0, DO(SR_OFF, 0, 1, 128, 0)},   /* TUIN: down it falls */
        {DT(W_SQUARE, 55, 48, 26, 32, 90), B0, N0, DF(F_LP, 3, 104), K0, M0,
         DO(SR_OFF, 0, 1, 128, DR_TFILT | DR_FSWEEP)},                                    /* LASER */
        {DT(W_SINE, 40, 24, 12, 30, 100), B0, DN(N_WHITE, 0, 220, 38), DF(F_LP, 1, 100),
         DK(255, 8, 0, 0), M0, DO(SR_OFF, 0, 4, 64, 0)},                                  /* SHOT */
        {DT(W_SINE, 30, 12, 30, 50, 110), B0, DN(N_WHITE, 0, 220, 50), DF(F_LP, 2, 90),
         DK(120, 10, 0, 0), M0, DO(SR_OFF, 0, 1, 48, DR_FSWEEP)},                         /* EXPLOSION */
        {DT(W_SINE, 23, 0, 0, 52, 20), B0, DN(N_CRACKLE, 1, 255, 52), DF(F_BP, 2, 100), K0, M0,
         DO(SR_OFF, 0, 0, 128, 0)},                                                       /* VINYL */
        {DT(W_SAW, 62, 0, 0, 36, 90), B0, DN(N_WHITE, 0, 30, 30), DF(F_BP, 4, 86), K0, DM(14, 160, 24),
         DO(SR_OFF, 0, 2, 128, DR_TFILT)},                                                /* SCRATCH */
        {T0, B0, DN(N_WHITE, 0, 240, 48), DF(F_BP, 4, 100), K0, DM(32, 0, 0), DO(SR_OFF, 0, 3, 128, 0)},   /* RISE */
    },
    {   /* PERCUS: the Brazilian percussion: atabaques (low, high, the slap), the surdo, the chocalho, the
         * pandeiro, the tamborim, the snare of the bloco, agogo bells, the cuica (low, high), the reco-reco, a
         * triangle, the whistle, the ganza */
        {DT(W_SINE, 50, 2, 28, 36, 125), DB(W_SINE, 407, 30, 28), N0, DF(F_LP, 1, 90),
         DK(60, 10, 0, 0), M0, DO(SR_OFF, 0, 1, 128, 0)},                                 /* ATABAQUE, low */
        {DT(W_SINE, 58, 2, 24, 32, 125), DB(W_SINE, 407, 30, 24), N0, DF(F_BP, 3, 99),
         DK(70, 8, 0, 0), M0, DO(SR_OFF, 0, 1, 128, 0)},                                  /* ATABAQUE, high */
        {DT(W_SINE, 63, 0, 0, 16, 70), B0, DN(N_WHITE, 0, 90, 20), DF(F_BP, 4, 104),
         DK(220, 12, 0, 0), M0, DO(SR_OFF, 0, 3, 128, 0)},                                /* SLAP */
        {DT(W_SINE, 38, 3, 36, 46, 125), DB(W_SINE, 407, 25, 36), DN(N_WHITE, 0, 16, 28), DF(F_LP, 1, 80),
         DK(70, 12, 0, 0), M0, DO(SR_OFF, 0, 1, 128, 0)},                                 /* SURDO */
        {T0, B0, DN(N_WHITE, 0, 230, 22), DF(F_BP, 3, 117), DK(0, 0, 1, 40), DM(14, 0, 0),
         DO(SR_OFF, 0, 0, 128, DR_HTONE)},                                                /* CHOCALHO */
        {DT(W_SINE, 62, 2, 20, 26, 90), B0, DN(MTL(2), 86, 160, 34), DF(F_HP, 1, 108), DK(120, 10, 1, 30), M0,
         DO(SR_OFF, 0, 0, 128, 0)},                                                       /* PANDEIRO */
        {DT(W_SINE, 76, 2, 14, 20, 120), DB(W_SINE | B_RING, 699, 40, 18), DN(N_WHITE, 0, 40, 16), DF(F_BP, 3, 110),
         DK(160, 6, 0, 0), M0, DO(SR_OFF, 0, 2, 128, 0)},                                 /* TAMBORIM */
        {DT(W_SINE, 62, 2, 16, 22, 60), DB(W_SINE, 410, 40, 0), DN(N_WHITE, 0, 170, 30), DF(F_BP, 2, 112),
         DK(150, 8, 2, 14), M0, DO(SR_OFF, 0, 1, 128, 0)},                                /* CAIXA, the bloco's */
        {DT(W_SINE, 79, 0, 0, 42, 120), DB(W_SINE | B_FM, 691, 40, 26), N0, DF(F_HP, 1, 100), DK(40, 6, 0, 0), M0,
         DO(SR_OFF, 0, 0, 128, 0)},                                                       /* AGOGO, low */
        {DT(W_SINE, 84, 0, 0, 40, 120), DB(W_SINE | B_FM, 691, 40, 26), N0, DF(F_HP, 1, 104), DK(40, 6, 0, 0), M0,
         DO(SR_OFF, 0, 0, 128, 0)},                                                       /* AGOGO, high */
        {DT(W_SINE, 64, -5, 20, 28, 120), DB(W_SINE, 512, 30, 20), N0, DF(F_BP, 2, 98), K0, DM(4, 40, 16),
         DO(SR_OFF, 0, 4, 128, DR_TFILT)},                                                /* CUICA, low */
        {DT(W_SINE, 74, -7, 20, 26, 120), DB(W_SINE, 512, 30, 18), N0, DF(F_BP, 2, 104), K0, DM(4, 40, 16),
         DO(SR_OFF, 0, 4, 128, DR_TFILT)},                                                /* CUICA, high */
        {T0, B0, DN(N_WHITE, 0, 30, 36), DF(F_BP, 6, 103), DK(200, 8, 14, 30), M0,
         DO(SR_OFF, 0, 1, 128, 0)},                                                       /* RECO-RECO */
        {DT(W_SINE, 93, 0, 0, 52, 90), DB(W_SINE | B_FM, 955, 30, 40), N0, DF(F_HP, 1, 117), DK(40, 6, 0, 0), M0,
         DO(SR_OFF, 0, 0, 128, 0)},                                                       /* TRIANGLE */
        {DT(W_SINE, 100, 0, 0, 34, 120), B0, N0, F0, K0, DM(4, 20, 100), DO(SR_OFF, 0, 0, 110, 0)},   /* WHISTLE */
        {T0, B0, DN(N_WHITE, 0, 230, 30), DF(F_HP, 2, 116), DK(0, 0, 1, 20), DM(12, 0, 0),
         DO(SR_OFF, 0, 0, 128, DR_HTONE)},                                                /* GANZA */
    }};
#undef DT
#undef DB
#undef DN
#undef DF
#undef DK
#undef DM
#undef DO
#undef T0
#undef B0
#undef N0
#undef F0
#undef K0
#undef M0
#undef MTL
