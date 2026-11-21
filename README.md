# BAILE — tracker de funk brasileiro para o M-VAVE FM-1

![O boot do BAILE: o mosaico de ladrilhos nas cores da arara](docs/boot.png)

**BAILE** é um firmware livre para o **M-VAVE FM-1** feito para **funk brasileiro**: tamborzão, Volt Mix, funk 150,
mandelão, brega funk e montagem. É um *tracker*: cada linha é um passo, cada coluna uma faixa, e a música desce a
tela. Seis faixas, um sequenciador por passos, patterns encadeados numa música, 64 efeitos ao vivo, tabelas, groove
por passo e um drive em cada faixa. A tela fala **português**, inglês ou espanhol.

É um fork do [KAWA](https://github.com/Guizmoh/Kawa-Tracker-Fm1), de Omnipotard, e herda dele o motor inteiro.

> **Beta 0.2.** Kits, breaks, sons, grooves, ferramentas MÁGICA e efeitos de funk prontos, quatro demos (uma por
> estilo), interface em português. A 0.1 já foi instalada num FM-1 de verdade; o resto do teste no aparelho está em
> andamento ([docs/TEST-RESULTS.md](docs/TEST-RESULTS.md), [PLAN.md](PLAN.md)). Firmware não oficial, não
> feito nem endossado pela M-VAVE: instale por sua conta e risco.

## O visual

Um **mosaico de ladrilhos pintados à mão** sobre chão preto, nas **cores das penas da arara** (vermelho, laranja,
amarelo, verde, turquesa e azul): uma cor por faixa. O mascote, no canto de cada página, é uma **arara de
headphone** que pisca, dança com os efeitos e dorme quando você para. Temas **TERRA** (padrão), **CLARO** e
**PAREDAO**. O mood board está em [`docs/moodboard/index.html`](docs/moodboard/index.html).

## O que vem do KAWA

- **Um tracker.** Cada célula tem uma nota, um volume e até dois efeitos (arpejo, glide, rufo, chance, atraso,
  avesso, pulo, fim…). Patterns de 16, 32 ou 64 passos, encadeados numa música.
- **Seis faixas, cada uma com um motor:** pulso, onda de 4 bits, ruído, FM de 6 operadores (uma faixa), kit de
  bateria ou sample, este cortado em 16 fatias.
- **Tabelas, groove e geração:** uma tabela por faixa (uma pequena sequência dentro de cada nota), groove passo a
  passo, Euclides, acaso e picador, 64 efeitos ao vivo em quatro bancos, filtro de 11 tipos, sequenciador de
  efeitos.
- **Seus samples** (4 espaços), desfazer e refazer, música salva sozinha e três espaços de projeto, relógio MIDI.

## Os botões

| Botão | O que faz |
| --- | --- |
| **HOME** | As faixas. Segurado: a ajuda da página. **HOME + PLAY**: pânico (para tudo) |
| **SEQ** | A grade de passos. **OCT− / OCT+**: 16, 32 ou 64 passos |
| **EDIT** | O som da faixa: SOM, SOM 2, (operadores FM / edição do sample), EFEITO, TABELA |
| **LFO** | LFO, depois MODULAÇÃO |
| **ENV** | ENVELOPE, depois MIX |
| **FX** | ENVIOS, depois LIVE (64 efeitos), FILTRO, SEQ FX. Segurado: LIVE enquanto você segura |
| **SCL** | ESCALA, depois MÁGICA (batidas, melodias, picador) |
| **GLO** | MÚSICA (a sequência), GROOVE, OPÇÕES (tema, idioma, relógio, fonte, metrônomo) |
| **SAVE** | PROJETOS. Segurado: as ferramentas. **OCT− / OCT+** segurando: desfazer / refazer |
| **PLAY**, **REC** | Toca / para; grava |
| **ARP** | A tecla de apagar e de *shift* |

## Instalar

**Pelo navegador (Chrome, Edge, Opera):** abra o [hub](https://saulofilho.github.io/baile-fm1/), ligue o FM-1 com um
cabo USB de dados, feche outros programas MIDI e clique em *Instalar o BAILE*. O pacote é conferido antes de apagar
qualquer coisa; se o cabo cair, conecte de novo e clique outra vez: a instalação continua.

### Instalar sem o navegador

Precisa de [Python 3](https://www.python.org/downloads/). Baixe este repositório (*Code*, *Download ZIP*), descompacte e
rode o lançador do seu sistema: **Windows** `INSTALL-Windows.bat`, **Mac** `INSTALL-Mac.command` (na primeira vez:
botão direito, Abrir), **Linux** `./INSTALL-Linux.sh`. O pacote fica em [`install/`](install/).

## Voltar ao firmware oficial

1. Os projetos do BAILE se perdem: o firmware oficial não os lê.
2. Use uma fonte de energia estável e um cabo USB de dados. Se o BAILE estiver estranho, abra antes o resgate USB
   (segure OCT− ao ligar).
3. Instale o firmware oficial **V15** da M-VAVE com o **M-UPGRADE**.
4. **Não desconecte nada durante a transferência** (o firmware oficial reescreve também o bootloader). Se parar,
   conecte de novo e recomece.

## No computador

Tudo fica em [`source/`](source/BUILDING.md). O simulador roda no macOS e no Linux; as telas e o áudio saem em
`source/build/host/`:

```bash
python3 -m venv .venv && .venv/bin/pip install pillow
cd source && PATH="$PWD/../.venv/bin:$PATH" tests/run_host.sh
```

O pacote do FM-1 (`baile.fwsc`, identidade `FM-1_971`) é feito com `source/build.sh`, a toolchain JieLi e o SDK
AC79, como no KAWA ([BUILDING.md](source/BUILDING.md)).

## Créditos e licença

BAILE, de saulofilho, sobre o **KAWA** de **Omnipotard** (com os efeitos do K-GLITCH), que roda sobre
[Dinghy](https://github.com/zvenson/dinghy) (zvenson), [Felucca](https://github.com/hugelton/Felucca) (Leo
Kuroshita, Hügelton Instruments) e [SLOOP](https://github.com/isod89/sloop-fm1) (isod89); o motor FM é o msfa (Dexed,
Apache-2.0). GPL-3.0-only: você pode usar, mudar e compartilhar, e quem receber um firmware feito daqui recebe também
o código. Detalhes em [LICENSING.md](LICENSING.md). "M-VAVE" e "FM-1" pertencem aos seus donos.

---

**In English:** BAILE is a free Brazilian funk tracker firmware for the M-VAVE FM-1, forked from Omnipotard's KAWA.
Its screen speaks Portuguese, English or Spanish; its look is a mosaic of painted tiles in a macaw's colours. Work in
progress, not yet tested on an FM-1. GPL-3.0-only.
