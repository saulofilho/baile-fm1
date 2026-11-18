# BAILE — plano do firmware (nome provisório)

Tracker de **funk brasileiro** para o M-VAVE FM-1: tamborzão, Volt Mix, 150 BPM, mandelão, brega funk e montagem.
Fork do [KAWA](https://github.com/Guizmoh/Kawa-Tracker-Fm1) (Omnipotard, GPL-3.0-only), que roda na plataforma
Felucca → SLOOP → Dinghy.

**Mood board:** [`docs/moodboard/index.html`](docs/moodboard/index.html) (abra no navegador). O resumo está na seção
[Mood](#mood) abaixo.

## Por que o KAWA

O KAWA já tem o que o funk pede, e o GR!MM (base do GL!TCH e do COQUÍ) não tem:

| O funk precisa de | O KAWA já tem |
| --- | --- |
| Tamborzão picotado, montagem, "puxadas" | Breaks em 16 fatias, ferramenta HACHOIR (chop), efeitos ROLL / REV / CUT / HOP por célula |
| Grave 808 que escorrega | Efeitos de célula GLI e BND, uma **TABLE** por trilha (pitch drops, ratchets) |
| O "atraso" do tamborzão | **GROOVE tables**: duração por passo, não um swing só |
| Virada de DJ ao vivo | 64 efeitos live (stutter, retrig, build-up, scratch, DESTROY e BEAT do K-GLITCH), FX sequencer |
| Paredão | Drive por trilha, sends, filtro de 11 tipos |
| Interface em português | O sistema de idiomas (`LANG_N`, hoje FR, EN e ES) |

## Decisões

| Tema | Decisão |
| --- | --- |
| Nome | **BAILE** (provisório; livre no catálogo do Hub em 2026-11-17). Alternativas: PANCADÃO, PAREDÃO, TAMBORZÃO |
| Base | KAWA **0.10**, commit `bc7dcf8` (2026-11-09), remoto `upstream`. Rebase em versões novas só por decisão |
| Gêneros da 1.0 | Funk carioca de raiz (Volt Mix / Miami bass), tamborzão, funk 150, mandelão (SP), brega funk (PE), montagem |
| Tempo | Padrão **130 BPM**; o funk 150 e o brega funk ganham projetos de fábrica no tempo deles |
| Identidade | `FM-1_971` (livre no catálogo do Hub em 2026-11-17; evitar `95x`, que é a série do KAWA). Magics próprios: projeto `BPRJ`, samples `BSMP`, ajustes `BAIL`, SysEx `BAIL`. Não lê saves do KAWA |
| Idiomas | **PT padrão**, EN e ES. O FR do KAWA sai (economiza flash; a confirmar) |
| Som | 100 % sintetizado, como no KAWA. **Nenhuma gravação de música alheia** (sem samples de Volt Mix, de MCs, de discos). Os 4 slots de sample ficam para o usuário |
| Voz de MC | Não haverá voz gravada. Fase opcional: "vocais" sintéticos curtos por formantes ("ô", "vai", "ai") |
| Visual | Estrutura do Byte Beats com um mosaico de ladrilhos pintados nas cores das penas da arara, sobre preto. Ver [Mood](#mood) |
| Hardware | Testes no simulador do KAWA (`tests/run_host.sh`) e no emulador web até haver teste no FM-1. Flash `0x856014` e `0xB36014` |
| Repositório | `projetos-git/baile-fm1`, git local. Publicar no GitHub só quando o usuário mandar |
| Licença | GPL-3.0-only, créditos em `LICENSING.md`: Omnipotard (KAWA e K-GLITCH), Felucca, SLOOP, Dinghy, msfa (Apache-2.0), fontes OFL |

## Fases

0. **Ambiente.** Rodar os testes do KAWA intacto: `tests/run_host.sh`, `run_stress_test.sh`, `run_kits_test.sh`, o
   emulador (`web/make_emulator.sh`) e o pacote (`./build.sh`, toolchain JieLi + SDK AC79 em Docker, como no COQUÍ).
   Só depois mudar código.
1. **Identidade.** `PRODUCT = "FM-1_971"` em `tools/build.py`, pacote `baile.fwsc`, `PRJ_MAGIC`/`USR_MAGIC` próprios,
   `APP_NAME`. Temas **TERRA** (padrão) e **CLARO** no lugar de KAWA, GAME BOY e BONBON. Os 16 ladrilhos e a tela
   de boot (o mosaico acendendo) em `tools/gen_art.py`. HOME com fileiras de ladrilhos animadas e o status em kaomoji. Idioma PT em toda a UI (`kawa_data.c`, `kawa_ui.c`). README e
   `LICENSING.md` novos.
2. **Bateria.** Os 8 kits viram kits de baile (16 peças cada, em `kawa_kits.h` e `kawa_drums.c`):
   - **VOLT** (808 de Miami bass: kick longo, clap, cowbell, hats)
   - **TAMBOR** (tamborzão: atabaque grave e agudo, "tum", caixa seca, palma)
   - **150** (kick curto e duro, caixa estalada, hat apertado)
   - **MANDELA** (mandelão: kick estourado, perc metálica, "bruxaria" com ruído e reverse)
   - **BREGA** (brega funk: kick seco, palma dobrada, timbal)
   - **MELODY** (funk melody dos anos 2000: kit mais limpo, ride, crash)
   - **TUIN** (efeitos de baile: sirene, apito, laser, "tuin", tiro de caixa, explosão)
   - **PERCUS** (atabaque, surdo, tamborim, agogô, cuíca, pandeiro, chocalho, caixa de guerra)
   Teste: `tests/kits_test.c` adaptado, custo por voz medido no simulador.
3. **Breaks.** Os 6 breaks de `tools/gen_breaks.py` viram 6 batidas de funk sintetizadas, um compasso cada, fatiáveis
   em 16: `TAMBOR`, `VOLT`, `CENT50`, `MANDELA`, `BREGA`, `MONTAG`. O gerador do KAWA tem BPM fixo (160): torná-lo
   por break ou confirmar que o fatiamento cobre 130–150 sem artefato. Teste: `tests/breaks_check.py`.
4. **Grooves e MAGIA.** Modelos de GROOVE com o balanço do tamborzão e do brega. Ferramentas de MAGIA novas: GERAR
   TAMBORZÃO, GERAR GRAVE (808 nos tempos do funk), **MONTAGEM** (recorta e reordena as fatias de um break), **VIRADA**
   (fill de fim de frase). Escalas: menor, frígio, menor harmônica (o "grave sinistro" do mandelão).
5. **Grave e melodia.** Sons de fábrica: GRAVE 808 (com glide e drive), GRAVE TORTO, SUB, SINO, PIANO MELODY, BRASS
   FM, "LEAD MELODY", ORQUESTRA STAB, SIRENE. Revisar os 4 patches FM próprios do KAWA (`gen_fm_patches.py`).
   Projetos de fábrica: um por gênero da 1.0 (substitui a demo do KAWA).
6. **Efeitos live de baile.** Renomear e ajustar bancos: PUXA (scratch), CORTA (mute em batida), SEGURA (stutter),
   SOBE (build-up), GRAVE+ (sub boost), ECO MC (eco de 1/8 pontuado), SIRENE (por cima do master). Os bancos DESTROY e
   BEAT do K-GLITCH ficam.
7. **Web.** Hub próprio (como o do COQUÍ: a cena do boot animada, cada gênero com grade e áudio do próprio firmware),
   emulador (`emulator/`), instalador no navegador (`install/webinstall.js`), importador de samples, manual e cheat
   sheet em **PT**, EN e ES.
8. **Release.** `./build.sh --release 1.0`, teste no FM-1 (instalar a partir do oficial V15 e de outro firmware,
   sair, voltar, update interrompido), `docs/TEST-RESULTS-1.0.md`, envio ao FM-1 Firmware Hub com `fmhub.json`.

Opcional, depois da 1.0: vocais sintéticos por formantes; modo LIVE do KAWA (lançador de chains, ideia 3 de
`source/docs/IDEES-M8-POLYEND.md`) para o DJ montar o set ao vivo.

## Andamento

- **2026-11-18, Fase 0 (no computador):** o simulador e os testes do KAWA rodam no macOS (`.venv` com Pillow na raiz;
  `PATH="$PWD/../.venv/bin:$PATH"` antes de `tests/run_host.sh`). Dois ajustes para o clang do macOS: sem seções ELF
  no build host (`gfx.c`, `platform.c`) e uma conta de ponteiro em `kawa_sysex.c`. Verdes: host, features, format,
  kits, ui, stress, `websamples_test.js`, `webinstall_test.js`. **Faltam:** o emulador web (precisa de `wasm-ld`:
  `brew install lld`) e o pacote do FM-1 (Docker parado; toolchain JieLi e SDK AC79 já estão na máquina).
- **2026-11-18, Fase 1 (parte):** identidade (`FM-1_971`, `baile.fwsc`, magics próprios, ferramentas de sample
  alinhadas; o `format_test` troca o magic dos fixtures do KAWA para seguir testando a conversão). Temas **TERRA**,
  **CLARO** e **PAREDAO** com as penas da arara; cores das páginas. Mascote: a **arara** de headphone no lugar do
  cachorro do KAWA (`tools/gen_art.py`). Boot: o **mosaico de ladrilhos** (`tools/gen_boot.py` → `art/boot-baile.png`)
  acendendo do centro para fora, "BAILE" na fonte grande (I e L acrescentados em `tools/gen_fonts.py`).
  **Falta na Fase 1:** README e `LICENSING.md` novos, tirar `art/boot-dog.png` e `art/mascot-dog.png` (não usados
  mais).
- **2026-11-18, interface em PT:** o português ocupa o lugar do francês do KAWA (`LANG_PT`, idiomas PT, EN, ES) e é
  o padrão de um FM-1 novo. 731 posições de texto (518 textos), cada uma no limite de largura do texto original;
  "track" é **FAIXA**. `tools/i18n_slots.py` acha as posições e aplica `tools/i18n_pt.json` (para revisar uma
  tradução: editar o JSON, `check`, `apply`). Nomes dos patches FM em `tools/gen_fm_patches.py`. Sem acentos: as
  fontes da tela são ASCII.

## Mood

Estrutura do **Byte Beats** (app de exemplo do Google AI Studio: cartões, pílulas, números grandes, kaomoji) com o
padrão e as cores de um **mosaico de ladrilhos pintados à mão** (referência enviada em 2026-11-18). O chão é preto;
o som é uma grade de quadrados nas cores das penas da arara (referência enviada em 2026-11-18), cada um com um símbolo geométrico em traço grosso
(espiral, losango, chevron, zigue-zague, listras, pontos, sol, alvo, trama…), com juntas pretas entre eles. Liga com a
raiz do tamborzão no atabaque. Cada trilha é uma fileira de ladrilhos: **muda, só o contorno no escuro; tocando,
acende e troca de símbolo no tempo**.

- **Paleta:** preto `#141210` (chão, juntas, traço), carvão `#1E1A16` / `#2A241E` (ladrilho apagado, cartões), creme
  `#F3EBDD` (texto), cinza `#9C9184` (legendas) e as **penas da arara**, na ordem do degradê: vermelho `#E3212B`, laranja `#F26A1B`, amarelo
  `#FFCF1F`, verde `#5AAE3A`, turquesa `#14A3A8`, azul `#1F5BD6`. Uma cor por trilha, nessa ordem. Destaque em
  amarelo, REC em vermelho, PLAY em verde.
- **Biblioteca de 16 símbolos:** cada peça do kit e cada efeito live tem o seu ladrilho, sempre o mesmo. No FM-1,
  bitmaps gerados por `tools/gen_art.py`.
- **Temas no FM-1:** **TERRA** (padrão: preto) e **CLARO** (creme, para luz do dia).
- **Boot:** o mosaico acende em onda, do centro para fora, até a faixa preta com "BAILE".
- **HOME:** as 6 trilhas como cartões com uma fileira de ladrilhos; faixa na cor da trilha selecionada.
- **Status em kaomoji**, pelo número de trilhas tocando: `(-_- )` PARADO, `(o_O )` ESQUENTANDO, `(⌐■_■)` NO GRAVE,
  `( ✧Д✧)` PAREDÃO.
- **Tipografia:** título preto e pesado (Archivo Black no hub; imagem no boot), rótulos grossos em caixa alta,
  legendas mono cinza espaçadas. No FM-1, as fontes do KAWA com acentos.
- **Hub e editor web:** fundo preto, uma faixa de mosaico animado no topo, botões em pílula, XY pads e faders com
  número grande.
- **Regras:** cor é som; feito à mão (traço grosso, quadrados imperfeitos); símbolos geométricos, nada copiado de um
  povo ou rito específico; sem neon, brilho ou gradiente.
- **Vocabulário da UI:** GRAVE, PUXA, CORTA, SEGURA, SOBE, VIRADA, MONTAGEM, PAREDÃO, BAILE, TAMBOR, MANDELA.
- **Evitar:** samples ou nomes de músicas e artistas, imagens de pessoas reais, armas, caricatura do morro.
  A celebração é do som e da festa.

## Riscos

- **Upstream em beta.** O KAWA muda rápido (0.1 → 0.10 em semanas). Fixar o commit base e decidir cada rebase.
- **Tamanho.** Na 0.3, o projeto do KAWA usava 33 KB dos 36 KB da sua área de store (conferir na 0.10); kits, breaks e a língua PT precisam caber
  na flash do app (`0x93000`). O `build.py` recusa o que passa, medir a cada fase.
- **CPU.** Kits mais longos (kick 808 de 1 s) e o drive em todas as trilhas: medir no simulador e no stress test.
- **Direitos.** Nada de samples de discos. O "Volt Mix" do kit é uma batida sintetizada no estilo, não o sample.
