# BAILE — testes num FM-1 de verdade (0.1, 0.2)

O que foi feito num M-VAVE FM-1 real, e o que ainda falta. O que não está marcado aqui não foi testado no aparelho
(só no simulador e nos testes automáticos de `source/tests/`).

## Instalação

| Data | De | Como | Resultado |
| --- | --- | --- | --- |
| 2026-11-18 | `FM-1_966` (outro firmware da comunidade, na porta "Felucca") | `install/fm1_install.py install/baile-0.1.fwsc` (macOS, Python 3.13 na `.venv` do projeto, mido + python-rtmidi) | Pacote conferido (18 leituras), modo de atualização, gravação 0–100% (uns 25 minutos), reinício: **"done: the FM-1 runs FM-1_971"**. Depois, `fm1_install.py --info`: `FM-1_971 [running]` |
| 2026-11-21 | `FM-1_971` (BAILE 0.1) | o mesmo, com `install/baile-0.2.fwsc` | Conferido (18 leituras), gravação 0–100%, reinício: **"done: the FM-1 runs FM-1_971"**; `--info`: `FM-1_971 [running]`. Uma atualização de BAILE para BAILE |

## No aparelho

| O quê | Resultado |
| --- | --- |
| Boot (mosaico, BAILE, BETA, V0.1), uma tecla abre FAIXAS, a arara | a testar |
| A DEMO (SAVE › DEMO › OCT+ OCT+ › PLAY): tamborzão, 808, refrão, virada | a testar |
| Volume e distorção do 808 e do bumbo do VOLT (alto-falante e fone) | a testar |
| Os 8 kits (KNOB KIT, as 16 teclas brancas) | a testar |
| MÁGICA: BEAT FUNK, GRAVE 808, VIRADA | a testar |
| Efeitos ao vivo: SEGURA, PUXA, SOBE; GRAVE+ e SIRENE (banco PAREDAO) | a testar |
| Salvar, desligar, ligar: a música volta | a testar |
| Resgate USB (OCT− segurado ao ligar) | a testar |
| Voltar ao oficial (M-UPGRADE, V15) e reinstalar o BAILE | a testar |
| Uma instalação interrompida (cabo puxado) que retoma | a testar (testado só no simulador do loader) |
