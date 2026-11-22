/* SPDX-License-Identifier: GPL-3.0-only */
/* KAWA: names, parameter descriptions, factory sounds, themes, chords, scales, the live effects and the
 * magic tools. Text on the screen is upper case without accents (the font is ASCII), in three languages:
 * French, English, Spanish (OPTIONS, KNOB 2). Tables hold [3] names in that order. */

enum { LANG_PT, LANG_EN, LANG_ES, LANG_N };    /* BAILE: Portuguese in KAWA's first slot (its French) */
static uint8_t lang = LANG_PT;                  /* the screen's language (the settings sector) */
#define TR(pt, en, es) (lang == LANG_EN ? (en) : lang == LANG_ES ? (es) : (pt))
static int32_t clampi(int32_t v, int32_t lo, int32_t hi) { return v < lo ? lo : v > hi ? hi : v; }
static const char *const LANG_CODE[LANG_N] = {"PT", "EN", "ES"};

/* ---- engines: each of the eight tracks plays one, picked with its sound (SOUND, PRESETS) */
#define NUSR 4u                                /* the user's sample slots (kawa_core.c) */
#define NTRK 6u                                /* six tracks: the FM-1's audio interrupt keeps a wide margin */
enum { E_PULSE, E_WAVE, E_NOISE, E_FM, E_KIT, E_SAMPLE, E_N };
static const char *const ENGINE_NAMES[LANG_N][E_N] = {{"PULSO", "ONDA", "RUIDO", "FM", "KIT", "SAMPLE"},
                                                      {"PULSE", "WAVE", "NOISE", "FM", "KIT", "SAMPLE"},
                                                      {"PULSO", "ONDA", "RUIDO", "FM", "KIT", "SAMPLE"}};
#define ENGINE_NAME ENGINE_NAMES[lang]
static const uint8_t ENGINE_ICON[E_N] = {ICO_PULSE, ICO_WAVE, ICO_NOISE, ICO_FM, ICO_KIT, ICO_SAMPLE};

/* ---- themes (OPTIONS, KNOB 1): the screen's colours. BAILE's are from its mood board (docs/moodboard): a black
 * floor and the six colours of a macaw's feathers, one a track, red to blue. TERRA is the default */
typedef struct {
    const char *name;
    uint16_t bg, bg2, beat, rule, faint, mid, txt, gold, rec, go, ink;   /* ink: text on a lit tile */
    uint16_t trk[NTRK];
} theme_t;
static const theme_t THEMES[3] = {
    {"TERRA", RGB(20, 18, 16), RGB(30, 26, 22), RGB(42, 36, 30), RGB(58, 51, 43), RGB(110, 101, 90), RGB(156, 145, 132),
     RGB(243, 235, 221), RGB(255, 207, 31), RGB(227, 33, 43), RGB(90, 174, 58), RGB(20, 18, 16),
     {RGB(227, 33, 43), RGB(242, 106, 27), RGB(255, 207, 31), RGB(90, 174, 58), RGB(20, 163, 168), RGB(52, 112, 230)}},
    {"CLARO", RGB(243, 235, 221), RGB(232, 222, 206), RGB(220, 208, 190), RGB(200, 186, 166), RGB(150, 138, 122),
     RGB(100, 90, 78), RGB(20, 18, 16), RGB(214, 92, 20), RGB(200, 20, 30), RGB(40, 130, 40), RGB(20, 18, 16),
     {RGB(210, 30, 40), RGB(230, 95, 20), RGB(225, 165, 0), RGB(60, 150, 40), RGB(10, 140, 145), RGB(30, 85, 200)}},
    {"PAREDAO", RGB(0, 0, 0), RGB(14, 14, 14), RGB(30, 30, 30), RGB(48, 48, 48), RGB(110, 110, 110), RGB(170, 170, 170),
     RGB(255, 255, 255), RGB(255, 207, 31), RGB(255, 26, 26), RGB(90, 220, 70), RGB(0, 0, 0),
     {RGB(255, 40, 40), RGB(255, 120, 30), RGB(255, 215, 40), RGB(110, 220, 70), RGB(30, 210, 215), RGB(80, 140, 255)}},
};
#define NTHEME 3u
static uint8_t theme;
static uint16_t C_BG, C_BG2, C_BEAT, C_RULE, C_FAINT, C_MID, C_TXT, C_GOLD, C_REC, C_GO, C_INK;
static uint16_t TRK_COL[NTRK];
static void theme_set(uint32_t k)
{
    const theme_t *t = &THEMES[k % NTHEME];
    uint32_t i;
    theme = (uint8_t)(k % NTHEME);
    C_BG = t->bg; C_BG2 = t->bg2; C_BEAT = t->beat; C_RULE = t->rule; C_FAINT = t->faint; C_MID = t->mid;
    C_TXT = t->txt; C_GOLD = t->gold; C_REC = t->rec; C_GO = t->go; C_INK = t->ink;
    for (i = 0; i < NTRK; i++)
        TRK_COL[i] = t->trk[i];
}
/* one knob, one colour: KNOB 1..4 everywhere (the cards, the bottom line, the emulator's rings) */
static const uint16_t KNOB_COL[4] = {RGB(255, 92, 92), RGB(255, 204, 64), RGB(92, 226, 116), RGB(84, 164, 255)};
/* one page, one colour (the page's pill, the emulator's buttons) */
enum { PG_TRACK, PG_GRID, PG_SOUND, PG_ENV, PG_MIX, PG_MAGIC, PG_SCALE, PG_SONG, PG_PROJ, PG_OPT, PG_FX, PG_HELP, PG_BOOT,
       PG_GROOVE, PG_SEND, PG_FILT, PG_FXSEQ, PG_N };                       /* (GROOVE last: the emulator knows the others by their number) */
/* the pages' colours: the macaw's feathers (a little lighter, for dark text on them) */
#define F_RED RGB(235, 60, 60)
#define F_ORA RGB(245, 120, 40)
#define F_YEL RGB(255, 207, 31)
#define F_GRN RGB(100, 190, 70)
#define F_TUR RGB(30, 185, 190)
#define F_BLU RGB(70, 130, 240)
static const uint16_t PAGE_COL[PG_N] = {F_BLU, F_RED, F_TUR, F_GRN, F_ORA, F_YEL, F_GRN, F_ORA, F_BLU, F_ORA, F_RED,
                                        F_BLU, F_BLU, F_ORA, F_RED, F_RED, F_TUR};

/* ---- the 24 parameters of a track: SOUND 1, SOUND 2 (the engine's), ENVELOPE, MIX, EFFECT, LFO */
#define NPARAM 28u
enum { P_S0, P_S1, P_S2, P_S3, P_S4, P_S5, P_S6, P_S7, P_ATT, P_DEC, P_SUS, P_REL, P_VOL, P_PAN, P_ECHO, P_VERB,
       P_FXT, P_FXA, P_FXB, P_FXM, P_LFOD, P_LFOR, P_LFOA, P_LFOW, P_MENVA, P_MVELA, P_MENVP, P_MLFRT };
/* SOUND for PULSE / WAVE / NOISE */
enum { P_SHAPE = 0, P_SWEEP, P_VIB, P_TON, P_CRUSH, P_DETUNE, P_ARPV, P_GLIDE };
/* FM */
enum { P_FMPAT = 0, P_FMALG, P_FMRAT, P_FMFB, P_FMBRI, P_FMMEG, P_FMDET, P_FMVIB };
/* KIT */
enum { P_KIT = 0, P_TUNE, P_DECAY, P_DRIVE, P_KCRUSH, P_KTON };
/* SAMPLE */
enum { P_SRC = 0, P_SMODE, P_STUNE, P_FIT, P_LEN, P_SDRIVE, P_SCRUSH, P_STON };
enum { K_NUM, K_SIGN, K_LIST, K_NAMES, K_PAN, K_MS, K_SRC };   /* K_LIST: n values x 3 languages, flat */
typedef struct {
    const char *name[LANG_N];
    int8_t lo, hi;
    uint8_t kind;
    const char *const *list;
} pdesc_t;
static const char *const L_DUTY[] = {"12%", "25%", "50%", "75%", "PWM", "12%", "25%", "50%", "75%", "PWM",
                                     "12%", "25%", "50%", "75%", "PWM"};
static const char *const L_WAVE[] = {"TRI", "SERRA", "SENO", "SUAVE", "GB", "ORGAO", "VOZ", "FM",
                                     "TRI", "SAW", "SINE", "SOFT", "GB", "ORGAN", "VOICE", "FM",
                                     "TRI", "SIERRA", "SENO", "SUAVE", "GB", "ORGANO", "VOZ", "FM"};
static const char *const L_NOISE[] = {"LONGO", "METAL", "LONG", "METAL", "LARGO", "METAL"};
static const char *const L_DUR[] = {"1/4", "1/2", "3/4", "1", "1.5", "2", "3", "4", "6", "8", "12", "TUDO",
                                    "1/4", "1/2", "3/4", "1", "1.5", "2", "3", "4", "6", "8", "12", "ALL",
                                    "1/4", "1/2", "3/4", "1", "1.5", "2", "3", "4", "6", "8", "12", "TODO"};
static const uint8_t DUR_Q[12] = {1, 2, 3, 4, 6, 8, 12, 16, 24, 32, 48, 0};   /* quarter slices, 0 = to the end */
static const char *const L_ONOFF[] = {"NAO", "SIM", "NO", "YES", "NO", "SI"};
static const char *const L_SMODE[] = {"FATIAS", "NOTAS", "SLICES", "NOTES", "CORTES", "NOTAS"};
static const char *const L_ALG[] = {"SOM", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
                                    "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32",
                                    "SOUND", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
                                    "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32",
                                    "SONIDO", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
                                    "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32"};
/* the effect of a track or of the master (EFFECT; MIX on MASTER) */
enum { FXT_OFF, FXT_LPF, FXT_HPF, FXT_BPF, FXT_DIST, FXT_CRUSH, FXT_DECIM, FXT_RING, FXT_TREM, FXT_WAH, FXT_N };
static const char *const L_FXT[] = {"NADA", "FILT GRV", "FILT AGU", "PASSA BD", "DISTOR", "ESMAGA", "DIZIMA", "ANEL", "TREMOLO", "WAH",
                                    "NONE", "LOWPASS", "HIPASS", "BANDPASS", "DRIVE", "CRUSH", "LO-FI", "RING", "TREMOLO", "WAH",
                                    "NADA", "FILT BAJ", "FILT ALT", "PASA BND", "DISTOR", "TRITURA", "DIEZMA", "ANILLO", "TREMOLO", "WAH"};
static const uint8_t FXT_ICON[FXT_N] = {ICO_ERASE, ICO_LPF, ICO_HPF, ICO_BPF, ICO_DIST, ICO_CRUSH, ICO_PIXEL, ICO_RING, ICO_TREM, ICO_WOB};
/* what the effect's A and B do, per type */
static const char *const FXA_NAMES[LANG_N][FXT_N] = {
    {"A", "CORTE", "CORTE", "CENTRO", "GANHO", "BITS", "TAXA", "FREQ", "VELOC", "VELOC"},
    {"A", "CUTOFF", "CUTOFF", "CENTER", "GAIN", "BITS", "RATE", "FREQ", "RATE", "RATE"},
    {"A", "CORTE", "CORTE", "CENTRO", "GANANC", "BITS", "TASA", "FREC", "VELOC", "VELOC"}};
static const char *const FXB_NAMES[LANG_N][FXT_N] = {
    {"B", "RESO", "RESO", "RESO", "TOM", "-", "-", "-", "PROFUND", "PROFUND"},
    {"B", "RESO", "RESO", "RESO", "TONE", "-", "-", "-", "DEPTH", "DEPTH"},
    {"B", "RESO", "RESO", "RESO", "TONO", "-", "-", "-", "PROFUND", "PROFUND"}};
/* the LFO */
enum { LFD_OFF, LFD_PITCH, LFD_VOL, LFD_FILT, LFD_PAN, LFD_SHAPE, LFD_N };
static const char *const L_LFOD[] = {"NADA", "ALTURA", "VOLUME", "EFEITO A", "PAN", "FORMA",
                                     "NONE", "PITCH", "VOLUME", "EFFECT A", "PAN", "SHAPE",
                                     "NADA", "ALTURA", "VOLUMEN", "EFECTO A", "PANEO", "FORMA"};
static const char *const L_LFOR[] = {"4 COMP", "2 COMP", "1 COMP", "1/2", "1/4", "1/8", "1/16", "1/32", "LENTO", "MEDIO", "RAPIDO",
                                     "4 BARS", "2 BARS", "1 BAR", "1/2", "1/4", "1/8", "1/16", "1/32", "SLOW", "MEDIUM", "FAST",
                                     "4 COMP", "2 COMP", "1 COMP", "1/2", "1/4", "1/8", "1/16", "1/32", "LENTO", "MEDIO", "RAPIDO"};
static const char *const L_LFOW[] = {"SENO", "TRIANG", "QUADRADA", "SERRA", "ACASO", "SINE", "TRIANGLE", "SQUARE", "SAW", "RANDOM",
                                     "SENO", "TRIANG", "CUADRADA", "SIERRA", "AZAR"};

#define PDN(pt, en, es) {pt, en, es}
#define PD_NONE {{0, 0, 0}, 0, 0, 0, 0}
#define PD_ENV {PDN("ATAQUE", "ATTACK", "ATAQUE"), 0, 15, K_MS, 0}, {PDN("QUEDA", "DECAY", "CAIDA"), 0, 15, K_MS, 0}, \
               {PDN("SUSTENT", "SUSTAIN", "SOSTEN"), 0, 15, K_NUM, 0}, {PDN("SOLTURA", "RELEASE", "SUELTA"), 0, 15, K_MS, 0}
#define PD_MIX {PDN("VOLUME", "VOLUME", "VOLUMEN"), 0, 15, K_NUM, 0}, {PDN("PAN", "PAN", "PANEO"), -7, 7, K_PAN, 0}, \
               {PDN("ECO", "ECHO", "ECO"), 0, 15, K_NUM, 0}, {PDN("REVERB", "REVERB", "REVERB"), 0, 15, K_NUM, 0}
#define PD_FX {PDN("EFEITO", "EFFECT", "EFECTO"), 0, FXT_N - 1, K_LIST, L_FXT}, {PDN("A", "A", "A"), 0, 15, K_NUM, 0}, \
              {PDN("B", "B", "B"), 0, 15, K_NUM, 0}, {PDN("MIX", "MIX", "MEZCLA"), 0, 15, K_NUM, 0}
#define PD_LFO {PDN("ALVO", "TARGET", "DESTINO"), 0, LFD_N - 1, K_LIST, L_LFOD}, {PDN("VELOC", "RATE", "VELOC"), 0, 10, K_LIST, L_LFOR}, \
               {PDN("PROFUND", "DEPTH", "PROFUND"), 0, 15, K_NUM, 0}, {PDN("ONDA", "WAVE", "ONDA"), 0, 4, K_LIST, L_LFOW}
#define PD_MOD {PDN("ENV>EFE", "ENV>FX", "ENV>EFE"), -15, 15, K_SIGN, 0}, {PDN("VEL>EFE", "VEL>FX", "VEL>EFE"), 0, 15, K_NUM, 0}, \
               {PDN("ENV>ALT", "ENV>PIT", "ENV>ALT"), -12, 12, K_SIGN, 0}, {PDN("LFO NOTA", "LFO KEY", "LFO NOTA"), 0, 1, K_LIST, L_ONOFF}
#define PD_TONAL_REST {PDN("VARRE", "SWEEP", "BARRIDO"), -15, 15, K_SIGN, 0}, {PDN("VIBRATO", "VIBRATO", "VIBRATO"), 0, 15, K_NUM, 0}, \
                      {PDN("TOM", "TONE", "TONO"), 0, 15, K_NUM, 0}, {PDN("ESMAGA", "CRUSH", "TRITURA"), 0, 7, K_NUM, 0}, \
                      {PDN("DESAFIN", "DETUNE", "DESAFIN"), 0, 15, K_NUM, 0}, {PDN("ARP VEL", "ARP SPD", "ARP VEL"), 1, 8, K_NUM, 0}, \
                      {PDN("DESLIZ", "GLIDE", "GLISA"), 0, 15, K_NUM, 0}
#define PD_SHAPE PDN("FORMA", "SHAPE", "FORMA")
static const pdesc_t PDESC[E_N][NPARAM] = {
    {{PD_SHAPE, 0, 4, K_LIST, L_DUTY}, PD_TONAL_REST, PD_ENV, PD_MIX, PD_FX, PD_LFO, PD_MOD},
    {{PD_SHAPE, 0, 7, K_LIST, L_WAVE}, PD_TONAL_REST, PD_ENV, PD_MIX, PD_FX, PD_LFO, PD_MOD},
    {{PD_SHAPE, 0, 1, K_LIST, L_NOISE}, PD_TONAL_REST, PD_ENV, PD_MIX, PD_FX, PD_LFO, PD_MOD},
    {{PDN("SOM FM", "PATCH", "SONIDO"), 0, FM_NPATCH - 1, K_NAMES, &FM_PATCH_NAME[0][0]},
     {PDN("ALGO", "ALGO", "ALGO"), 0, 32, K_LIST, L_ALG}, {PDN("RATIO", "RATIO", "RATIO"), -8, 8, K_SIGN, 0},
     {PDN("RETORNO", "FEEDBK", "RETORNO"), -7, 7, K_SIGN, 0}, {PDN("BRILHO", "BRIGHT", "BRILLO"), -15, 15, K_SIGN, 0},
     {PDN("MOD ENV", "MOD ENV", "MOD ENV"), -8, 8, K_SIGN, 0}, {PDN("DESAFIN", "DETUNE", "DESAFIN"), 0, 15, K_NUM, 0},
     {PDN("VIBRATO", "VIBRATO", "VIBRATO"), 0, 15, K_NUM, 0}, PD_ENV, PD_MIX, PD_FX, PD_LFO, PD_MOD},
    {{PDN("KIT", "KIT", "KIT"), 0, NKIT - 1, K_LIST, L_KITS}, {PDN("AFINA", "TUNE", "AFINA"), -12, 12, K_SIGN, 0},
     {PDN("QUEDA", "DECAY", "CAIDA"), -8, 8, K_SIGN, 0}, {PDN("SATURA", "DRIVE", "SATURA"), 0, 15, K_NUM, 0},
     {PDN("ESMAGA", "CRUSH", "TRITURA"), 0, 7, K_NUM, 0}, {PDN("TOM", "TONE", "TONO"), 0, 15, K_NUM, 0}, PD_NONE, PD_NONE,
     PD_ENV, PD_MIX, PD_FX, PD_LFO, PD_MOD},
    {{PDN("FONTE", "SOURCE", "FUENTE"), 0, (int8_t)(BRK_N + NUSR - 1u), K_SRC, 0}, {PDN("MODO", "MODE", "MODO"), 0, 1, K_LIST, L_SMODE},
     {PDN("AFINA", "TUNE", "AFINA"), -12, 12, K_SIGN, 0}, {PDN("AJUSTE", "FIT", "AJUSTE"), 0, 1, K_LIST, L_ONOFF},
     {PDN("DURAC", "LENGTH", "LARGO"), 0, 11, K_LIST, L_DUR}, {PDN("SATURA", "DRIVE", "SATURA"), 0, 15, K_NUM, 0},
     {PDN("ESMAGA", "CRUSH", "TRITURA"), 0, 7, K_NUM, 0}, {PDN("TOM", "TONE", "TONO"), 0, 15, K_NUM, 0},
     PD_ENV, PD_MIX, PD_FX, PD_LFO, PD_MOD},
};
/* the pages of the SOUND page (EDIT again: the next one); the FM track has two more: its operators; a SAMPLE
 * track one: its sample's edit. Every track has its TABLE last */
enum { SP_SON1, SP_SON2, SP_OP, SP_OPENV, SP_SMP, SP_FX, SP_LFO, SP_MOD, SP_TABLE, SP_N };
static const uint8_t SP_FIRST[SP_N] = {P_S0, P_S4, 0, 0, 0, P_FXT, P_LFOD, P_MENVA, 0};
static const char *const SP_NAMES[LANG_N][SP_N] = {
    {"SOM", "SOM 2", "OPERADOR", "ENV OPERAD", "SAMPLE", "EFEITO", "LFO", "MODULACAO", "TABEL"},
    {"SOUND", "SOUND 2", "OPERATOR", "OP ENVELOPE", "SAMPLE EDIT", "EFFECT", "LFO", "MODULATION", "TABLE"},
    {"SONIDO", "SONIDO 2", "OPERADOR", "ENV OPERAD", "EDITAR SAMPLE", "EFECTO", "LFO", "MODULACION", "TABLA"}};
static const uint8_t SP_LIST_FM[8] = {SP_SON1, SP_SON2, SP_OP, SP_OPENV, SP_FX, SP_LFO, SP_MOD, SP_TABLE};
static const uint8_t SP_LIST_SMP[7] = {SP_SON1, SP_SON2, SP_SMP, SP_FX, SP_LFO, SP_MOD, SP_TABLE};
static const uint8_t SP_LIST[6] = {SP_SON1, SP_SON2, SP_FX, SP_LFO, SP_MOD, SP_TABLE};
/* an FM operator's knobs (OPERATOR, OP ENV): what they change in the patch is in kawa_edit.c (op_get, op_set) */
enum { OPK_LEVEL, OPK_RATIO, OPK_FINE, OPK_DET, OPK_ATT, OPK_DEC, OPK_SUS, OPK_REL, OPK_N };
static const char *const OPK_NAMES[LANG_N][OPK_N] = {
    {"NIVEL", "RATIO", "FINO", "DESAFIN", "ATAQUE", "QUEDA", "SUSTENT", "SOLTURA"},
    {"LEVEL", "RATIO", "FINE", "DETUNE", "ATTACK", "DECAY", "SUSTAIN", "RELEASE"},
    {"NIVEL", "RATIO", "FINO", "DESAFIN", "ATAQUE", "CAIDA", "SOSTEN", "SUELTA"}};
static const int8_t OPK_LO[OPK_N] = {0, 0, 0, -7, 0, 0, 0, 0}, OPK_HI[OPK_N] = {99, 31, 99, 7, 99, 99, 99, 99};

/* ---- factory sounds: a name, SOUND 1-2 and the envelope (the mix, the effect and the LFO stay) */
typedef struct {
    const char *name[LANG_N];
    uint8_t engine;
    int8_t s[8], env[4];
} preset_t;
static const preset_t PRESETS[] = {
    {{"LEAD 25", "LEAD 25", "LEAD 25"}, E_PULSE, {1, 0, 3, 15, 0, 0, 3, 0}, {0, 6, 10, 5}},
    {{"BIP 12", "BEEP 12", "BIP 12"}, E_PULSE, {0, 0, 0, 15, 0, 0, 3, 0}, {0, 4, 0, 3}},
    {{"QUADRADA 50", "SQUARE 50", "CUADRADA 50"}, E_PULSE, {2, 0, 0, 13, 0, 0, 3, 0}, {0, 8, 12, 5}},
    {{"SUPER PULSO", "SUPER PULSE", "SUPER PULSO"}, E_PULSE, {1, 0, 2, 14, 0, 9, 3, 0}, {0, 8, 11, 6}},
    {{"PLUCK", "PLUCK", "PLUCK"}, E_PULSE, {1, 0, 0, 12, 0, 0, 3, 0}, {0, 5, 0, 4}},
    {{"LASER", "LASER", "LASER"}, E_PULSE, {0, 12, 0, 15, 0, 0, 3, 0}, {0, 7, 0, 4}},
    {{"PWM PAD", "PWM PAD", "PWM PAD"}, E_PULSE, {4, 0, 2, 11, 0, 4, 3, 0}, {7, 9, 11, 9}},
    {{"BAIXO", "BASS", "BAJO"}, E_PULSE, {2, 0, 0, 9, 0, 0, 3, 0}, {0, 7, 9, 3}},
    {{"SUJO", "DIRTY", "SUCIO"}, E_PULSE, {1, 0, 0, 15, 5, 0, 3, 0}, {0, 6, 10, 4}},
    {{"BAIXO NES", "NES BASS", "BAJO NES"}, E_WAVE, {0, 0, 0, 15, 0, 0, 3, 0}, {0, 8, 13, 3}},
    {{"BAIXO GB", "GB BASS", "BAJO GB"}, E_WAVE, {4, 0, 0, 12, 0, 0, 3, 0}, {0, 6, 10, 3}},
    {{"SERRA", "SAW", "SIERRA"}, E_WAVE, {1, 0, 2, 13, 0, 6, 3, 0}, {0, 7, 9, 5}},
    {{"FLAUTA", "FLUTE", "FLAUTA"}, E_WAVE, {2, 0, 4, 12, 0, 0, 3, 3}, {4, 8, 12, 7}},
    {{"ORGAO", "ORGAN", "ORGANO"}, E_WAVE, {5, 0, 0, 13, 0, 0, 3, 0}, {1, 9, 13, 6}},
    {{"VOZ", "VOICE", "VOZ"}, E_WAVE, {6, 0, 5, 12, 0, 3, 3, 0}, {3, 8, 11, 7}},
    {{"KICK TRI", "KICK TRI", "KICK TRI"}, E_WAVE, {0, 15, 0, 15, 0, 0, 3, 0}, {0, 4, 0, 2}},
    {{"CHIMBAL", "HI-HAT", "CHARLES"}, E_NOISE, {0, 0, 0, 15, 0, 0, 3, 0}, {0, 2, 0, 2}},
    {{"CAIXA", "SNARE", "CAJA"}, E_NOISE, {0, -3, 0, 13, 0, 0, 3, 0}, {0, 5, 0, 4}},
    {{"METAL", "METAL", "METAL"}, E_NOISE, {1, 0, 0, 15, 0, 0, 3, 0}, {0, 4, 0, 3}},
    {{"VAPOR", "STEAM", "VAPOR"}, E_NOISE, {0, 0, 0, 10, 0, 0, 3, 0}, {8, 10, 8, 9}},
    {{"EXPLOSAO", "EXPLOSION", "EXPLOSION"}, E_NOISE, {0, -8, 0, 11, 0, 0, 3, 0}, {0, 12, 0, 10}},
    {{"CRASH", "CRASH", "CRASH"}, E_NOISE, {0, 0, 0, 15, 0, 0, 3, 0}, {0, 11, 0, 10}},
    {{"PIANO TINE", "TINE EP", "PIANO TINE"}, E_FM, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 15, 15, 5}},
    {{"SINO", "BELL", "CAMPANA"}, E_FM, {1, 0, 0, 0, 0, 0, 0, 0}, {0, 15, 15, 9}},
    {{"BAIXO FM", "FM BASS", "BAJO FM"}, E_FM, {2, 0, 0, 0, 0, 0, 0, 0}, {0, 15, 15, 3}},
    {{"METAIS", "BRASS", "METALES"}, E_FM, {3, 0, 0, 0, 0, 0, 0, 0}, {0, 15, 15, 5}},
    {{"PAD", "PAD", "COLCHON"}, E_FM, {4, 0, 0, 0, 0, 0, 3, 0}, {0, 15, 15, 9}},
    {{"MARIMBA", "MARIMBA", "MARIMBA"}, E_FM, {5, 0, 0, 0, 0, 0, 0, 0}, {0, 15, 15, 5}},
    {{"ORGAO FM", "FM ORGAN", "ORGANO FM"}, E_FM, {6, 0, 0, 0, 0, 0, 0, 0}, {0, 15, 15, 4}},
    {{"VIOLAO", "PLUCK", "PUNTEO"}, E_FM, {7, 0, 0, 0, 0, 0, 0, 0}, {0, 15, 15, 4}},
    {{"LEAD CHIP", "CHIP LEAD", "LEAD CHIP"}, E_FM, {8, 0, 0, 0, 0, 0, 0, 4}, {0, 15, 15, 4}},
    {{"BAIXO ACIDO", "ACID BASS", "BAJO ACIDO"}, E_FM, {9, 0, 0, 0, 0, 0, 0, 0}, {0, 15, 15, 2}},
    {{"HOOVER", "HOOVER", "HOOVER"}, E_FM, {10, 0, 0, 0, 0, 0, 0, 0}, {0, 15, 15, 6}},
    {{"KALIMBA", "KALIMBA", "KALIMBA"}, E_FM, {11, 0, 0, 0, 0, 0, 0, 0}, {0, 15, 15, 6}},
    {{"KIT VOLT", "VOLT KIT", "KIT VOLT"}, E_KIT, {0, 0, 0, 0, 0, 14, 0, 0}, {0, 15, 15, 15}},
    {{"KIT TAMBORZAO", "TAMBORZAO KIT", "KIT TAMBORZAO"}, E_KIT, {1, 0, 0, 1, 0, 14, 0, 0}, {0, 15, 15, 15}},
    {{"KIT 150", "150 KIT", "KIT 150"}, E_KIT, {2, 0, 0, 1, 0, 15, 0, 0}, {0, 15, 15, 15}},
    {{"KIT MANDELAO", "MANDELAO KIT", "KIT MANDELAO"}, E_KIT, {3, 0, 0, 2, 0, 13, 0, 0}, {0, 15, 15, 15}},
    {{"KIT BREGA", "BREGA KIT", "KIT BREGA"}, E_KIT, {4, 0, 0, 1, 0, 14, 0, 0}, {0, 15, 15, 15}},
    {{"KIT MELODY", "MELODY KIT", "KIT MELODY"}, E_KIT, {5, 0, 0, 0, 0, 15, 0, 0}, {0, 15, 15, 15}},
    {{"KIT TUIN", "TUIN FX KIT", "KIT TUIN"}, E_KIT, {6, 0, 0, 0, 0, 15, 0, 0}, {0, 15, 15, 15}},
    {{"KIT PERCUSSAO", "BR PERC KIT", "KIT PERCUSION"}, E_KIT, {7, 0, 0, 0, 0, 15, 0, 0}, {0, 15, 15, 15}},
    {{"KIT 150 SUJO", "DIRTY 150 KIT", "KIT 150 SUCIO"}, E_KIT, {2, 2, 2, 12, 0, 13, 0, 0}, {0, 15, 15, 15}},
    {{"TAMBORZAO", "TAMBORZAO", "TAMBORZAO"}, E_SAMPLE, {0, 0, 0, 1, 11, 2, 0, 15}, {0, 15, 15, 2}},   /* atabaques */
    {{"VOLT", "VOLT", "VOLT"}, E_SAMPLE, {1, 0, 0, 1, 11, 2, 0, 15}, {0, 15, 15, 2}},            /* Miami bass, 808 */
    {{"FUNK 150", "FUNK 150", "FUNK 150"}, E_SAMPLE, {2, 0, 0, 1, 11, 2, 0, 15}, {0, 15, 15, 2}},   /* fast, hard */
    {{"MANDELAO", "MANDELAO", "MANDELAO"}, E_SAMPLE, {3, 0, 0, 1, 11, 2, 0, 15}, {0, 15, 15, 2}},   /* bare, a sub, metal */
    {{"BREGA FUNK", "BREGA FUNK", "BREGA FUNK"}, E_SAMPLE, {4, 0, 0, 1, 11, 2, 0, 15}, {0, 15, 15, 2}},   /* timbal, palms */
    {{"MONTAGEM", "MONTAGEM", "MONTAGEM"}, E_SAMPLE, {5, 0, 0, 1, 11, 2, 0, 15}, {0, 15, 15, 2}},   /* a hit every 16th */
    {{"MANDELAO SUJO", "DIRTY MANDELAO", "MANDELAO SUCIO"}, E_SAMPLE, {3, 0, 0, 1, 11, 10, 3, 12}, {0, 15, 15, 2}},
    {{"150 CURTO", "SHORT 150", "150 CORTO"}, E_SAMPLE, {2, 0, 0, 1, 3, 2, 0, 15}, {0, 15, 15, 1}},
    {{"MEU SAMPLE 1", "MY SAMPLE 1", "MI SAMPLE 1"}, E_SAMPLE, {(int8_t)(BRK_N + 0u), 1, 0, 0, 11, 0, 0, 15}, {0, 15, 15, 3}},
    {{"MEU SAMPLE 2", "MY SAMPLE 2", "MI SAMPLE 2"}, E_SAMPLE, {(int8_t)(BRK_N + 1u), 1, 0, 0, 11, 0, 0, 15}, {0, 15, 15, 3}},
    {{"MEU SAMPLE 3", "MY SAMPLE 3", "MI SAMPLE 3"}, E_SAMPLE, {(int8_t)(BRK_N + 2u), 1, 0, 0, 11, 0, 0, 15}, {0, 15, 15, 3}},
    {{"MEU SAMPLE 4", "MY SAMPLE 4", "MI SAMPLE 4"}, E_SAMPLE, {(int8_t)(BRK_N + 3u), 1, 0, 0, 11, 0, 0, 15}, {0, 15, 15, 3}},
    /* BAILE's sounds, after KAWA's (so the indices a project holds keep their sounds) */
    {{"GRAVE 808", "808 BASS", "BAJO 808"}, E_WAVE, {3, 4, 0, 10, 0, 0, 3, 6}, {0, 12, 9, 7}},       /* a punch, a slide */
    {{"GRAVE TORTO", "BENT 808", "808 TORCIDO"}, E_WAVE, {1, 3, 0, 9, 3, 2, 3, 6}, {0, 11, 10, 6}},  /* mandelao: crushed */
    {{"SUB", "SUB", "SUB"}, E_WAVE, {2, 0, 0, 6, 0, 0, 3, 0}, {0, 15, 15, 5}},
    {{"LEAD MELODY", "MELODY LEAD", "LEAD MELODY"}, E_PULSE, {1, 0, 4, 13, 0, 3, 3, 3}, {0, 8, 11, 6}},
    {{"SIRENE", "SIREN", "SIRENA"}, E_PULSE, {2, -12, 15, 14, 0, 0, 3, 0}, {6, 15, 15, 8}},
    {{"PIANO MELODY", "MELODY PIANO", "PIANO MELODY"}, E_FM, {0, 0, 0, 0, 4, 0, 0, 0}, {0, 15, 15, 6}},
    {{"STAB", "STAB", "STAB"}, E_FM, {3, 0, 0, 0, 6, 0, 0, 0}, {0, 6, 0, 3}},
};
#define KIT_DEMO 1                              /* the demo's kit (its first knob): TAMBOR */
#define BRK_DEMO 0                              /* the demo's break: TAMBOR */
#define NPRESET ((uint8_t)(sizeof(PRESETS) / sizeof(PRESETS[0])))
/* each track's sound on a new project (an index in PRESETS) */
static const uint8_t TRK_ENGINE0[NTRK] = {E_PULSE, E_FM, E_WAVE, E_NOISE, E_KIT, E_SAMPLE};   /* a new project: lead, */
static const int8_t TRK_S0[NTRK] = {1, 0, 3, 0, 1, 0};   /* FM, bass, hats, kit, break (each its engine's sound with this */
                                                          /* first knob: LEAD 25, TINE EP, GRAVE 808, HI-HAT, TAMBOR, TAMBORZAO) */

/* ---- notes */
static const char *const NOTE_NAME[12] = {"C-", "C#", "D-", "D#", "E-", "F-", "F#", "G-", "G#", "A-", "A#", "B-"};
#define NOTE_NONE 0u
#define NOTE_OFF 255u
#define KEY0 53u                                /* key 0 = F3 */
static int is_black(uint32_t note) { return (0x54Au >> (note % 12u)) & 1u; }
static int8_t WHITE_OF_KEY[27], BLACK_OF_KEY[27];    /* key -> its index among the white / black keys, or -1 */
static uint8_t KEY_OF_WHITE[16], KEY_OF_BLACK[11];
static void keys_init(void)
{
    uint32_t k, w = 0, b = 0;
    for (k = 0; k < 27u; k++) {
        WHITE_OF_KEY[k] = BLACK_OF_KEY[k] = -1;
        if (is_black(KEY0 + k)) { BLACK_OF_KEY[k] = (int8_t)b; KEY_OF_BLACK[b++] = (uint8_t)k; }
        else { WHITE_OF_KEY[k] = (int8_t)w; KEY_OF_WHITE[w++] = (uint8_t)k; }
    }
}

/* ---- the cell tricks (FX column): a type and a value */
enum { FX_NONE, FX_ARP, FX_GLIDE, FX_VIB, FX_ROLL, FX_BEND, FX_CHANCE, FX_DELAY, FX_CUT, FX_REV, FX_PITCH, FX_SHAPE,
       FX_CRUSH, FX_VSL, FX_PAN, FX_OFS, FX_HOP, FX_END, FX_N };   /* (HOP and END: the sequencer's, format 5) */
typedef struct {
    const char *tag[LANG_N];                    /* three letters */
    uint8_t icon;
    int8_t lo, hi, def;
} fxdesc_t;
static const fxdesc_t FXD[FX_N] = {
    {{"---", "---", "---"}, ICO_ERASE, 0, 0, 0},
    {{"ARP", "ARP", "ARP"}, ICO_ARP, 0, 13, 1},             /* arpeggio */
    {{"GLI", "GLI", "GLI"}, ICO_GLIDE, 1, 15, 6},           /* glide */
    {{"VIB", "VIB", "VIB"}, ICO_VIB, 1, 15, 5},             /* vibrato */
    {{"ROL", "ROL", "RED"}, ICO_ROLL, 0, 8, 2},             /* roll (redoble) */
    {{"BND", "BND", "BND"}, ICO_BEND, -15, 15, -6},         /* bend */
    {{"CHN", "CHN", "AZR"}, ICO_DICE, 1, 9, 5},             /* chance (azar) */
    {{"ATR", "DLY", "RET"}, ICO_CLOCK, 1, 23, 12},          /* delay (retard, retraso) */
    {{"CRT", "CUT", "CRT"}, ICO_CUT, 1, 23, 12},            /* cut (coupe, corte) */
    {{"INV", "REV", "REV"}, ICO_REV, 0, 0, 0},              /* reverse (envers, reves) */
    {{"ALT", "PIT", "ALT"}, ICO_SHARP, -12, 12, 12},        /* pitch (hauteur, altura) */
    {{"FOR", "SHP", "FOR"}, ICO_SHAPE, 0, 7, 0},            /* shape (forme, forma) */
    {{"ESM", "CRU", "TRI"}, ICO_CRUSH, 1, 7, 4},            /* crush (ecrase, tritura) */
    {{"VOL", "VSL", "VOL"}, ICO_VOL, -15, 15, -4},          /* volume slide over the row (an empty cell: the note playing) */
    {{"PAN", "PAN", "PAN"}, ICO_MIRROR, -7, 7, -5},         /* this note's pan */
    {{"INI", "OFS", "INI"}, ICO_RIGHT, 0, 15, 8},           /* SAMPLE: start further in (n / 16 of the slice; depart, inicio) */
    {{"PUL", "HOP", "SAL"}, ICO_LOOP, 0, 31, 0},            /* after this row, row n + 1 (saut, salto) */
    {{"FIM", "END", "FIN"}, ICO_STOP, 0, 0, 0},             /* the pattern ends after this row */
};
/* the tricks of a table's steps (TABLE): each acts on the note playing when its step comes */
enum { TB_NONE, TB_HIT, TB_CUT, TB_VIB, TB_BEND, TB_SHAPE, TB_CRUSH, TB_VSL, TB_PAN, TB_HOP, TB_N };
static const fxdesc_t TBD[TB_N] = {
    {{"---", "---", "---"}, ICO_ERASE, 0, 0, 0},
    {{"BAT", "HIT", "GOL"}, ICO_AGAIN, 0, 0, 0},            /* the note again (frappe, golpe), its step's pitch */
    {{"CRT", "CUT", "CRT"}, ICO_CUT, 0, 0, 0},              /* the note stops */
    {{"VIB", "VIB", "VIB"}, ICO_VIB, 0, 15, 5},             /* vibrato from here (0: none) */
    {{"BND", "BND", "BND"}, ICO_BEND, -15, 15, -6},         /* the pitch bends from here (0: no more) */
    {{"FOR", "SHP", "FOR"}, ICO_SHAPE, 0, 7, 0},            /* the wave's shape */
    {{"ESM", "CRU", "TRI"}, ICO_CRUSH, 0, 7, 4},            /* crush (0: none) */
    {{"VOL", "VSL", "VOL"}, ICO_VOL, -15, 15, -4},          /* the volume slides (0: it stops) */
    {{"PAN", "PAN", "PAN"}, ICO_MIRROR, -7, 7, -5},         /* the note's pan */
    {{"PUL", "HOP", "SAL"}, ICO_LOOP, 0, 15, 0},            /* to step n + 1 (after this one plays its time) */
};
static const uint8_t GROOVE_PRESET[6][17] = {   /* the groove's presets (GROOVE, KNOB 3): length, then the ticks
                                                 * (6 a 16th, 24 a beat): the funk's feels */
    {2, 6, 6}, {4, 6, 7, 5, 6}, {2, 7, 5}, {4, 6, 5, 7, 6}, {4, 7, 5, 6, 6}, {3, 4, 4, 4}};
static const char *const GROOVE_NAMES[LANG_N][6] = {   /* straight; the tamborzao's drag on the 2nd 16th; the brega's
                                                        * swing; the 150 pushing the 2nd; the mandelao lazy; triplets */
    {"RETO", "TAMBOR", "BREGA", "150", "MANDELA", "TERCINA"},
    {"STRAIGHT", "TAMBOR", "BREGA", "150", "MANDELA", "TRIPLET"},
    {"RECTO", "TAMBOR", "BREGA", "150", "MANDELA", "TRESILLO"}};
static const uint8_t ROLL_N[9] = {2, 3, 4, 6, 8, 12, 16, 24, 32};
typedef struct {
    const char *name[LANG_N];
    int8_t n, off[4];
} chord_t;
static const chord_t CHORDS[14] = {
    {{"MAI", "MAJ", "MAY"}, 3, {0, 4, 7, 0}}, {{"MEN", "MIN", "MEN"}, 3, {0, 3, 7, 0}}, {{"OCT", "OCT", "OCT"}, 2, {0, 12, 0, 0}},
    {{"5TA", "5TH", "5TA"}, 2, {0, 7, 0, 0}}, {{"SUS", "SUS", "SUS"}, 3, {0, 5, 7, 0}}, {{"7", "7", "7"}, 4, {0, 4, 7, 10}},
    {{"MA7", "MA7", "MA7"}, 4, {0, 4, 7, 11}}, {{"ME7", "MI7", "ME7"}, 4, {0, 3, 7, 10}}, {{"DIM", "DIM", "DIS"}, 3, {0, 3, 6, 0}},
    {{"AUM", "AUG", "AUM"}, 3, {0, 4, 8, 0}}, {{"2OC", "2OC", "2OC"}, 3, {0, 12, 24, 0}}, {{"AD9", "AD9", "AD9"}, 4, {0, 4, 7, 14}},
    {{"TRI", "TRL", "TRI"}, 2, {0, 1, 0, 0}}, {{"GRV", "LOW", "BAJ"}, 2, {0, -12, 0, 0}},
};

/* ---- scales (bit n: semitone n above the root) */
typedef struct {
    const char *name[LANG_N];
    uint16_t mask;
} scale_t;
static const scale_t SCALES[12] = {
    {{"CROMATICA", "CHROMATIC", "CROMATICA"}, 0xFFF}, {{"MAIOR", "MAJOR", "MAYOR"}, 0xAB5},
    {{"MENOR", "MINOR", "MENOR"}, 0x5AD}, {{"PENTA", "PENTA", "PENTA"}, 0x295},
    {{"PENTA MEN", "PENTA MIN", "PENTA MEN"}, 0x4A9}, {{"BLUES", "BLUES", "BLUES"}, 0x4E9},
    {{"DORICA", "DORIAN", "DORICA"}, 0x6AD}, {{"FRIGIA", "PHRYGIAN", "FRIGIA"}, 0x5AB},
    {{"HARMONIC", "HARMONIC", "ARMONICA"}, 0x9AD}, {{"JAPONESA", "JAPANESE", "JAPONESA"}, 0x1A3},
    {{"ARABE", "ARABIC", "ARABE"}, 0x9B3}, {{"TONS INTEI", "WHOLE TONE", "TONOS"}, 0x555},
};

/* ---- live effects: hold FX (or tap it to keep the page open), then the white keys. Two banks of 16:
 * ids 0..31 (bit id of a mask); the LIVE lane of a pattern stores id + 1 (0: none). They play on the
 * master or on one track (FX page, KNOB 4: TARGET) */
enum { LF_LOOP16, LF_LOOP12, LF_LOOP32, LF_LOOP64, LF_UNI, LF_UNILO, LF_OCTUP, LF_OCTDN,
       LF_STUT4, LF_STUT3, LF_SCR, LF_SCRF, LF_TRIP, LF_AGAIN, LF_REV, LF_ROLLUP,
       LF_CRUSH, LF_DECIM, LF_LPF, LF_HPF, LF_TAPE, LF_DIVE, LF_GATE16, LF_GATE32,
       LF_FREEZE, LF_BASS, LF_ECHO, LF_DIST, LF_WOB, LF_SIREN, LF_NOMEL, LF_NOBEAT, LF_N };   /* (BAILE: GRAVE+ for KAWA's
                                                 * RING, SIRENE for its VINYL) */
typedef struct {
    const char *name[LANG_N], *sub[LANG_N];
    uint8_t icon;
} lfx_t;
static const lfx_t LFX[LF_N] = {
    {{"LOOP", "LOOP", "BUCLE"}, {"1/16", "1/16", "1/16"}, ICO_LOOP},
    {{"LOOP", "LOOP", "BUCLE"}, {"1/12", "1/12", "1/12"}, ICO_LOOP},
    {{"LOOP", "LOOP", "BUCLE"}, {"1/32", "1/32", "1/32"}, ICO_LOOP},
    {{"LOOP", "LOOP", "BUCLE"}, {"1/64", "1/64", "1/64"}, ICO_LOOP},
    {{"UNISSON", "UNISON", "UNISONO"}, {"", "", ""}, ICO_UNI},
    {{"UNISSON", "UNISON", "UNISONO"}, {"GRV", "LOW", "GRAVE"}, ICO_UNI},
    {{"OITAVA", "OCTAVE", "OCTAVA"}, {"+1", "+1", "+1"}, ICO_UP},
    {{"OITAVA", "OCTAVE", "OCTAVA"}, {"-1", "-1", "-1"}, ICO_DOWN},
    {{"SEGURA", "STUTTER", "TARTAMU"}, {"X4", "X4", "X4"}, ICO_STUT},
    {{"SEGURA", "STUTTER", "TARTAMU"}, {"X3", "X3", "X3"}, ICO_STUT},
    {{"PUXA", "SCRATCH", "SCRATCH"}, {"", "", ""}, ICO_DISC},
    {{"PUXA", "SCRATCH", "SCRATCH"}, {"RAPIDO", "FAST", "RAPIDO"}, ICO_DISC},
    {{"6/8", "6/8", "6/8"}, {"TERCINA", "TRIPLET", "SWING"}, ICO_TRI3},
    {{"REPETE", "RETRIG", "REPITE"}, {"1 TEMPO", "1 BEAT", "1 PULSO"}, ICO_AGAIN},
    {{"AVESSO", "REVERSE", "REVES"}, {"", "", ""}, ICO_REV},
    {{"SOBE", "BUILDUP", "REDOBLE"}, {"ACELERA", "ROLL", "ACELERA"}, ICO_ACCEL},
    {{"ESMAGA", "CRUSH", "TRITURA"}, {"4 BITS", "4 BITS", "4 BITS"}, ICO_CRUSH},
    {{"DIZIMA", "LO-FI", "DIEZMA"}, {"", "RATE", ""}, ICO_PIXEL},
    {{"FILTRO", "LOWPASS", "FILTRO"}, {"GRV", "SWEEP", "GRAVES"}, ICO_LPF},
    {{"FILTRO", "HIPASS", "FILTRO"}, {"AGUDOS", "SWEEP", "AGUDOS"}, ICO_HPF},
    {{"FITA", "TAPE", "CINTA"}, {"PARA", "STOP", "PARADA"}, ICO_TAPE},
    {{"MERGULH", "DIVE", "PICADO"}, {"", "", ""}, ICO_DIVE},
    {{"CORTA", "GATE", "GATE"}, {"1/16", "1/16", "1/16"}, ICO_GATE},
    {{"CORTA", "GATE", "GATE"}, {"1/32", "1/32", "1/32"}, ICO_GATE},
    {{"CONGELA", "FREEZE", "CONGELA"}, {"", "", ""}, ICO_SNOW},
    {{"GRAVE+", "BASS+", "GRAVES+"}, {"", "", ""}, ICO_BASS},
    {{"ECO", "ECHO", "ECO"}, {"MC", "", ""}, ICO_ECHO},
    {{"DISTOR", "DISTORT", "DISTOR"}, {"", "", ""}, ICO_DIST},
    {{"WOBBLE", "WOBBLE", "WOBBLE"}, {"", "", ""}, ICO_WOB},
    {{"SIRENE", "SIREN", "SIRENA"}, {"", "", ""}, ICO_SIREN},
    {{"SEM", "NO", "SIN"}, {"MELODIA", "MELODY", "MELODIA"}, ICO_NOMEL},
    {{"SEM", "NO", "SIN"}, {"BEAT", "BEAT", "RITMO"}, ICO_NOBEAT},
};
static const char *const LBANK_NAMES[LANG_N][4] = {{"BAILE", "PAREDAO", "DESTROI", "BEAT"}, {"POCKET", "WRECK", "DESTROY", "BEAT"},
                                                   {"BOLSA", "ROTO", "DESTRUYE", "BEAT"}};   /* (DESTROY, BEAT: K-GLITCH's, kawa_kg.c) */
#define LBANK_NAME LBANK_NAMES[lang]
static const uint16_t LBANK_COL[4] = {RGB(255, 120, 200), RGB(255, 110, 70), RGB(255, 70, 90), RGB(90, 200, 255)};
#define NLBANK 4u

/* ---- the magic tools: tap LFO (MAGIE), then a white key; one undo each (SAVE held) */
enum { MG_CHOP, MG_BEAT, MG_MELO, MG_BASS, MG_MONT, MG_EUCL, MG_VARY, MG_ROLLS, MG_NUANCE, MG_DOUBLE, MG_SHIFT,
       MG_CLONE, MG_TRANSP, MG_COPY, MG_PASTE, MG_CLEAR, MG_N };
static const lfx_t MAGIC[MG_N] = {
    {{"PICADOR", "CHOPPER", "PICADOR"}, {"BREAK", "BREAK", "BREAK"}, ICO_KNIFE},
    {{"BEAT", "BEAT", "RITMO"}, {"FUNK", "FUNK", "FUNK"}, ICO_KIT},
    {{"MELODIA", "MELODY", "MELODIA"}, {"ESCALA", "SCALE", "ESCALA"}, ICO_NOTE},
    {{"GRAVE", "BASS", "BAJO"}, {"808", "808", "808"}, ICO_BASS},
    {{"MONTAGE", "MONTAGE", "MONTAJE"}, {"FATIAS", "SLICES", "CORTES"}, ICO_KNIFE},
    {{"EUCLID", "EUCLID", "EUCLIDE"}, {"N BATID", "N HITS", "GOLPES"}, ICO_EUCL},
    {{"VARIAR", "VARY", "VARIAR"}, {"UM POUC", "A BIT", "UN POCO"}, ICO_DICE},
    {{"VIRADA", "FILL", "REDOBLE"}, {"FINAL", "ENDS", "FINAL"}, ICO_ROLL},
    {{"ACENTOS", "ACCENTS", "MATICES"}, {"VOLUMES", "VOLUMES", "VOLUMEN"}, ICO_VOL},
    {{"DOBRAR", "DOUBLE", "DUPLICA"}, {"X2", "X2", "X2"}, ICO_X2},
    {{"DESLOCA", "SHIFT", "MOVER"}, {"1 PASS", "1 STEP", "1 PASO"}, ICO_RIGHT},
    {{"CLONAR", "CLONE", "CLONAR"}, {"PADRAO", "PATTERN", "PATRON"}, ICO_CLONE},
    {{"TRANSP", "TRANSP", "TRANSP"}, {"+1 NOTA", "+1 NOTE", "+1 NOTA"}, ICO_UPDN},
    {{"COPIAR", "COPY", "COPIAR"}, {"", "", ""}, ICO_COPY},
    {{"COLAR", "PASTE", "PEGAR"}, {"", "", ""}, ICO_PASTE},
    {{"APAGAR", "CLEAR", "BORRAR"}, {"", "", ""}, ICO_ERASE},
};
static const char *const L_SCOPES[LANG_N][2] = {{"FAIXA", "PADRAO"}, {"TRACK", "PATTERN"}, {"PISTA", "PATRON"}};
#define L_SCOPE L_SCOPES[lang]

/* ---- names for new projects */
static const char *const NAME_A[8] = {"BAILE", "BATIDA", "PIXEL", "TAMBOR", "GRAVE", "CHIP", "PANCADA", "MANDELA"};
static const char *const NAME_B[8] = {"ROSA", "VOLT", "NOITE", "LOUCO", "MAGICO", "TURBO", "DOCE", "SUJO"};

/* a list's value in the language (K_LIST: n values x 3 languages; K_NAMES: [3][n], here FM_PATCH_NAME) */
static const char *pd_value(const pdesc_t *d, int32_t v)
{
    uint32_t n = (uint32_t)(d->hi - d->lo + 1);
    v = clampi(v, d->lo, d->hi);
    if (d->kind == K_NAMES)
        return d->list[(uint32_t)lang * FM_NPATCH + (uint32_t)(v - d->lo)];
    return d->list[(uint32_t)lang * n + (uint32_t)(v - d->lo)];
}
