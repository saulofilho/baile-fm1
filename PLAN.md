# BAILE — plano do firmware (nome provisório)

Tracker de **funk brasileiro** para o M-VAVE FM-1: tamborzão, Volt Mix, 150 BPM, mandelão, brega funk e montagem.
Firmware livre (GPL-3.0-only); a autoria e a licença de cada parte estão em [LICENSING.md](LICENSING.md).

**Mood board:** [`docs/moodboard/index.html`](docs/moodboard/index.html) (abra no navegador). O resumo está na seção
[Mood](#mood) abaixo.

## Roteiro

Organizado em 2026-11-22. **É a lista que vale:** tudo o que vamos fazer está aqui, com um código para citar ("faz o
S3"). O que já foi feito, dia a dia, está em [Andamento](#andamento); as fases da criação, em [Fases](#fases).

Estados: **lançado** · **pronto** (no código, sem release) · **a fazer** · **pausado** · **do autor** (só o autor pode
fazer) · **a decidir**.

### Visão geral

| Versão | Tema | Itens | Estado |
| --- | --- | --- | --- |
| **0.3** | Identidade, português, telas legíveis | H1 a H7 | lançada em 2026-11-21, validação aberta |
| **0.4** | Grave de paredão | S1, S2, S3, W1 | S1, S2 e W1 prontos; S3 pausado |
| **0.5** | Baile ao vivo | S4, S5, S6, S7 | a fazer |
| **0.6** | Voz | S8 | a fazer, por último |
| **1.0** | Firmware validado e listado | critérios abaixo | a fazer |

A ordem dos itens de som é a do autor. A divisão em versões é proposta e pode mudar.

### Agora, nesta ordem

1. Push do `som-808` e merge no `main` (do autor).
2. **S3**, grave em mono (pausado a pedido, para arrumar o site).
3. Pacote 0.4 candidato no FM-1, com o roteiro de teste.
4. **H1 a H4**: o que destrava a listagem no Hub.

### 0.3: validação e Hub

| Código | O quê | Pronto quando | Estado |
| --- | --- | --- | --- |
| H1 | Roteiro de 10 itens no aparelho | cada item relatado em `docs/TEST-RESULTS.md` | do autor |
| H2 | Instalar a partir do V15 oficial e voltar para ele | os dois sentidos relatados (apaga projetos e samples) | do autor |
| H3 | Instalar a partir de outro firmware, e outro a partir do BAILE | os dois sentidos relatados | do autor |
| H4 | Formulário do Hub | Check again verde, texto de teste verdadeiro, caixa de testado marcada só depois de H2 e H3 | do autor |
| H5 | Licença dos sons `licensed` | o Sven aprova | esperando o Hub |
| H6 | Pages com um deploy só | Settings › Pages › Source: GitHub Actions | do autor |
| H7 | Estalo do GRAVE+ na 0.3 | sai uma 0.3.1 a partir da tag, ou espera a 0.4 | a decidir |

### 0.4: grave de paredão

| Código | O quê | Pronto quando | Estado |
| --- | --- | --- | --- |
| S1 | GRAVE+ com harmônicos para alto-falante pequeno, sem estalo | 120–500 Hz sobe sem subir o pico do master | pronto, aprovado de ouvido; falta o FM-1 |
| S2 | DUCK: o bumbo abaixa o baixo, por faixa | salvo no projeto, 0.3 compatível | pronto, aprovado de ouvido; falta o FM-1 |
| S3 | Grave em mono | abaixo de ~120 Hz esquerda = direita, agudos abertos, opcional por projeto | pausado |
| W1 | Emulador e importador no desenho novo | iguais ao hub no desktop e no celular, PT e EN | pronto; vai ao ar com o merge |
| R4 | Release 0.4 | roteiro no FM-1, CPU anotada, áudios do hub e telas do manual refeitos, tag | a fazer |

Medidas e preço do S1: nas 4 demos +1,0 a +1,5 dB em 120–500 Hz com pico igual; no 808 sozinho +5 a +19 dB em
200–1000 Hz, **pico +1,0 dB** (9872 de 32767) e **fundamental ~2 dB menor**; +18% do motor no computador enquanto
ligado. Músicas com GRAVE+ gravado (a demo MANDELAO) mudam de som.

S2: DUCK em ENVIOS (KNOB 4), no byte que era folga (`sound_t.duck`): mesmo formato, idêntico byte a byte com 0.

### 0.5: baile ao vivo

| Código | O quê | Pronto quando | Antes de começar |
| --- | --- | --- | --- |
| S4 | Montagem por frase | ÂNCORA mantém 1, 2 e 4; a virada cai só no fim da frase de 2 a 16 compassos | onde entra o controle |
| S5 | THROW: tudo para o eco ou reverb enquanto segura | rampa de ~12 ms, a cauda continua ao soltar, grava com REC | os 64 efeitos estão ocupados: o que sai |
| S6 | DROP: corta tudo e volta no tempo forte | volta no compasso, sem estalo | o mesmo |
| S7 | Modo LIVE de lançar patterns | a tecla pisca na fila e o pattern entra no fim do compasso | página e teclas |

### 0.6: voz

| Código | O quê | Pronto quando | Antes de começar |
| --- | --- | --- | --- |
| S8 | Voz por formantes ("ô", "ai", "ei"), toda sintética | vogal por passo, sem voz gravada, cabe na CPU do aparelho | medir a CPU no FM-1 |

### 1.0: critérios

- [ ] S1 a S8 lançados, cada um testado no FM-1.
- [ ] H1 a H5 fechados e o BAILE listado no Hub.
- [ ] Update interrompido retomado no aparelho (T6).
- [ ] Dívidas marcadas "antes da 1.0" resolvidas.
- [ ] Manual, READMEs e site conferidos em PT e EN.

### Dívidas técnicas

| Código | O quê | Quando |
| --- | --- | --- |
| T1 | CI roda os testes antes de publicar o Pages e a release (hoje nenhum roda) | antes da 0.4 |
| T2 | O Pages publica o repositório inteiro (PLAN, rascunhos, fontes): publicar só o site | com T1 |
| T3 | O emulador do site (o link `play` do Hub) segue o `main` e fica à frente da release: separar ou avisar | aviso feito; separar a decidir |
| T4 | Testes de interface com Playwright nunca rodaram e esperam textos antigos | antes da 1.0 |
| T5 | CPU medida no FM-1 (OPÇÕES: CPU e MAX) com GRAVE+, DUCK e 6 faixas | na 0.4 |
| T6 | Instalação interrompida e retomada, confirmada no aparelho | antes da 1.0 |
| T7 | Ícones e faders pálidos no tema CLARO | antes da 1.0 |
| T8 | 11 valores de 7 letras cortados na linha de baixo | antes da 1.0 |
| T9 | Manual: telas e textos do DUCK e do GRAVE+, cheat sheet (campo `cheat` do Hub) | na 0.4; cheat sheet antes da 1.0 |
| T10 | `source/BUILDING.md` com trechos herdados (inglês e 100 BPM na partida, roteiros em francês) | antes da 1.0 |
| T11 | `tests/run_stress_test.sh` sem permissão de execução | qualquer hora |
| T12 | Manual em espanhol (o firmware e o emulador já falam) | a decidir |

### Ideias, sem decisão

Não entram em versão sem o autor aprovar. Origem em [`docs/REFERENCES.md`](docs/REFERENCES.md).

| Código | Ideia | O que pesa |
| --- | --- | --- |
| I1 | Variação que evolui: até 4 passos novos por compasso, por mapa de funk | mapas próprios por kit |
| I2 | Proteção de CPU por etapas | só se T5 mostrar necessidade |
| I3 | Riff repetível por semente, preso à escala | parecido com a MELODIA de hoje |
| I4 | DUCK disparado também por bumbo de break | detectar o bumbo na fatia |

### Regras de trabalho

- Cada melhoria entra nos **dois READMEs** e neste roteiro no mesmo commit, dizendo o que foi e o que não foi testado
  no aparelho.
- Trabalho no **`main`**, sem criar branch (o `som-808` é o último). O autor faz push, merge e tags.
- Cada item de som: teste que falha antes, stress sem estouro, projetos antigos abrindo, A/B para ouvir.
- Uma tag `v*` publica na hora: só depois do candidato instalado no FM-1. Tag publicada não se move.
- Tudo sintetizado, licença conferida antes de aproveitar código dos outros.

## Por que esta base

A base escolhida já tinha o que o funk pede, e o GR!MM (base do GL!TCH e do COQUÍ) não tem:

| O funk precisa de | A base já tinha |
| --- | --- |
| Tamborzão picotado, montagem, "puxadas" | Breaks em 16 fatias, ferramenta HACHOIR (chop), efeitos ROLL / REV / CUT / HOP por célula |
| Grave 808 que escorrega | Efeitos de célula GLI e BND, uma **TABLE** por trilha (pitch drops, ratchets) |
| O "atraso" do tamborzão | **GROOVE tables**: duração por passo, não um swing só |
| Virada de DJ ao vivo | 64 efeitos live (stutter, retrig, build-up, scratch, DESTROY e BEAT), FX sequencer |
| Paredão | Drive por trilha, sends, filtro de 11 tipos |
| Interface em português | O sistema de idiomas (`LANG_N`, hoje FR, EN e ES) |

## Decisões

| Tema | Decisão |
| --- | --- |
| Nome | **BAILE** (provisório; livre no catálogo do Hub em 2026-11-17). Alternativas: PANCADÃO, PAREDÃO, TAMBORZÃO |
| Base | A registrada em `LICENSING.md`, congelada num commit, remoto `upstream`. Rebase em versões novas só por decisão |
| Gêneros da 1.0 | Funk carioca de raiz (Volt Mix / Miami bass), tamborzão, funk 150, mandelão (SP), brega funk (PE), montagem |
| Tempo | Padrão **130 BPM**; o funk 150 e o brega funk ganham projetos de fábrica no tempo deles |
| Identidade | `FM-1_808130` desde a 0.3 (a 0.1 e a 0.2 eram `FM-1_971`, dentro da faixa do zp12; evitar `95x`, que é a série da base). Magics próprios: projeto `BPRJ`, samples `BSMP`, ajustes `BAIL`, SysEx `BAIL`. Não lê saves de outros firmwares |
| Idiomas | **PT padrão**, EN e ES. O FR da base sai (economiza flash; a confirmar) |
| Som | 100 % sintetizado. **Nenhuma gravação de música alheia** (sem samples de Volt Mix, de MCs, de discos). Os 4 slots de sample ficam para o usuário |
| Voz de MC | Não haverá voz gravada. Fase opcional: "vocais" sintéticos curtos por formantes ("ô", "vai", "ai") |
| Visual | Estrutura do Byte Beats com um mosaico de ladrilhos pintados nas cores das penas da arara, sobre preto. Ver [Mood](#mood) |
| Hardware | Testes no simulador (`tests/run_host.sh`) e no emulador web até haver teste no FM-1. Flash `0x856014` e `0xB36014` |
| Repositório | `projetos-git/baile-fm1`, git local. Público no GitHub; trabalho no `main`, o autor faz push, merge e tags |
| Licença | GPL-3.0-only, autoria e licença de cada parte em `LICENSING.md` |

## Fases

As fases da criação (0 a 7 feitas; a 8 continua no [Roteiro](#roteiro)). Histórico: nomes e números são os de então.

0. **Ambiente.** Rodar os testes da base intacta: `tests/run_host.sh`, `run_stress_test.sh`, `run_kits_test.sh`, o
   emulador (`web/make_emulator.sh`) e o pacote (`./build.sh`, toolchain JieLi + SDK AC79 em Docker, como no COQUÍ).
   Só depois mudar código.
1. **Identidade.** `PRODUCT = "FM-1_971"` em `tools/build.py`, pacote `baile.fwsc`, `PRJ_MAGIC`/`USR_MAGIC` próprios,
   `APP_NAME`. Temas **TERRA** (padrão) e **CLARO** no lugar dos três temas da base. Os 16 ladrilhos e a tela
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
   em 16: `TAMBOR`, `VOLT`, `CENT50`, `MANDELA`, `BREGA`, `MONTAG`. O gerador da base tem BPM fixo (160): torná-lo
   por break ou confirmar que o fatiamento cobre 130–150 sem artefato. Teste: `tests/breaks_check.py`.
4. **Grooves e MAGIA.** Modelos de GROOVE com o balanço do tamborzão e do brega. Ferramentas de MAGIA novas: GERAR
   TAMBORZÃO, GERAR GRAVE (808 nos tempos do funk), **MONTAGEM** (recorta e reordena as fatias de um break), **VIRADA**
   (fill de fim de frase). Escalas: menor, frígio, menor harmônica (o "grave sinistro" do mandelão).
5. **Grave e melodia.** Sons de fábrica: GRAVE 808 (com glide e drive), GRAVE TORTO, SUB, SINO, PIANO MELODY, BRASS
   FM, "LEAD MELODY", ORQUESTRA STAB, SIRENE. Revisar os 4 patches FM próprios da base (`gen_fm_patches.py`).
   Projetos de fábrica: um por gênero da 1.0 (substitui a demo da base).
6. **Efeitos live de baile.** Renomear e ajustar bancos: PUXA (scratch), CORTA (mute em batida), SEGURA (stutter),
   SOBE (build-up), GRAVE+ (sub boost), ECO MC (eco de 1/8 pontuado), SIRENE (por cima do master). Os bancos DESTROY e
   BEAT ficam.
7. **Web.** Hub próprio (como o do COQUÍ: a cena do boot animada, cada gênero com grade e áudio do próprio firmware),
   emulador (`emulator/`), instalador no navegador (`install/webinstall.js`), importador de samples, manual e cheat
   sheet em **PT**, EN e ES.
8. **Release.** `./build.sh --release 1.0`, teste no FM-1 (instalar a partir do oficial V15 e de outro firmware,
   sair, voltar, update interrompido), `docs/TEST-RESULTS-1.0.md`, envio ao FM-1 Firmware Hub com `fmhub.json`.

O que era opcional (vocais por formantes, modo LIVE) virou S8 e S7 no Roteiro.

## Andamento

- **2026-11-18, Fase 0 (no computador):** o simulador e os testes da base rodam no macOS (`.venv` com Pillow na raiz;
  `PATH="$PWD/../.venv/bin:$PATH"` antes de `tests/run_host.sh`). Dois ajustes para o clang do macOS: sem seções ELF
  no build host (`gfx.c`, `platform.c`) e uma conta de ponteiro em `kawa_sysex.c`. Verdes: host, features, format,
  kits, ui, stress, `websamples_test.js`, `webinstall_test.js`. **Faltam:** o emulador web (precisa de `wasm-ld`:
  `brew install lld`) e o pacote do FM-1 (Docker parado; toolchain JieLi e SDK AC79 já estão na máquina).
- **2026-11-18, Fase 1 (parte):** identidade (`FM-1_971`, `baile.fwsc`, magics próprios, ferramentas de sample
  alinhadas; o `format_test` troca o magic dos fixtures da base para seguir testando a conversão). Temas **TERRA**,
  **CLARO** e **PAREDAO** com as penas da arara; cores das páginas. Mascote: a **arara** de headphone no lugar do
  cachorro da base (`tools/gen_art.py`). Boot: o **mosaico de ladrilhos** (`tools/gen_boot.py` → `art/boot-baile.png`)
  acendendo do centro para fora, "BAILE" na fonte grande (I e L acrescentados em `tools/gen_fonts.py`).
  README (PT, com resumo em EN) e `LICENSING.md` novos; a arte do cachorro e os READMEs FR/ES da base saíram.
  **Fase 1 completa** no computador (o site, o instalador web e o manual ainda são os da base: Fase 7).
- **2026-11-18, interface em PT:** o português ocupa o lugar do francês da base (`LANG_PT`, idiomas PT, EN, ES) e é
  o padrão de um FM-1 novo. 731 posições de texto (518 textos), cada uma no limite de largura do texto original;
  "track" é **FAIXA**. `tools/i18n_slots.py` acha as posições e aplica `tools/i18n_pt.json` (para revisar uma
  tradução: editar o JSON, `check`, `apply`; só funciona desde a correção de 2026-11-21, abaixo). Nomes dos patches FM em `tools/gen_fm_patches.py`. Sem acentos: as
  fontes da tela são ASCII.
- **2026-11-18, Fase 2 (kits):** os 8 kits da base viraram **VOLT, TAMBOR, 150, MANDELA, BREGA, MELODY, TUIN e
  PERCUS** (`source/firmware/src/kawa_kits.h`), 16 peças cada, com as mesmas regras de tecla (1 bumbo, 2 segundo
  bumbo, 3 caixa, 5 e 6 chimbal; no PERCUS, atabaques, chocalho e pandeiro). Presets de kit renomeados (KIT
  TAMBORZAO, KIT MANDELAO, KIT 150 SUJO…). `kits_test` verde (sem clip, sem silêncio, nenhuma tecla igual entre
  kits); o `features_test` agora espera o bumbo do VOLT terminar (até ~1,7 s depois do STOP). **Falta ouvir:** os
  WAVs de cada kit saem em `source/build/kits/` (`kit_N.wav`, `beat_N.wav`) com `tests/run_kits_test.sh`; ajustar o
  timbre de ouvido. Os breaks e os grooves de funk são as Fases 3 e 4.
- **2026-11-18, Fase 3 (breaks):** os 6 breaks da base viraram **TAMBOR, VOLT, CENT50, MANDELA, BREGA e MONTAG**
  (`source/tools/gen_breaks.py` → `kawa_breaks.h`), batidas originais e sintetizadas, cada uma com o seu "estúdio"
  (sala, mesa, fita, sampler): o tamborzão com atabaques, o Volt com 808 e sub, o 150 seco num sampler de 16 kHz, o
  mandelão sujo a 9 kHz e 8 bits, o brega com swing, timbal e ride, a montagem com um som diferente a cada
  semicolcheia. `tests/breaks_check.py` ok (caixa no 2 e no 4, bumbos e caixas onde marcados, nenhum par parecido).
  O BPM dos breaks continua 160 (o da base): fatiados, eles tocam a 130–150 sem problema. Presets de sample
  renomeados (TAMBORZAO, VOLT, FUNK 150, MANDELAO, BREGA FUNK, MONTAGEM…). `numpy` na `.venv` para o gerador.
  **Falta ouvir:** `source/build/breaks/*.wav`.
- **2026-11-18, Fase 4 (grooves e MÁGICA):** modelos de GROOVE de funk: RETO, **TAMBOR** (6 7 5 6: o atraso da 2ª
  semicolcheia), **BREGA** (7 5), **150** (6 5 7 6: empurra), **MANDELA** (7 5 6 6), TERCINA. Ferramentas MÁGICA
  (`source/firmware/src/kawa_edit.c`): **BEAT FUNK** escreve o funk do kit da faixa (cada kit com o seu bumbo, caixa,
  palmas, percussão e chimbal; a intensidade acrescenta camadas, ghosts e o rufo final); **GRAVE 808** (no lugar de
  BAIXO) põe o baixo no 0 3 6 10 14, quase sempre a tônica, com glides; **MONTAGE** (no lugar de ARPEJO) picota 2 a 4
  fragmentos de um break ou de um kit em grupos que se repetem, com avesso e tom; **VIRADA** (no lugar de RUFOS)
  acrescenta, num kit, a virada de caixa que acelera no fim do compasso. Teste novo no `features_test` (10). As
  escalas da base já têm frígia e menor harmônica: ficam.
- **2026-11-18, Fase 5 (sons e demo):** sons de fábrica novos, depois dos da base (os índices que um projeto guarda
  não mudam): **GRAVE 808**, **GRAVE TORTO**, **SUB**, **LEAD MELODY**, **SIRENE**, **PIANO MELODY**, **STAB**. Um
  projeto novo já vem com o GRAVE 808 e o kit TAMBOR. A **demo** agora é "BAILE": um tamborzão em lá menor a 130,
  4 patterns (intro com o break e o piano; o tamborzão com o 808; o drop com o refrão no lead, os acordes e o break
  picotado; a virada com o filtro fechando) numa música de 5 entradas. A demo da base mora agora no
  `format_test` (que confere a conversão do save antigo). `tests/demo_baile.txt` carrega e toca a demo no
  simulador; o áudio fica em `source/build/demo/baile-demo.wav`. Ficou de fora: um projeto de fábrica por gênero
  (feito na 0.2: quatro demos, uma por estilo).
- **2026-11-18, Fase 6 (efeitos ao vivo):** bancos **BAILE** e **PAREDAO** (DESTROI e BEAT ficam).
  Renomeados: **SEGURA** (stutter), **PUXA** (scratch), **SOBE** (build-up), **CORTA** (gate), **ECO MC** (o eco de
  colcheia pontuada da base). Novos, no lugar do ANEL e do VINIL da base (`source/firmware/src/kawa_fx.c`):
  **GRAVE+** (os graves abaixo de ~120 Hz em dobro, com o joelho suave) e **SIRENE** (um tom que sobe e desce de 700
  a 1300 Hz a cada batida e meia, por cima de tudo), com ícone novo. O stress test toca todos no máximo: ok. **Falta
  ouvir** o GRAVE+ e a SIRENE.
- **2026-11-18, Fase 7 (web):** o **pacote** compila (`./build.sh`, com o Docker Desktop no macOS): `baile-0.1.fwsc`,
  `FM-1_971`, todas as checagens de tamanho, RAM e flash ok; os testes do loader passam (instalação, retomada, chip
  desconhecido). Um `strcmp` que só existia no build do computador foi trocado (a libc do firmware não tem). Os
  pacotes da base saíram de `install/`; `install/baile-0.1.fwsc` e a cópia na raiz, com `SHA256SUMS`
  (`release_check.sh` ok). **Instalador web** e lançadores com a identidade do BAILE (48 testes ok com o pacote
  real). **Hub** novo (`index.html`) em PT no visual do mood board: instalador, áudios da demo e dos 6 breaks
  (`docs/audio/`, AAC feito com `afconvert`), o que tem, links. **Emulador** (`emulator/index.html`) compilado num
  contêiner Debian com clang e lld; a página em PT (padrão), EN e ES, com o rodapé de licença. **Manual** novo em PT
  (`manual/index.html`) com telas do simulador (`source/tests/manual_pt.txt`); o manual, o cheat sheet e o card da
  base saíram. Importador de samples renomeado. `fmhub.json` do BAILE.
- **2026-11-18, Fase 8 (começo):** a 0.1 instalada num FM-1 de verdade a partir de `FM-1_966`: "done: the FM-1 runs
  FM-1_971" (`docs/TEST-RESULTS.md`; o resto do roteiro no aparelho está por fazer).
- **2026-11-18, o site todo no BAILE:** menu único em PT em todas as páginas, GitHub do `baile-fm1`, importador de
  samples em PT (erros traduzidos na página pelo código), cores do BAILE no emulador e no importador, projetos
  `.baile`, favicon de ladrilhos.
- **2026-11-21, 0.2: uma demo por estilo.** PROJETOS › DEMO carrega a próxima a cada vez: **BAILE** (tamborzão, 130),
  **VOLT** (Miami bass em mi menor, 128), **MANDELAO** (fá frígio, 130, GRAVE+ e DISTOR gravados) e **BREGA FUNK**
  (dó menor, 150, groove BREGA). `features_test` 11 carrega e toca as quatro. Áudio de cada uma no hub. A tag `v0.9`
  herdada da base saiu (dispararia uma release). `source/BUILDING.md` com o BAILE e as notas do macOS. A 0.1 (a
  instalada no aparelho) foi para `install/older/`.
- **2026-11-21, 0.2 no aparelho:** instalada por cima da 0.1; o autor relatou "Testei tudo, ok" sobre o roteiro
  de `docs/TEST-RESULTS.md` (sem item por item). Os dois chips de flash são aceitos (`FL_CHIP_OK`). Tag `v0.2` criada; rascunho do e-mail ao
  Hub em `docs/HUB-SUBMIT.md`.
- **2026-11-21, auditoria (corrigido no código, rumo à 0.3):** defeitos que estavam publicados como prontos.
  **Emulador:** procurava o magic de projeto da base (salvar no navegador, exportar e importar `.baile` nunca
  funcionaram) e mandava samples com o magic da base (o BAILE recusa); o site mostrava 0.10, agora a versão vem de
  `source/VERSION`. **Firmware 0.2:** os bancos DESTROI e BEAT (`kawa_kg.c`) ficaram em francês, o idioma PT se chamava
  FRANCAIS, e cinco traduções saíram erradas. **`i18n_slots.py`:** o `apply` quebrava e não lia o `kawa_kg.c`; a chave
  de cada texto agora é arquivo + EN + ES + ordem. **Manual:** a DEMO pede um OCT+, não dois. Teste novo:
  `source/tests/emulator_test.js`. O pacote em `install/` continua a 0.2, com esses defeitos de texto.
- **2026-11-21, telas da 0.3 (antes de instalar):** medidas no simulador em todas as páginas, 3 idiomas e 3 temas. A
  linha de baixo cortava valores de 3 caracteres (BPM 130 aparecia 13, NAO aparecia NA). Nomes: bancos BAILE e PAREDAO
  nos três idiomas, MAGICA, DOBRA, DESCE, BATIDAS, POUCO, 1 PASSO, RETRIG. No tema CLARO o texto sem contraste escurece
  sozinho (`g_readable`, `kawa_gfx.c`). Ficam: valores de 7 letras cortados na linha de baixo (o nome inteiro está na
  página) e ícones e faders pálidos no CLARO. Candidato novo em `source/build/baile-0.3.fwsc`, sem teste no aparelho.
- **2026-11-21, 0.3:** instalada por cima da 0.2 (`FM-1_808130`, versão lida por USB). O roteiro no aparelho está aberto
  (`docs/TEST-RESULTS.md`). `install/`, site, manual e emulador na 0.3; a release sai com o push da tag `v0.3`.

- **2026-11-21, som (`som-808`):** S1 (GRAVE+ com harmônicos) e S2 (DUCK), os dois aprovados de ouvido pelo autor nos
  A/B, sem teste no FM-1.
- **Site, 2026-11-21:** a diagramação de <https://www.lamannabakery.com/> com as cores do BAILE (hub gerado por
  `source/tools/gen_site.py` de `source/web/hub.html`; barra comum em `site.css`) e versão em inglês.
- **2026-11-22, site (W1):** emulador e importador no desenho do hub (hero, letreiro, blocos, rodapé; o aparelho segue
  escuro). Corrigidos no caminho: o aviso falso de "nunca testado num FM-1", as cores antigas na onda do importador em
  inglês, o seletor de espaço gigante, a barra do emulador sempre em português, o CSS velho no cache (`site.css?v=`
  pelo hash, em `gen_site.py`). Roteiro reorganizado.

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
  legendas mono cinza espaçadas. No FM-1, as fontes de tela com acentos.
- **Hub e editor web:** fundo preto, uma faixa de mosaico animado no topo, botões em pílula, XY pads e faders com
  número grande.
- **Regras:** cor é som; feito à mão (traço grosso, quadrados imperfeitos); símbolos geométricos, nada copiado de um
  povo ou rito específico; sem neon, brilho ou gradiente.
- **Vocabulário da UI:** GRAVE, PUXA, CORTA, SEGURA, SOBE, VIRADA, MONTAGEM, PAREDÃO, BAILE, TAMBOR, MANDELA.
- **Evitar:** samples ou nomes de músicas e artistas, imagens de pessoas reais, armas, caricatura do morro.
  A celebração é do som e da festa.

## Riscos

- **Upstream em beta.** A base muda rápido (0.1 → 0.10 em semanas). Fixar o commit base e decidir cada rebase.
- **Tamanho.** Na 0.3, o projeto da base usava 33 KB dos 36 KB da sua área de store (conferir na 0.10); kits, breaks e a língua PT precisam caber
  na flash do app (`0x93000`). O `build.py` recusa o que passa, medir a cada fase.
- **CPU.** Kits mais longos (kick 808 de 1 s) e o drive em todas as trilhas: medir no simulador e no stress test.
- **Direitos.** Nada de samples de discos. O "Volt Mix" do kit é uma batida sintetizada no estilo, não o sample.
