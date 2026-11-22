# BAILE: tracker de funk brasileiro para o M-VAVE FM-1

**Português** · [English](README.en.md)

<p align="center">
  <img src="docs/screens/pt/boot.png" width="220" height="220" alt="O boot: o mosaico">
  <img src="docs/screens/pt/tracks.png" width="220" height="220" alt="FAIXAS: a música desce a tela">
  <img src="docs/screens/pt/live-baile.png" width="220" height="220" alt="Banco BAILE">
</p>

**BAILE** é um firmware livre para o **M-VAVE FM-1**, feito para **funk brasileiro**: tamborzão, Volt Mix, funk 150,
mandelão, brega funk e montagem. É um *tracker*: cada linha é um passo, cada coluna uma faixa, e a música desce a
tela.

[Site e instalador](https://saulofilho.github.io/baile-fm1/) ·
[Emulador](https://saulofilho.github.io/baile-fm1/emulator/) ·
[Manual](https://saulofilho.github.io/baile-fm1/manual/) ·
[Importador de samples](https://saulofilho.github.io/baile-fm1/samples.html) ·
[Releases](https://github.com/saulofilho/baile-fm1/releases)

**Índice:** [telas](#veja-na-tela) · [estado](#estado) · [próxima versão](#próxima-versão-04) · [o que tem](#o-que-tem) · [primeiro tamborzão](#primeiro-tamborzão) ·
[botões](#botões) · [instalar](#instalar) · [samples](#seus-samples) · [compatibilidade](#compatibilidade) ·
[resgate](#resgate) · [voltar ao oficial](#voltar-ao-firmware-oficial) · [compilar](#compilar-e-testar) ·
[créditos](#créditos-e-licença)

## Veja na tela

Telas do firmware da 0.3, tiradas no simulador com a demo BAILE.

### Montar a batida

<table>
  <tr>
    <td align="center"><img src="docs/screens/pt/boot.png" width="240" height="240" alt="O boot: o mosaico"><br>O boot: o mosaico</td>
    <td align="center"><img src="docs/screens/pt/tracks.png" width="240" height="240" alt="FAIXAS: a música desce a tela"><br>FAIXAS: a música desce a tela</td>
    <td align="center"><img src="docs/screens/pt/grid.png" width="240" height="240" alt="GRADE: os 16 passos"><br>GRADE: os 16 passos</td>
  </tr>
</table>

### Som

<table>
  <tr>
    <td align="center"><img src="docs/screens/pt/bass.png" width="240" height="240" alt="SOM: o GRAVE 808"><br>SOM: o GRAVE 808</td>
    <td align="center"><img src="docs/screens/pt/kit.png" width="240" height="240" alt="SOM: o kit TAMBOR"><br>SOM: o kit TAMBOR</td>
    <td align="center"><img src="docs/screens/pt/mix.png" width="240" height="240" alt="MIX: as seis faixas"><br>MIX: as seis faixas</td>
  </tr>
</table>

### Funk

<table>
  <tr>
    <td align="center"><img src="docs/screens/pt/magic.png" width="240" height="240" alt="MÁGICA: escreve o funk"><br>MÁGICA: escreve o funk</td>
    <td align="center"><img src="docs/screens/pt/groove.png" width="240" height="240" alt="GROOVE: o atraso do tamborzão"><br>GROOVE: o atraso do tamborzão</td>
    <td align="center"><img src="docs/screens/pt/song.png" width="240" height="240" alt="MÚSICA: patterns em sequência"><br>MÚSICA: patterns em sequência</td>
  </tr>
</table>

### Ao vivo

<table>
  <tr>
    <td align="center"><img src="docs/screens/pt/live-baile.png" width="240" height="240" alt="Banco BAILE"><br>Banco BAILE</td>
    <td align="center"><img src="docs/screens/pt/live-paredao.png" width="240" height="240" alt="Banco PAREDAO"><br>Banco PAREDAO</td>
    <td align="center"><img src="docs/screens/pt/playing.png" width="240" height="240" alt="Tocando"><br>Tocando</td>
  </tr>
</table>

### Destruir

<table>
  <tr>
    <td align="center"><img src="docs/screens/pt/live-destroy.png" width="240" height="240" alt="Banco DESTROI"><br>Banco DESTROI</td>
    <td align="center"><img src="docs/screens/pt/live-beat.png" width="240" height="240" alt="Banco BEAT"><br>Banco BEAT</td>
    <td align="center"><img src="docs/screens/pt/projects.png" width="240" height="240" alt="PROJETOS e as demos"><br>PROJETOS e as demos</td>
  </tr>
</table>

### Temas

<table>
  <tr>
    <td align="center"><img src="docs/screens/pt/options.png" width="240" height="240" alt="TERRA"><br>TERRA</td>
    <td align="center"><img src="docs/screens/pt/theme-claro.png" width="240" height="240" alt="CLARO"><br>CLARO</td>
    <td align="center"><img src="docs/screens/pt/theme-paredao.png" width="240" height="240" alt="PAREDAO"><br>PAREDAO</td>
  </tr>
</table>

## Estado

| | |
| --- | --- |
| Versão | **0.3 beta** |
| Identidade | `FM-1_808130` a partir da 0.3. A 0.1 e a 0.2 respondem `FM-1_971` |
| No FM-1 de verdade | A 0.1 foi instalada a partir de outro firmware (`FM-1_966`), a 0.2 por cima dela e a 0.3 por cima da 0.2. O roteiro de testes da 0.3 está aberto: [resultados](docs/TEST-RESULTS.md) |
| Ainda não confirmado | Instalar a partir do V15 oficial e voltar para ele |
| Mudou na 0.3 | Identidade nova, interface em português sem francês, valores inteiros na linha de baixo (BPM 130), tema CLARO legível |

Firmware não oficial, não feito nem endossado pela M-VAVE. Instale por sua conta e risco.

## Próxima versão (0.4)

**Ainda não lançada, e não testada no FM-1:** está no código. O instalador e a release continuam na 0.3. Cada
melhoria entra aqui quando é feita. O que vem depois está no [roteiro](PLAN.md#roteiro).

### GRAVE+ que se ouve no celular

O GRAVE+ (banco PAREDAO) agora soma ao grave os **harmônicos** que o ouvido usa para reconstruir um 808 num
alto-falante pequeno, que não toca a fundamental.

| | 0.3 | 0.4 |
| --- | --- | --- |
| Senoide de 41 a 82 Hz, o que sobra acima de 200 Hz | −49 a −21 dB | **−21 a −12 dB** |
| Pico do master nas 4 demos | referência | igual |
| Apertar e soltar | estalava | **sem estalo** |
| Peso da fundamental | referência | cerca de 2 dB menor |

Músicas com GRAVE+ gravado, como a demo MANDELAO, mudam de som. O efeito pesa mais no processador enquanto está
ligado: +18% no computador, ainda não medido no FM-1.

### DUCK: o bumbo abre espaço

<p align="center">
  <img src="docs/screens/pt/sends.png" width="240" height="240" alt="ENVIOS com a coluna DUCK">
</p>

Cada faixa pode **recuar quando o bumbo bate**, e o 808 para de brigar com ele.

1. **FX** uma vez: ENVIOS.
2. Escolha a faixa do baixo com **ALGORITHM**.
3. **KNOB 4**: DUCK de 0 a 15 (8 recua uns 5 dB, 15 uns 18 dB).

- O bumbo é a **tecla 1 ou 2 de qualquer faixa de KIT**. Bumbos de break (SAMPLE) não disparam.
- A faixa de kit não recua no próprio bumbo. Kit mudo não dispara, kit com VOL 0 dispara (bumbo fantasma).
- Desce em 3 ms, segura 25 ms e volta em uns 90 ms. Uma batida fraca recua menos.
- O valor é salvo no projeto. **Músicas da 0.3 abrem com DUCK 0**, e com 0 o DUCK não muda um sample. A 0.3 também
  abre projetos salvos com DUCK, só não o aplica.

### Site: emulador e importador no desenho novo

O [emulador](https://saulofilho.github.io/baile-fm1/emulator/) e o
[importador de samples](https://saulofilho.github.io/baile-fm1/samples.html) ficam com a cara do site: título gigante,
letreiro, blocos de cor e rodapé.

- No emulador, o FM-1 continua escuro, como o de verdade, e a barra segue o idioma escolhido.
- O aviso do emulador agora diz o que foi instalado num FM-1 e que ele pode estar à frente da release.
- No importador em inglês, a onda voltou às cores do BAILE. O seletor de espaço voltou ao tamanho normal.

### O que vem

| Versão | O quê |
| --- | --- |
| 0.4 | Falta o grave em mono |
| 0.5 | Montagem por frase, THROW e DROP ao vivo, modo LIVE de lançar patterns |
| 0.6 | Voz sintética por formantes |
| 1.0 | Tudo testado no FM-1 e listado no Hub |

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
  dos outros sons de fábrica.
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
.venv/bin/python install/fm1_install.py install/baile-0.3.fwsc
```

O pacote é conferido inteiro antes de apagar qualquer coisa. A gravação levou de 1 a 25 minutos nos nossos
testes. Não desligue. Se o cabo cair, ligue de novo e repita: a instalação continua. Para ver o que está instalado,
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

- **O BAILE não lê projetos nem samples do firmware oficial ou de qualquer outro firmware**, e eles não leem
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
| GRAVE+ e DUCK | `tests/run_bass_test.sh`, `tests/run_duck_test.sh` |
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

BAILE, de saulofilho, é derivado de software livre. A autoria e a licença de cada parte estão em
[LICENSING.md](LICENSING.md).

**GPL-3.0-only:** você pode usar, estudar, mudar e compartilhar, e quem receber um firmware feito daqui recebe também
o código. Texto em [LICENSE](LICENSE), detalhes em [LICENSING.md](LICENSING.md). "M-VAVE" e "FM-1" pertencem aos seus
donos.
