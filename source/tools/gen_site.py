#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-only
"""BAILE's hub in two languages: index.html (Portuguese) and en/index.html (English), from source/web/hub.html; and the
bar (site.css) of the other pages: the manual, the sample importer and the emulator, in theirs.

  python3 tools/gen_site.py

The layout follows lamannabakery.com (a sticky bar with the logo in the middle, giant type, layered shadows, a turning
star, tickers, blobs, a carousel of stars, flat blocks with stickers down their sides); the colours are BAILE's.
Every text is here, once per language, so the two pages never drift apart. {{B}} is the way back to the root.
"""
import json
import math
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TEMPLATE = ROOT / "source" / "web" / "hub.html"
FAVICON = ("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 32 32'%3E%3Crect width='32' height='32' rx='7' fill='%23141210'/%3E"
           "%3Crect x='4' y='4' width='11' height='11' rx='2' fill='%23E3212B'/%3E%3Crect x='17' y='4' width='11' height='11' rx='2' fill='%23FFCF1F'/%3E"
           "%3Crect x='4' y='17' width='11' height='11' rx='2' fill='%235AAE3A'/%3E%3Crect x='17' y='17' width='11' height='11' rx='2' fill='%231F5BD6'/%3E%3C/svg%3E")
COLS = ["#E3212B", "#F26A1B", "#FFCF1F", "#5AAE3A", "#14A3A8", "#1F5BD6"]


def burst(n=18, ro=96, ri=78):
    pts = []
    for i in range(2 * n):
        r = ro if i % 2 == 0 else ri
        a = math.pi * i / n - math.pi / 2
        pts.append(f"{100 + r * math.cos(a):.1f},{100 + r * math.sin(a):.1f}")
    return " ".join(pts)


# the hall: (file, name, the Portuguese line, the English line)
HALL = [
    ("demo", "BAILE", "demo: tamborzão em lá menor, 130", "demo: a tamborzão in A minor, 130"),
    ("demo-volt", "VOLT", "demo: Miami bass em mi menor, 128", "demo: Miami bass in E minor, 128"),
    ("demo-mandelao", "MANDELAO", "demo: fá frígio, 130, GRAVE+", "demo: F Phrygian, 130, BASS+"),
    ("demo-brega", "BREGA FUNK", "demo: dó menor, 150, groove BREGA", "demo: C minor, 150, the BREGA groove"),
    ("break-tambor", "TAMBOR", "break: atabaques no 3-3-2", "break: atabaques in the 3-3-2"),
    ("break-volt", "VOLT", "break: 808 e sub", "break: 808 and sub"),
    ("break-cent50", "CENT50", "break: o 150, seco e rápido", "break: the 150, dry and fast"),
    ("break-mandela", "MANDELA", "break: sub, metal, sampler sujo", "break: sub, metal, a dirty sampler"),
    ("break-brega", "BREGA", "break: swing, timbal, palmas", "break: swing, timbales, palms"),
    ("break-montag", "MONTAG", "break: um som por semicolcheia", "break: a new sound every 16th"),
]

T = {
"pt": dict(
    lang="pt-BR", title="BAILE — tracker de funk para o M-VAVE FM-1",
    description="BAILE: um firmware livre que transforma o M-VAVE FM-1 num tracker de funk brasileiro. Instale pelo navegador.",
    nav_label="BAILE", nav_label2="Mais", nav_install="Instalar", nav_manual="Manual", nav_emu="Emulador", nav_samples="Samples",
    home_href="index.html", manual_href="manual/index.html", emu_href="emulator/index.html", samples_href="samples.html",
    cur_pt=' aria-current="page"', cur_en="",
    hero_small="o funk no seu", hero_big="FM-1",
    hero_alt="A tela de boot do BAILE: um mosaico de ladrilhos nas cores das penas da arara",
    star_install="Instalar agora",
    intro_h="tracker de funk brasileiro",
    tagline="Feito para funk brasileiro: tamborzão, Volt Mix, 150, mandelão, brega funk e montagem, 6 faixas",
    intro_p="Um firmware livre que transforma o M-VAVE FM-1 num tracker de funk: escreva os padrões em seis faixas (808, kits "
            "de baile, breaks picotados, FM, samples), encadeie numa música e toque os efeitos ao vivo. Tudo sintetizado, "
            "nada tirado de disco. Beta, GPL-3.0.",
    ticker1="".join(f"<span>{w}</span><i>✺</i>" for w in ["TAMBORZÃO", "VOLT MIX", "150", "MANDELÃO", "BREGA FUNK", "MONTAGEM"]),
    ticker2="".join(f"<span>{w}</span><i>✺</i>" for w in ["BOTA PRA TOCAR", "SEGURA", "PUXA", "SOBE", "GRAVE+", "SIRENE"]),
    made_h="Feito sobre:", hall_h="Ouça", prev="Anterior", next="Próximo",
    install_h="Instalar o BAILE",
    beta="BETA 0.2 · TESTADO NUM FM-1 DE VERDADE",
    install_steps="<li>Ligue o FM-1 e conecte-o a este computador com um cabo USB <em>de dados</em>.</li>"
                  "<li>Feche qualquer outro programa que use MIDI.</li>"
                  "<li>Clique no botão e permita o acesso MIDI com SysEx quando o navegador pedir.</li>",
    go="Instalar o BAILE", pick="Usar um arquivo .fwsc…", prog_label="Progresso da instalação", loading="Carregando…",
    keep="Gravando: não desconecte o FM-1, não feche nem recarregue esta página. Deixe esta aba na frente e o computador acordado até aparecer <em>Pronto</em>.",
    log_label="Registro da instalação",
    safety="O pacote inteiro é conferido antes de apagar qualquer coisa: um pacote danificado, ou de outro modelo, é recusado e o "
           "firmware antigo fica. O bootloader do chip nunca é gravado. Se o cabo cair durante a gravação, conecte o FM-1 de "
           "novo e clique outra vez: a instalação continua de onde parou.",
    adv="Avançado", port_label="O nome da porta MIDI contém", port_ph="(automático: FM-1)", probe="Testar a conexão",
    feat_h="O que tem",
    features=[("8 kits de baile", "VOLT, TAMBOR, 150, MANDELA, BREGA, MELODY, TUIN (sirenes, apito, tiro, o \"tuin\") e PERCUS (atabaques, surdo, cuíca, pandeiro, agogô…). Tudo sintetizado."),
              ("6 breaks", "Tamborzão, Volt, 150, mandelão, brega e montagem, cada um fatiado em 16: o picador, rolos, avesso e tom em cada célula."),
              ("Grave 808", "GRAVE 808 com glide, GRAVE TORTO, SUB, LEAD MELODY, PIANO MELODY, STAB, SIRENE. Um projeto novo já vem com o 808 e o tamborzão."),
              ("MÁGICA de funk", "BEAT FUNK escreve o ritmo do kit, GRAVE 808 a linha de baixo, MONTAGE picota o break, VIRADA fecha o compasso. Grooves TAMBOR, BREGA, 150, MANDELA."),
              ("64 efeitos ao vivo", "SEGURA, PUXA, SOBE, CORTA, ECO MC, GRAVE+, SIRENE, e os bancos DESTROI e BEAT do K-GLITCH."),
              ("4 demos, em português", "BAILE, VOLT, MANDELAO e BREGA FUNK no menu PROJETOS. A tela fala português, inglês ou espanhol, e a arara no canto pisca, dança e dorme.")],
    emu_h="Toque no navegador", emu_p="O próprio firmware, compilado para a web: o painel do FM-1, o teclado do computador ou um controlador MIDI. Sem FM-1.",
    emu_btn="Abrir o emulador", emu_alt="A página FAIXAS do BAILE com a demo tocando",
    man_h="O manual", man_p="Os botões, as páginas, os kits, a MÁGICA, o groove e um primeiro tamborzão, passo a passo, com as telas do firmware.",
    man_btn="Ler o manual", man_alt="A página MÁGICA do BAILE",
    smp_h="Os seus sons", smp_p="Converta WAV, MP3, OGG ou FLAC e mande até quatro para os espaços MEU 1 a MEU 4 pelo USB. Nada sai do seu computador.",
    smp_btn="Abrir o importador", smp_alt="O kit TAMBORZAO na página SOM",
    more_label="Navegadores e firmware oficial",
    br_h="Navegadores",
    br_p1="O instalador precisa de <strong>Web MIDI com SysEx</strong>: <strong>Chrome, Edge ou Opera</strong> num computador. Firefox e Safari não têm.",
    br_p2="Outro navegador, ou não deu certo? Use o <code>INSTALL-Windows.bat</code>, o <code>INSTALL-Mac.command</code> ou o <code>INSTALL-Linux.sh</code> do "
          "<a href=\"https://github.com/saulofilho/baile-fm1#instalar-sem-o-navegador\">repositório</a> (precisam de Python 3).",
    off_h="Voltar ao firmware oficial",
    off_p="Não curtiu? O firmware da M-VAVE volta com a ferramenta da própria M-VAVE, o <strong>M-UPGRADE</strong>. Os seus projetos do BAILE se perdem. "
          "Leia os passos antes: <a href=\"https://github.com/saulofilho/baile-fm1#voltar-ao-firmware-oficial\">README, voltar ao firmware oficial</a>. "
          "Esta página não instala o firmware oficial.",
    foot="BAILE, de saulofilho, GPL-3.0-only, sobre o KAWA de Omnipotard (com o K-GLITCH), que roda sobre Dinghy, Felucca (Leo Kuroshita, "
         "Hügelton Instruments) e SLOOP. Não é feito nem endossado pela M-VAVE. \"M-VAVE\" e \"FM-1\" pertencem aos seus donos.",
    noscript="O instalador precisa de JavaScript.",
    dlg_h="Gravar o BAILE no FM-1?",
    dlg_resume="Este FM-1 está em modo de atualização (uma instalação anterior foi interrompida): a gravação vai ser terminada.",
    dlg_strong="Não desconecte o FM-1, não feche nem recarregue esta página e não deixe o computador dormir enquanto grava. Leva alguns minutos.",
    dlg_note="Firmware beta, não oficial: por sua conta e risco.", dlg_no="Cancelar", dlg_yes="Gravar no FM-1",
    play="Ouvir",
    js=dict(err="Erro: ", errx="Erro inesperado: ",
            again="Se o FM-1 mostrar uma tela de atualização ou não ligar, conecte de novo e clique em Instalar o BAILE: a instalação continua.",
            stopped0="Parado. Nada foi gravado.", stopped="Parado.",
            leave="O FM-1 está sendo atualizado. Sair agora pode deixá-lo em modo de atualização.",
            info="Pacote {p} ({n}) no aparelho {d} na porta \"{o}\".",
            confirm="Gravar {p} no FM-1 ({d})? Não desconecte o FM-1 enquanto grava.",
            writing="Gravando ", checking="Conferindo o pacote ({n} leituras)", reading="Lendo ", downloading="Baixando o pacote…",
            checkpkg="Conferindo o pacote…", looking="Procurando o FM-1 (permita o acesso MIDI se pedir)…",
            found="FM-1 encontrado. Esperando a sua confirmação…", cancelled="Cancelado. Nada foi gravado.",
            donesite="Pronto: o FM-1 roda o BAILE ({id}).", done="Pronto: o FM-1 roda {id}.",
            probed="FM-1 encontrado na porta \"{o}\": {id}",
            inloader=", em modo de atualização (uma instalação foi interrompida: Instalar o BAILE termina).", running=", ligado.",
            noscript="O script do instalador (install/webinstall.js) não carregou.", nobrowser="Este navegador não instala o BAILE.",
            ready="Pronto para instalar.", pkg="Pacote: ",
            fromfile="Aberta de um arquivo: a página não consegue baixar o pacote. Use um arquivo .fwsc (install/baile-*.fwsc)."),
),
"en": dict(
    lang="en", title="BAILE — a funk tracker for the M-VAVE FM-1",
    description="BAILE: a free firmware that turns the M-VAVE FM-1 into a Brazilian funk tracker. Install it from the browser.",
    nav_label="BAILE", nav_label2="More", nav_install="Install", nav_manual="Manual", nav_emu="Emulator", nav_samples="Samples",
    home_href="en/index.html", manual_href="manual/en.html", emu_href="emulator/index.html#en", samples_href="samples.en.html",
    cur_pt="", cur_en=' aria-current="page"',
    hero_small="funk in your", hero_big="FM-1",
    hero_alt="BAILE's boot screen: a mosaic of tiles in the colours of a macaw's feathers",
    star_install="Install it now",
    intro_h="a Brazilian funk tracker",
    tagline="Made for Brazilian funk: tamborzão, Volt Mix, 150, mandelão, brega funk and montagem, 6 tracks",
    intro_p="A free firmware that turns the M-VAVE FM-1 into a funk tracker: write patterns on six tracks (808, baile kits, "
            "chopped breaks, FM, samples), chain them into a song and play the live effects. All synthesised, nothing taken "
            "from a record. Beta, GPL-3.0.",
    ticker1="".join(f"<span>{w}</span><i>✺</i>" for w in ["TAMBORZÃO", "VOLT MIX", "150", "MANDELÃO", "BREGA FUNK", "MONTAGEM"]),
    ticker2="".join(f"<span>{w}</span><i>✺</i>" for w in ["DROP IT", "STUTTER", "SCRATCH", "BUILD UP", "BASS+", "SIREN"]),
    made_h="Made on:", hall_h="Listen", prev="Previous", next="Next",
    install_h="Install BAILE",
    beta="BETA 0.2 · TESTED ON A REAL FM-1",
    install_steps="<li>Switch the FM-1 on and plug it into this computer with a USB <em>data</em> cable.</li>"
                  "<li>Close every other program that uses MIDI.</li>"
                  "<li>Click the button, and allow MIDI access with SysEx when the browser asks.</li>",
    go="Install BAILE", pick="Use a local .fwsc file…", prog_label="Install progress", loading="Loading…",
    keep="Writing: do not unplug the FM-1, do not close or reload this page. Keep this tab in front and the computer awake until it says <em>Done</em>.",
    log_label="Install log",
    safety="The whole package is checked before anything is erased: a damaged package, or one for another model, is refused and the "
           "old firmware stays. The chip's bootloader is never written. If the cable is cut during the write, plug the FM-1 back in "
           "and click again: the install resumes.",
    adv="Advanced", port_label="MIDI port name contains", port_ph="(automatic: FM-1)", probe="Check the connection",
    feat_h="What's inside",
    features=[("8 baile kits", "VOLT, TAMBOR, 150, MANDELA, BREGA, MELODY, TUIN (sirens, whistle, shot, the falling \"tuin\") and PERCUS (atabaques, surdo, cuíca, pandeiro, agogô…). All synthesised."),
              ("6 breaks", "Tamborzão, Volt, 150, mandelão, brega and montagem, each cut in 16 slices: the chopper, rolls, reverse and pitch in every cell."),
              ("The 808", "808 BASS with glide, BENT 808, SUB, MELODY LEAD, MELODY PIANO, STAB, SIREN. A new project starts with the 808 and the tamborzão."),
              ("Funk MAGIC", "BEAT FUNK writes the kit's rhythm, 808 BASS the bassline, MONTAGE cuts the break up, FILL ends the bar. Grooves TAMBOR, BREGA, 150, MANDELA."),
              ("64 live effects", "STUTTER, SCRATCH, BUILD-UP, GATE, MC ECHO, BASS+, SIREN, and K-GLITCH's DESTROY and BEAT banks."),
              ("4 demos, 3 languages", "BAILE, VOLT, MANDELAO and BREGA FUNK in the PROJECTS menu. The screen speaks Portuguese, English or Spanish; the macaw in the corner blinks, dances and sleeps.")],
    emu_h="Play it in the browser", emu_p="The firmware itself, compiled for the web: the FM-1's panel, the computer keyboard or a MIDI controller. No FM-1 needed.",
    emu_btn="Open the emulator", emu_alt="BAILE's TRACKS page with the demo playing",
    man_h="The manual", man_p="The buttons, the pages, the kits, MAGIC, the groove and a first tamborzão, step by step, with the firmware's screens.",
    man_btn="Read the manual", man_alt="BAILE's MAGIC page",
    smp_h="Your own sounds", smp_p="Convert WAV, MP3, OGG or FLAC and send up to four to the MY 1 to MY 4 slots over USB. Nothing leaves your computer.",
    smp_btn="Open the importer", smp_alt="The TAMBORZAO kit on the SOUND page",
    more_label="Browsers and the official firmware",
    br_h="Browsers",
    br_p1="The installer needs <strong>Web MIDI with SysEx</strong>: <strong>Chrome, Edge or Opera</strong> on a computer. Firefox and Safari do not have it.",
    br_p2="Another browser, or no luck? Use the <code>INSTALL-Windows.bat</code>, <code>INSTALL-Mac.command</code> or <code>INSTALL-Linux.sh</code> launcher of the "
          "<a href=\"https://github.com/saulofilho/baile-fm1#instalar-sem-o-navegador\">repository</a> (they need Python 3).",
    off_h="Back to the official firmware",
    off_p="Not for you? Put M-VAVE's firmware back with M-VAVE's own <strong>M-UPGRADE</strong> tool. Your BAILE projects will be lost. "
          "Read the steps first: <a href=\"https://github.com/saulofilho/baile-fm1#voltar-ao-firmware-oficial\">README, back to the official firmware</a>. "
          "This page does not install the official firmware.",
    foot="BAILE by saulofilho, GPL-3.0-only, on KAWA by Omnipotard (with K-GLITCH), which runs on Dinghy, Felucca (Leo Kuroshita, "
         "Hügelton Instruments) and SLOOP. Not made or endorsed by M-VAVE. \"M-VAVE\" and \"FM-1\" belong to their owners.",
    noscript="The installer needs JavaScript.",
    dlg_h="Write BAILE to the FM-1?",
    dlg_resume="This FM-1 is in update mode (an earlier install was cut off): the write will be finished.",
    dlg_strong="Do not unplug the FM-1, do not close or reload this page, and do not let the computer sleep while it is writing. It takes a few minutes.",
    dlg_note="Beta, unofficial firmware: at your own risk.", dlg_no="Cancel", dlg_yes="Write to the FM-1",
    play="Play",
    js=dict(err="Error: ", errx="Unexpected error: ",
            again="If the FM-1 shows an update screen or does not start, plug it in again and click Install BAILE: the install resumes.",
            stopped0="Stopped. Nothing was written.", stopped="Stopped.",
            leave="The FM-1 is being updated. Leaving now can leave it in update mode.",
            info="Package {p} ({n}) onto the device {d} on the port \"{o}\".",
            confirm="Write {p} to the FM-1 ({d})? Do not unplug the FM-1 while it is writing.",
            writing="Writing ", checking="Checking the package ({n} reads)", reading="Reading ", downloading="Downloading the package…",
            checkpkg="Checking the package…", looking="Looking for the FM-1 (allow MIDI access if asked)…",
            found="FM-1 found. Waiting for your confirmation…", cancelled="Cancelled. Nothing was written.",
            donesite="Done: the FM-1 runs BAILE ({id}).", done="Done: the FM-1 runs {id}.",
            probed="FM-1 found on the port \"{o}\": {id}",
            inloader=", in update mode (an earlier install was cut off: Install BAILE finishes it).", running=", running.",
            noscript="The installer script (install/webinstall.js) did not load.", nobrowser="This browser cannot install BAILE.",
            ready="Ready.", pkg="Package: ",
            fromfile="Opened from a file: the page cannot download the package. Use a local .fwsc file (install/baile-*.fwsc)."),
),
}


def hall(lang, B):
    out = []
    for k, (f, name, pt, en) in enumerate(HALL):
        line = pt if lang == "pt" else en
        col = COLS[k % 6]
        play = T[lang]["play"]
        out.append(
            f'    <div class="item"><button class="badge" type="button" data-m="{k}" aria-pressed="false" aria-label="{play}: {name}, {line}">'
            f'<svg viewBox="0 0 200 200" aria-hidden="true"><use href="#burst" fill="{col}" stroke="#141210" stroke-width="5"/></svg>'
            f'<canvas width="168" height="168"></canvas><span class="pl" aria-hidden="true">▶</span></button>'
            f'<b>{name}</b><span>{line}</span><audio preload="none" src="{B}docs/audio/{f}.m4a"></audio></div>')
    return "\n".join(out)


def features(lang):
    return "".join(f'<div><canvas data-m="{k + 2}" width="168" height="168"></canvas><h3>{h}</h3><p>{p}</p></div>'
                   for k, (h, p) in enumerate(T[lang]["features"]))


def render(lang, B):
    s = TEMPLATE.read_text()
    v = dict(T[lang])
    v.update(B=B, favicon=FAVICON, burst=burst(), hall_items=hall(lang, B), features=features(lang),
             js=json.dumps(v["js"], ensure_ascii=False))
    for k, val in v.items():
        if isinstance(val, str):
            s = s.replace("{{" + k + "}}", val)
    assert "{{" not in s, s[s.index("{{"):s.index("{{") + 40]
    return s


# ---- the bar of the other pages (site.css): written between <!-- bar --> and <!-- /bar --> in each of them
NAV = {"pt": [("install", "Instalar"), ("emu", "Emulador"), ("manual", "Manual"), ("samples", "Samples")],
       "en": [("install", "Install"), ("emu", "Emulator"), ("manual", "Manual"), ("samples", "Samples")]}
HREF = {"pt": dict(home="index.html", install="index.html#install", emu="emulator/index.html", manual="manual/index.html",
                   samples="samples.html"),
        "en": dict(home="en/index.html", install="en/index.html#install", emu="emulator/index.html#en", manual="manual/en.html",
                   samples="samples.en.html")}
# each page: its file, its language, the way back to the root, which link it is, its twin in the other language
PAGES = [("manual/index.html", "pt", "../", "manual", "manual/en.html"),
         ("manual/en.html", "en", "../", "manual", "manual/index.html"),
         ("samples.html", "pt", "", "samples", "samples.en.html"),
         ("samples.en.html", "en", "", "samples", "samples.html"),
         ("source/web/emulator.html", "pt", "../", "emu", None)]


def page_bar(lang, B, cur, twin):
    h, n = HREF[lang], dict(NAV[lang])
    a = lambda k: f'<a href="{B}{h[k]}"' + (' aria-current="page"' if k == cur else "") + f">{n[k]}</a>"
    if twin is None:                        # the emulator: one page, its language in the hash
        pt, en = f'<a href="{B}emulator/index.html#pt" data-lang-link="pt">PT</a>', f'<a href="{B}emulator/index.html#en" data-lang-link="en">EN</a>'
    else:
        here = '<a href="#" aria-current="page">{}</a>'
        other = '<a href="' + B + twin + '" hreflang="{}">{}</a>'
        pt = here.format("PT") if lang == "pt" else other.format("pt-BR", "PT")
        en = here.format("EN") if lang == "en" else other.format("en", "EN")
    return ("<!-- bar -->\n"
            f'<header class="sbar">\n  <nav aria-label="BAILE">{a("install")}{a("manual")}</nav>\n'
            f'  <a class="slogo" href="{B}{h["home"]}" aria-label="BAILE"><img src="{FAVICON}" alt="">BAILE</a>\n'
            f'  <nav class="r" aria-label="BAILE">{a("emu")}{a("samples")}<span class="slangs">{pt}{en}</span></nav>\n</header>\n'
            f'<nav class="smnav" aria-label="BAILE">{a("install")}{a("emu")}{a("manual")}{a("samples")}</nav>\n'
            "<!-- /bar -->")


def bars():
    import re
    for f, lang, B, cur, twin in PAGES:
        p = ROOT / f
        if not p.exists():
            continue
        s = p.read_text()
        if "<!-- bar -->" not in s:
            print("   (no <!-- bar --> in", f + ")")
            continue
        s = re.sub(r"<!-- bar -->.*?<!-- /bar -->", lambda m: page_bar(lang, B, cur, twin), s, count=1, flags=re.S)
        p.write_text(s)
        print("-> the bar of", f)


def samples_en():
    """samples.en.html: samples.html with its Portuguese lines put back into English (tools/samples_en.json)"""
    s = (ROOT / "samples.html").read_text()
    for pt, en in json.loads((ROOT / "source" / "tools" / "samples_en.json").read_text()):
        if pt not in s:
            print("   (samples_en.json: not in samples.html:", pt[:60] + ")")
        s = s.replace(pt, en)
    (ROOT / "samples.en.html").write_text(s)
    print("-> samples.en.html")


def main():
    samples_en()
    (ROOT / "index.html").write_text(render("pt", ""))
    (ROOT / "en").mkdir(exist_ok=True)
    (ROOT / "en" / "index.html").write_text(render("en", "../"))
    print("-> index.html, en/index.html")
    bars()


if __name__ == "__main__":
    main()
