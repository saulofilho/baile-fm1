# Formulário do FM-1 Firmware Hub

<https://thefirmwarehub.com/submit/>, regras em <https://thefirmwarehub.com/fmhub.md> (lidas em 2026-11-21). O
formulário substitui o rascunho de e-mail que ficava aqui. Quem preenche e envia é o autor.

## Antes de enviar

- [ ] **Identidade.** `FM-1_971` está "In use: inside the range of zp12" no verificador do Hub. `FM-1_808130` e
      `FM-1_971130` estavam livres em 2026-11-21. Conferir de novo no dia.
- [ ] **`sounds` no `fmhub.json`.** O valor de hoje não está num dos formatos aceitos. É uma declaração do autor.
      Sugestão, porque oito patches FM são da Felucca e outros sons são do KAWA:
      `licensed: FM presets from Felucca and factory sounds from KAWA (BAILE's own kits and breaks are synthesised), GPL-3.0`
- [ ] **Push**, para o emulador do link `play` e o README valerem.
- [ ] **Release 0.3** com as correções e a identidade nova.
- [ ] **No FM-1, com a release 0.3:** instalar a partir do **V15 oficial**; instalar a partir de **outro firmware**;
      do BAILE, instalar outro firmware. Só então marcar a caixa de testado.
- [ ] Conferir o arquivo em <https://thefirmwarehub.com/kb/#fmhub>.

## Os campos

**For which device?**

    M-VAVE FM-1

**Repository**

    https://github.com/saulofilho/baile-fm1

**Name of the firmware**

    BAILE

**Your name, as it should appear**

    saulofilho

**Your address:** o e-mail do autor, digitado por ele.

**What it is, in one line** (até 160)

    A Brazilian funk tracker: tamborzao, Volt Mix, 150, mandelao and brega funk, with eight synthesised kits, breaks to chop, 808 bass and 64 live effects

**Which device?**, **VIBE features**, **VIBE Box Challenge:** em branco.

**How you tested it** (até 600; só depois dos testes acima, tirando o que não tiver sido feito)

    On a real FM-1, with this release: installed from the official V15 and from GR!MM, left to V15 with M-UPGRADE and installed BAILE again. Installed another community firmware from BAILE too. Checked the identity over USB, the demos, the kits, the live effects, saving through a power cycle and the USB rescue.

**Anything Sven should know** (até 2000)

    BAILE is a GPL-3.0-only fork of KAWA 0.10 by Omnipotard (with K-GLITCH's live effects), on Felucca, SLOOP and Dinghy; credits and licences are in LICENSING.md. It has its own identity and keeps Felucca's update loader. It accepts both flash IDs (0x856014 and 0xB36014). It does not read other firmwares' projects or samples, as the README says. The kits and breaks are synthesised; eight FM presets come from Felucca and other factory sounds from KAWA, both GPL-3.0. The audio files in docs/audio are renders of this firmware for the web page. Releases are built and signed on GitHub with zvenson/fm1-build@v1. The screen speaks Portuguese (the default), English and Spanish; the site, manual and README are in Portuguese and English.

**As duas caixas** (testado; direitos dos sons): marcar só quando forem verdade.
