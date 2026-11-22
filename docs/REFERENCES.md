# Referências no FM-1 Firmware Hub

Pesquisa de 2026-11-21 no catálogo do [Hub](https://thefirmwarehub.com/) (283 firmwares de FM-1): busca por palavras
nos nomes e descrições (funk, baile, 808, tracker, break, phonk, percussão, voz…), depois leitura de **trechos** do
código de 10 deles e comparação com o BAILE. Nenhum foi instalado, compilado ou ouvido: o que está aqui vem de
código, documentação e descrição. Nada foi copiado para o BAILE.

Na busca não apareceu outro firmware de funk brasileiro. O "Dark Funk Durcal Synt" é de outro funk (broken e warped
funk, acid).

## O que vale fazer, em ordem

| # | Ideia | Referência | O BAILE hoje | Como fazer aqui | Esforço, risco |
| --- | --- | --- | --- | --- | --- |
| 1 | **808 que se ouve no alto-falante pequeno** | K-WASUB, `SUB HARMONICS`: satura só abaixo de ~90 Hz e soma apenas os harmônicos que isso cria | GRAVE+ dobra os graves e gasta o headroom | Trocar ou completar o GRAVE+: passa-baixa, saturação, subtrair o original, somar o resto | Baixo. Só inteiros nos dois, mesma família de código |
| 2 | **O bumbo abre espaço no 808** (ducking) | RHYTM-SEC-1, `duck_env`: o bumbo arma um envelope que abaixa o baixo | Não tem, só o limiter no master | Envelope inteiro armado pelas teclas 1 e 2 do kit, um valor de DUCK por projeto | Médio. A referência usa float (reescrever) e o formato do projeto precisa de um byte |
| 3 | **Grave em mono** | K-WASUB, `MONO BASS`: abaixo de 60–200 Hz os dois lados recebem o mesmo | Não tem | Dois passa-baixas de um polo no master, antes do limiter | Baixo |
| 4 | **Montagem por frase** | CHOPPAH, `brk_gen_t`: complexidade, âncora, rufo, virada e frase de 2 a 16 compassos | MONTAGE decide um pattern por vez | ÂNCORA (mantém 1, 2 e 4) e virada só no fim da frase, dentro da MONTAGE | Médio. Motor em float: levar a ideia, não o código |
| 5 | **Variação que evolui** | RHYTM-SEC-1, `evolve_bar`: cada passo guarda o seu sorteio e poucos são sorteados de novo por compasso | BEAT FUNK reescreve o pattern; VARIAR é manual | Um mapa de probabilidade por kit e até 4 passos novos por compasso | Médio. Escrever mapas de funk próprios |
| 6 | **Modo LIVE de lançar trechos** (já no TODO) | TRIBE, `switch_clip`: prepara a cópia fora do áudio e troca no fim do pattern. Bubba Machine, `scene_q`: cena em fila para o próximo compasso | Só a lista da MÚSICA | Fila de um pattern nas teclas brancas, troca no fim do compasso, piscando até entrar | Médio. Mexe no sequenciador e na UI |
| 7 | **Jogadas ao vivo** | Dark Funk Durcal, `perform.c`: segurar para mandar tudo ao eco ou reverb (THROW), DROP, mudos momentâneos por faixa | Tem ECO e SEM MELODIA, não tem throw nem drop | THROW e DROP no banco BAILE, com rampa de ~12 ms | Baixo a médio. Os 64 lugares estão ocupados |
| 8 | **Voz sintética** (já no TODO) | FMLarynx: serra, 3 formantes, vogal por passo, em inteiros. MONK-1: soa mais como canto, mas é float e usa tabelas grandes | Não tem | Presets "Ô", "AI", "EI" com 3 filtros passa-banda | Alto. Medir CPU antes |
| 9 | **Proteção de CPU** | K-WASUB, *governor*: acima de 70% do bloco tira qualidade por etapas | Só mostra CPU e MAX | Desligar primeiro o reverb, depois vozes | Médio. Só se o medidor do aparelho mostrar necessidade |

Começar por 1, 2 e 3: são o som do paredão. Cada um com teste no simulador e audição no FM-1 antes da release.

## Os 10 firmwares lidos

| Firmware | O que olhar | Arquivos | Licença |
| --- | --- | --- | --- |
| [K-WASUB](https://github.com/Guizmoh/K-WASUB_Firmware_for_FM1) | 808, grave, limiter, CPU | `source/firmware/src/ksub_dsp.c`, `docs/TECHNICAL-NOTES.md` | GPL-3.0 |
| [TRAPSTATION OS](https://github.com/sog-maker/trapstation-os) | Máquinas de 808 com glide e accent, geradores com desfazer | `firmware/src/eng_analog.c`, `firmware/src/fx.c` | GPL-3.0-only; nome, logo e arte fora da GPL |
| [RHYTM-SEC-1](https://github.com/hamperj/rhytm-sec-1) | Ducking, probabilidade por estilo, evolução | `rhytmsec1/perf/db_engine.c`, `styles.h` | GPL-3.0-only; derivado de PERF-1, HYP-1 e AMB-1 |
| [CHOPPAH](https://github.com/profikid/fm1-break-choppah) | Picotar, gerador por frase, efeito por fatia | `app/dsp/brk.h`, `app/dsp/kick.c` | MPL-2.0, arquivo por arquivo |
| [TRIBE](https://github.com/apiel/fm1-tribe) | Fila de clips | `firmware/src/tribe/engine.c` | GPL-3.0-only; várias origens |
| [Bubba Machine](https://github.com/Erbubar23/bubba-machine) | Fila de cenas, sidechain | `core/bm_seq.c`, `core/bm_audio.c` | GPL-3.0, com terceiros em `third_party/` |
| [Dark Funk Durcal Synt](https://github.com/drophlex/dark-funk-durcal-synt-fm1) | THROW, DROP, estilos em tabela | `firmware-src/firmware/src/perform.c`, `dfd.c` | GPL-3.0-only, com terceiros |
| [BEETLE BLUE](https://github.com/SikkenWorks/BEETLE-BLUE) | Riff repetível por semente, preso à escala | `firmware/fm1-native/native_performance.c` | GPL-3.0, com terceiros (há LGPL-2.1) |
| [FMLarynx](https://github.com/ejtb76/FMLarynx) | Formantes em inteiros | `app/app.c` | GPL-3.0-only; base MPL-2.0 |
| [MONK-1](https://github.com/charlesvestal/fm1-monk) | Voz por grãos | `firmware/src/dsp/monk.c` | MIT (MonkSynth) e GPL-3.0-only |

A base do BAILE não tinha commits novos depois do nosso commit de origem, na data da pesquisa.

## Antes de aproveitar código

- Ideia e lógica: pode. Escrever o nosso e citar a inspiração em `LICENSING.md`.
- Código: só com o cabeçalho e a origem de cada arquivo conferidos (vários são portes de terceiros), copyright mantido
  e linha em `LICENSING.md`. GPL-3.0 entra direto; MPL-2.0 continua MPL naquele arquivo; MIT mantém o aviso.
- FM-1 Chimera Vocal: sem licença no catálogo. Não usar o código.
- Samples, bancos, padrões de discos, nomes e arte dos outros: não. O BAILE é todo sintetizado.
- O BAILE roda só com inteiros e sem divisão de 64 bits: motor em float não entra como está.
