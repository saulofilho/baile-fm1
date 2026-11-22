# BAILE: tracker de funk brasileiro para o M-VAVE FM-1

**Português** · [English](README.en.md)

![O boot do BAILE: o mosaico de ladrilhos nas cores da arara](docs/boot.png)

**BAILE** é um firmware livre para o **M-VAVE FM-1**, feito para **funk brasileiro**: tamborzão, Volt Mix, funk 150,
mandelão, brega funk e montagem. É um *tracker*: cada linha é um passo, cada coluna uma faixa, e a música desce a
tela. É um fork do [KAWA](https://github.com/Guizmoh/Kawa-Tracker-Fm1), de Omnipotard.

[Site e instalador](https://saulofilho.github.io/baile-fm1/) ·
[Emulador](https://saulofilho.github.io/baile-fm1/emulator/) ·
[Manual](https://saulofilho.github.io/baile-fm1/manual/) ·
[Importador de samples](https://saulofilho.github.io/baile-fm1/samples.html) ·
[Releases](https://github.com/saulofilho/baile-fm1/releases)

**Índice:** [estado](#estado) · [o que tem](#o-que-tem) · [primeiro tamborzão](#primeiro-tamborzão) ·
[botões](#botões) · [instalar](#instalar) · [samples](#seus-samples) · [compatibilidade](#compatibilidade) ·
[resgate](#resgate) · [voltar ao oficial](#voltar-ao-firmware-oficial) · [compilar](#compilar-e-testar) ·
[créditos](#créditos-e-licença)

## Estado

| | |
| --- | --- |
| Versão publicada | **0.2 beta** |
| Identidade | `FM-1_971` |
| No FM-1 de verdade | A 0.1 foi instalada a partir de outro firmware (`FM-1_966`) e a 0.2 por cima dela. O que foi e o que não foi confirmado: [resultados](docs/TEST-RESULTS.md) |
| No repositório | Rumo à 0.3: só testado no computador |
| Defeitos da 0.2 | Com o idioma em português, os bancos DESTROI e BEAT e o nome do idioma aparecem em francês, e alguns textos estão errados. Já corrigido no código, entra na 0.3 |

Firmware não oficial, não feito nem endossado pela M-VAVE. Instale por sua conta e risco.

## O que tem

### O tracker

- **Seis faixas**, cada uma com um motor: pulso, onda de 4 bits, ruído, FM de 6 operadores (uma faixa), kit de bateria
  ou sample em 16 fatias.
- **32 patterns** de 16, 32 ou 64 passos, encadeados numa música.
- Em cada célula, uma nota, um volume e até **dois efeitos**: arpejo, glide, vibrato, rufo, chance, atraso, corte,
  avesso, tom, pulo, fim.
- Uma **tabela** por faixa (uma pequena sequência dentro da nota), **groove** por passo, filtro de 11 tipos e
  sequenciador de efeitos.
- Drive, eco e reverb por faixa, metrônomo, relógio MIDI e áudio por USB.
- Desfazer e refazer, música salva sozinha e **três espaços de projeto**.
- Tela em **português**, inglês ou espanhol.

### Os 8 kits

As 16 teclas brancas são 16 peças. Em todo kit a tecla 1 é o bumbo, a 2 o segundo bumbo, a 3 a caixa e a 5 e a 6 o
chimbal fechado e aberto.

| Kit | O som |
| --- | --- |
| **VOLT** | O 808 do Miami bass: bumbo longo, palma, cowbell, clave, congas |
| **TAMBOR** | O tamborzão: bumbo seco, TUM, caixa seca, palmas, atabaques |
| **150** | Curto e duro: bumbo seco, soco distorcido, caixa estalada, metal |
| **MANDELA** | Mandelão: bumbo estourado, sub, bigornas, bruxaria, laser |
| **BREGA** | Brega funk: dois bumbos, palma dobrada, timbales |
| **MELODY** | A bateria limpa do funk melody dos anos 2000 |
| **TUIN** | Efeitos de baile: sirenes, apito, tuin, laser, tiro, explosão |
| **PERCUS** | Atabaques, surdo, tamborim, agogô, cuíca, pandeiro, reco-reco, ganzá |

### Breaks e sons

- **Seis breaks** em 16 fatias: TAMBORZAO, VOLT, FUNK 150, MANDELAO, BREGA FUNK, MONTAGEM.
- **Sons de funk:** GRAVE 808 (com soco e glide), GRAVE TORTO, SUB, LEAD MELODY, PIANO MELODY, STAB e SIRENE, além
  dos sons de fábrica do KAWA.
- Kits e breaks são **sintetizados**, sem gravação de discos. A origem de cada parte está em
  [LICENSING.md](LICENSING.md).

### MÁGICA (SCL duas vezes)

| Ferramenta | O que faz |
| --- | --- |
| **BEAT FUNK** | Escreve o funk do kit da faixa. A intensidade acrescenta camadas |
| **GRAVE 808** | O baixo no 3-3-2, quase sempre na tônica, com glides |
| **MONTAGE** | Pedaços do break ou do kit que se repetem, alguns ao contrário |
| **VIRADA** | Rufos e a virada de caixa no fim do compasso |
| E mais | Picador, melodia, Euclides, variações, acentos, dobrar, deslocar, clonar, transpor, copiar e colar |

### Grooves

| Groove | Tiques por passo | O balanço |
| --- | --- | --- |
| RETO | 6 6 | Nenhum |
| TAMBOR | 6 7 5 6 | O atraso da segunda semicolcheia |
| BREGA | 7 5 | O swing do brega funk |
| 150 | 6 5 7 6 | Empurra a segunda |
| MANDELA | 7 5 6 6 | Arrasta |
| TERCINA | 4 4 4 | Tercinas |

### 64 efeitos ao vivo

Segure **FX** e toque as teclas brancas. São quatro bancos (OCT− e OCT+): **BAILE**, **PAREDAO**, **DESTROI** e
**BEAT**. Tem SEGURA, PUXA, SOBE, CORTA, AVESSO, FITA, GRAVE+, ECO MC, SIRENE e muito mais, no master ou numa faixa.
Com REC, o efeito fica gravado no pattern.

### Quatro demos

Cada carga da DEMO traz a próxima:

| Demo | Estilo | BPM |
| --- | --- | --- |
| BAILE | Tamborzão | 130 |
| VOLT | Miami bass | 128 |
| MANDELAO | Mandelão | 130 |
| BREGA FUNK | Brega funk | 150 |

Para ouvir: **SAVE**, desça até DEMO com **SELECT**, **OCT+** (mais uma vez se ele perguntar pela música não salva),
**PLAY**.

### O visual

Um mosaico de ladrilhos pintados à mão sobre chão preto, nas cores das penas da arara, uma cor por faixa. O mascote é
uma arara de headphone. Temas TERRA, CLARO e PAREDAO, quatro fontes de tela.
[Mood board](https://saulofilho.github.io/baile-fm1/docs/moodboard/).

## Primeiro tamborzão

1. **SAVE**, música nova. A faixa 5 já é o kit TAMBOR e a faixa 3 o GRAVE 808.
2. Na faixa 5 (ALGORITHM), **SCL** duas vezes e toque **BEAT FUNK** (tecla 2).
3. Na faixa 3, toque **GRAVE 808** (tecla 4).
4. **GLO** duas vezes, escolha o groove TAMBOR com o KNOB 3 e ligue com o KNOB 4.
5. **PLAY**. Segure **FX** e toque nas teclas brancas.

## Botões

| Botão | O que faz |
| --- | --- |
| **HOME** | As faixas. Segurado: a ajuda da página. **HOME + PLAY**: pânico, para tudo |
| **SEQ** | A grade de passos. OCT− e OCT+: 16, 32 ou 64 passos |
| **EDIT** | O som: SOM, SOM 2, operadores ou edição do sample, EFEITO, TABELA |
| **LFO** | LFO, depois MODULAÇÃO |
| **ENV** | ENVELOPE, depois MIX |
| **FX** | ENVIOS, LIVE, FILTRO, SEQ FX. Segurado: LIVE |
| **SCL** | ESCALA, depois MÁGICA |
| **GLO** | MÚSICA, GROOVE, OPÇÕES |
| **SAVE** | PROJETOS. Segurado: ferramentas, e OCT− e OCT+ desfazem e refazem |
| **PLAY**, **REC** | Toca e para; grava |
| **ARP** | Apaga a célula. Segurado é o *shift* |
| **SELECT** | A linha ou a página |
| **ALGORITHM** | A faixa |
| **PRESETS** | O som de fábrica ou o pattern. Com ARP segurado, o motor |
| **KNOB 1 a 4** | O que diz a linha de baixo da tela: vermelho, amarelo, verde, azul |

Tudo em detalhe, com telas, no [manual](https://saulofilho.github.io/baile-fm1/manual/).

## Instalar

Você precisa de um FM-1, um cabo USB **de dados** e energia estável. Feche os outros programas MIDI e salve fora o
que for importante: projetos de outros firmwares não são lidos pelo BAILE.

**Pelo navegador (Chrome, Edge, Opera):** abra o [site](https://saulofilho.github.io/baile-fm1/), ligue o FM-1 no USB
e clique em *Instalar o BAILE*.

**Pelo lançador:** baixe o repositório (*Code*, *Download ZIP*), descompacte e rode o do seu sistema, com
[Python 3](https://www.python.org/downloads/) instalado:

| Sistema | Arquivo |
| --- | --- |
| Windows | `INSTALL-Windows.bat` |
| macOS | `INSTALL-Mac.command` (na primeira vez: botão direito, Abrir) |
| Linux | `./INSTALL-Linux.sh` |

**Pelo terminal:**

```bash
python3 -m venv .venv
.venv/bin/pip install mido python-rtmidi
.venv/bin/python install/fm1_install.py install/baile-0.2.fwsc
```

O pacote é conferido inteiro antes de apagar qualquer coisa. A gravação pode demorar (25 minutos num dos nossos
testes). Não desligue. Se o cabo cair, ligue de novo e repita: a instalação continua. Para ver o que está instalado,
sem gravar nada:

```bash
.venv/bin/python install/fm1_install.py --info
```

Os SHA-256 dos pacotes estão em [install/SHA256SUMS](install/SHA256SUMS).

## Seus samples

São quatro espaços, MY 1 a MY 4: mono, 8 bits mu-law, até 1,66 s a 22 050 Hz ou 3,3 s a 11 025 Hz. Use o
[importador no navegador](https://saulofilho.github.io/baile-fm1/samples.html) ou, com o BAILE parado:

```bash
.venv/bin/python install/baile_samples.py put 1 som.wav --name SOM
```

No FM-1: página SOM, motor SAMPLE, fonte MY 1 a MY 4. Use sons que são seus ou que você pode usar.

## Compatibilidade

- **O BAILE não lê projetos nem samples do KAWA, do firmware oficial ou de qualquer outro firmware**, e eles não leem
  os do BAILE.
- Aceita os dois chips de flash conhecidos do FM-1: `0x856014` e `0xB36014`. Num chip desconhecido o atualizador não
  grava nada.
- No emulador, os projetos ficam no navegador e saem e entram como `.baile`.

## Resgate

Segure **OCT−** ao ligar, ou espere: depois de duas falhas seguidas na partida, o FM-1 abre sozinho o resgate USB
(`BAILE USB RESCUE`). Dali, rode o instalador outra vez.

Problemas comuns:

| Problema | O que fazer |
| --- | --- |
| O instalador não acha o FM-1 | Cabo de dados, outros programas MIDI fechados, um navegador com Web MIDI |
| Silêncio | O BAILE começa vazio: grave notas ou carregue a DEMO |
| PRESETS não muda o som | Você editou o som: o próximo aparece em dourado, OCT+ carrega |
| Um clique na gravação USB | É o metrônomo: desligue em OPÇÕES |
| Errei | Segure SAVE e aperte OCT− |

## Voltar ao firmware oficial

1. Os projetos e samples do BAILE se perdem.
2. Use energia estável e cabo de dados. Se o BAILE estiver estranho, abra antes o resgate USB.
3. Instale o **V15** oficial (`FM-1_015`) com o **M-UPGRADE**, da M-VAVE.
4. **Não desconecte nada durante a transferência**: o instalador oficial reescreve também o bootloader. Este é o
   passo mais arriscado ([detalhes](source/BUILDING.md#safety-rescue-and-back-to-the-official-firmware)).

## Compilar e testar

O simulador roda no macOS e no Linux, com o compilador C do sistema:

```bash
python3 -m venv .venv
.venv/bin/pip install pillow numpy mido python-rtmidi
cd source
export PATH="$PWD/../.venv/bin:$PATH"
tests/run_host.sh
```

| O quê | Comando, dentro de `source/` |
| --- | --- |
| Recursos, formato, kits, interface | `tests/run_features_test.sh`, `tests/run_format_test.sh`, `tests/run_kits_test.sh`, `tests/run_ui_test.sh` |
| Stress | `sh tests/run_stress_test.sh` |
| Breaks | `python3 tests/breaks_check.py` |
| Emulador | `web/make_emulator.sh` (clang e lld), depois `node tests/emulator_test.js` |
| Pacote do FM-1 | `PYTHON=../.venv/bin/python ./build.sh` (Docker, toolchain JieLi, SDK AC79) |
| Atualizador, instalador, samples | `tests/run_loader_tests.sh`, `node tests/webinstall_test.js`, `node --test tests/websamples_test.js` |
| Traduções | `python3 tools/i18n_slots.py check tools/i18n_pt.json` |
| Site | `python3 tools/gen_site.py` |

| Pasta | O que tem |
| --- | --- |
| `source/firmware/` | O firmware |
| `source/tools/` | Geradores de arte, fontes, breaks, traduções, site e pacote |
| `source/tests/` | Simulador e testes |
| `source/web/` | Fontes do emulador e do site |
| `install/` | Pacotes, instaladores e ferramenta de samples |
| `manual/`, `docs/` | Manual, resultados de teste, mood board, referências |

Guia completo: [source/BUILDING.md](source/BUILDING.md). Plano: [PLAN.md](PLAN.md). Defeitos e ideias:
[issues](https://github.com/saulofilho/baile-fm1/issues), com a versão, o que você fez e o que aconteceu.

## Créditos e licença

BAILE, de saulofilho, sobre o trabalho de:

- **[KAWA](https://github.com/Guizmoh/Kawa-Tracker-Fm1)** e **[K-GLITCH](https://github.com/Guizmoh/K-Glitch)**, de
  Omnipotard: o motor, o tracker e os bancos DESTROI e BEAT.
- **[Felucca](https://github.com/hugelton/Felucca)**, de Leo Kuroshita (Hügelton Instruments): a plataforma, o
  atualizador e oito dos patches FM.
- **[SLOOP](https://github.com/isod89/sloop-fm1)**, de isod89, e **[Dinghy](https://github.com/zvenson/dinghy)**, de
  zvenson: a plataforma.
- **msfa**, do Google e de Pascal Gauthier, via Dexed (Apache-2.0): a síntese FM.
- As fontes Terminus, IBM Plex Mono, Atkinson Hyperlegible Mono e Press Start 2P (OFL).

**GPL-3.0-only:** você pode usar, estudar, mudar e compartilhar, e quem receber um firmware feito daqui recebe também
o código. Texto em [LICENSE](LICENSE), detalhes em [LICENSING.md](LICENSING.md). "M-VAVE" e "FM-1" pertencem aos seus
donos.
