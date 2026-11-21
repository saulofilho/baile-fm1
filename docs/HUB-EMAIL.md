# E-mail para o FM-1 Firmware Hub (rascunho)

Mandar só depois do push da tag `v0.2` e de a release aparecer no GitHub com o `baile-0.2.fwsc` anexado (o workflow
`release.yml` compila e assina com `zvenson/fm1-build@v1`). Como no COQUÍ: o Hub pede por e-mail o nome, o autor, o
repositório, a identidade `FM-1_`, a licença e a declaração de teste num FM-1 de verdade; texto, imagem e links vão
no `fmhub.json` (na raiz do repositório).

**Para:** zven@thefirmwarehub.com
**Assunto:** New firmware for the hub: BAILE (FM-1_971)

---

Hi zven,

I'd like to submit BAILE for the FM-1 Firmware Hub.

- Firmware: BAILE, a Brazilian funk tracker for the FM-1 (tamborzao, Volt Mix, 150, mandelao, brega funk), a fork of
  KAWA 0.10 by Omnipotard
- Author, as it should appear: saulofilho
- Repository: https://github.com/saulofilho/baile-fm1
- Identity: FM-1_971 (every release; KAWA keeps its FM-1_957)
- Licence: GPL-3.0-only (LICENSE and LICENSING.md in the repository root; credits to KAWA and K-GLITCH by Omnipotard,
  Dinghy, Felucca and SLOOP)
- Releases: GitHub releases with the .fwsc attached, built and attested with zvenson/fm1-build@v1
- Update loader: Felucca's, in the package
- Newer FM-1s: both flash IDs accepted (0x856014 and 0xB36014)
- fmhub.json: in the repository root (card: docs/boot.png; play: the web emulator)
- Sounds: everything is synthesised by the firmware (kits, breaks, factory sounds); no recording is used

Tested on a real FM-1: 0.1 installed from another firmware (FM-1_966), then 0.2 over it; the demos, the kits, the
magic tools, the live effects, saving and power cycling, the USB rescue (OCT- at power-on), going back to the official
firmware with M-UPGRADE and installing BAILE again, and an interrupted install resumed by the installer. The results:
https://github.com/saulofilho/baile-fm1/blob/main/docs/TEST-RESULTS.md

Thanks for the hub!

saulofilho
