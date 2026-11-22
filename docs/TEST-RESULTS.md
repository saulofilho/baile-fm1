# BAILE — testes num FM-1 de verdade (0.1, 0.2, 0.3)

O que foi feito num M-VAVE FM-1 real, e o que ainda falta. O que não está marcado aqui não foi testado no aparelho
(só no simulador e nos testes automáticos de `source/tests/`).

## Instalação

| Data | De | Como | Resultado |
| --- | --- | --- | --- |
| 2026-11-18 | `FM-1_966` (outro firmware da comunidade, na porta "Felucca") | `install/fm1_install.py install/baile-0.1.fwsc` (macOS, Python 3.13 na `.venv` do projeto, mido + python-rtmidi) | Pacote conferido (18 leituras), modo de atualização, gravação 0–100% (uns 25 minutos), reinício: **"done: the FM-1 runs FM-1_971"**. Depois, `fm1_install.py --info`: `FM-1_971 [running]` |
| 2026-11-21 | `FM-1_971` (BAILE 0.1) | o mesmo, com `install/baile-0.2.fwsc` | Conferido (18 leituras), gravação 0–100%, reinício: **"done: the FM-1 runs FM-1_971"**; `--info`: `FM-1_971 [running]`. Uma atualização de BAILE para BAILE |
| 2026-11-21 | `FM-1_971` (BAILE 0.2) | o mesmo, com `baile-0.3.fwsc` (SHA-256 `fd0c26fc…eb966`) | Conferido (18 leituras), gravação 0–100% em cerca de 1 minuto, reinício: **"done: the FM-1 runs FM-1_808130"**; depois, lido por USB: `FM-1_808130 [running]`, versão `0.3` |

## No aparelho (BAILE 0.3)

A instalação acima foi conferida por USB. O resto espera o relato do autor, item por item.

| Roteiro | Confirmado item a item |
| --- | --- |
| O boot mostra V0.3 | a confirmar |
| As músicas da 0.2 continuam lá | a confirmar |
| Em MÚSICA (GLO) o BPM aparece com três dígitos na linha de baixo | a confirmar |
| Os 4 bancos de efeitos em português | a confirmar |
| O tema CLARO legível | a confirmar |
| A demo toca | a confirmar |
| Instalar a partir do V15 oficial | a confirmar |
| Instalar a partir de outro firmware | a confirmar |
| Sair do BAILE para outro firmware | a confirmar |

## No aparelho (BAILE 0.2, 2026-11-21)

Depois de instalar a 0.2, o autor relatou, sobre o roteiro inteiro e numa frase só: **"Testei tudo, ok"**. Não houve
relato item por item; a coluna da direita é para o autor preencher.

| Roteiro | Confirmado item a item |
| --- | --- |
| Boot (mosaico, BAILE, BETA, V0.2), uma tecla abre FAIXAS, a arara | a confirmar |
| As DEMOS (SAVE › DEMO › OCT+ › PLAY, uma por estilo: BAILE, VOLT, MANDELAO, BREGA FUNK) | a confirmar |
| Volume e distorção do 808 e do bumbo do VOLT (alto-falante e fone) | a confirmar |
| Os 8 kits (KNOB KIT, as 16 teclas brancas) | a confirmar |
| MÁGICA: BEAT FUNK, GRAVE 808, VIRADA | a confirmar |
| Efeitos ao vivo: SEGURA, PUXA, SOBE; GRAVE+ e SIRENE (banco PAREDAO) | a confirmar |
| Salvar, desligar, ligar: a música volta | a confirmar |
| Resgate USB (OCT− segurado ao ligar) | a confirmar |
| Voltar ao oficial (M-UPGRADE, V15) e reinstalar o BAILE | a confirmar |
| Uma instalação interrompida (cabo puxado) que retoma | a confirmar |

## Defeitos achados depois, lendo o código da 0.2 (corrigidos no código, não testados no aparelho)

- Os 32 efeitos dos bancos DESTROI e BEAT aparecem em francês com o idioma em português.
- Em OPCOES, o português se chama "FRANCAIS".
- Textos errados em português: "FINO" no lugar de "FIM", "SEGURO" no lugar de "SEGURE", "LONGO" no lugar de "TAM"
  (o comprimento), "PULSO" para a onda quadrada do LFO.
- A linha de baixo corta valores de 3 caracteres: BPM 130 aparece "13" e NAO aparece "NA".
- No tema CLARO muitos textos coloridos ficam ilegíveis.
- Em inglês e espanhol os bancos de efeitos ainda têm os nomes antigos (POCKET, WRECK, BOLSA, ROTO).
