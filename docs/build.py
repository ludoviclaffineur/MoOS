#!/usr/bin/env python3
"""Génère le site GitHub Pages de MoOS (docs/_site) à partir de docs/manuel.md.

    pip install -r docs/requirements.txt
    python docs/build.py            # -> docs/_site/index.html + assets
"""

import html
import re
import shutil
from datetime import date
from pathlib import Path

import markdown

DOCS = Path(__file__).resolve().parent
OUT = DOCS / "_site"


def render_manual() -> tuple[str, list[tuple[str, str]]]:
    md = markdown.Markdown(
        extensions=["tables", "fenced_code", "sane_lists", "toc"],
        extension_configs={"toc": {"toc_depth": "2"}},
    )
    body = md.convert((DOCS / "manuel.md").read_text(encoding="utf-8"))

    # Le schéma est inséré en SVG inline pour suivre le thème (clair / sombre)
    svg = (DOCS / "assets" / "pipeline.svg").read_text(encoding="utf-8")
    body = body.replace("<!-- diagram:pipeline -->", f'<figure class="diagram">{svg}</figure>')

    # Tableaux larges : défilement horizontal sur mobile
    body = re.sub(r"<table>", '<div class="table-wrap"><table>', body)
    body = body.replace("</table>", "</table></div>")

    toc = [(t["id"], t["name"]) for t in md.toc_tokens]
    return body, toc


def main() -> None:
    body, toc = render_manual()
    nav = "\n".join(f'<a href="#{i}">{html.escape(html.unescape(n))}</a>' for i, n in toc)
    page = (DOCS / "template.html").read_text(encoding="utf-8")
    page = (page.replace("{{nav}}", nav)
                .replace("{{content}}", body)
                .replace("{{year}}", str(date.today().year)))

    if OUT.exists():
        shutil.rmtree(OUT)
    OUT.mkdir()
    (OUT / "index.html").write_text(page, encoding="utf-8")
    shutil.copytree(DOCS / "assets", OUT / "assets")
    (OUT / ".nojekyll").touch()  # servir les fichiers tels quels
    print(f"Site généré dans {OUT}")


if __name__ == "__main__":
    main()
