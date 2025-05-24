# PlutoPrint

**PlutoPrint** is a lightweight and easy-to-use Python library for generating high-quality PDFs and images directly from HTML content. Leveraging [PlutoBook's](https://github.com/plutoprint/plutobook) robust rendering engine, PlutoPrint provides a simple API to seamlessly convert your HTML into crisp PDF documents or vibrant image files, making it perfect for reports, invoices, or visual snapshots.

## Installation

```bash
pip install plutoprint
```

> **Note:** PlutoPrint depends on [PlutoBook](https://github.com/plutoprint/plutobook). For faster builds, it is highly recommended to [install PlutoBook and its dependencies manually](https://github.com/plutoprint/plutobook?tab=readme-ov-file#installation-guide) beforehand. Otherwise, Meson will build them from source during installation, which can significantly increase build time.

For Windows users, **PlutoPrint** provides prebuilt binaries, so no additional setup is required.

## Quick Usage

```python
import plutoprint

book = plutoprint.Book()
book.load_html("<b> Hello World </b>")
book.write_to_pdf("hello.pdf")
```

## Command Line Tool

**PlutoPrint** provides a flexible command-line interface (CLI) for converting HTML documents to PDF.

```bash
usage: plutoprint [-h] [--size {a3,a4,a5,b4,b5,letter,legal,ledger}]
                  [--margin MARGIN] [--media {print,screen}]
                  [--orientation {portrait,landscape}] [--margin-top MARGIN]
                  [--margin-right MARGIN] [--margin-bottom MARGIN]
                  [--margin-left MARGIN] [--width WIDTH] [--height HEIGHT]
                  [--page-start START] [--page-end END] [--page-step STEP]
                  [--user-style STYLE] [--user-script SCRIPT] [--title TITLE]
                  [--subject SUBJECT] [--author AUTHOR] [--keywords KEYWORDS]
                  [--creator CREATOR] [--version]
                  input output

Convert HTML to PDF.

positional arguments:
  input                 Specify the input HTML filename or URL.
  output                Specify the output PDF filename.

options:
  -h, --help            Show this help message and exit
  --size {a3,a4,a5,b4,b5,letter,legal,ledger}
                        Specify the page size (e.g., A4).
  --margin MARGIN       Set all margins uniformly (e.g., 72pt).
  --media {print,screen}
                        Choose media type (e.g., print, screen).
  --orientation {portrait,landscape}
                        Set page orientation.
  --margin-top MARGIN   Set top margin.
  --margin-right MARGIN Set right margin.
  --margin-bottom MARGIN Set bottom margin.
  --margin-left MARGIN  Set left margin.
  --width WIDTH         Set custom page width (e.g., 210mm).
  --height HEIGHT       Set custom page height (e.g., 297mm).
  --page-start START    First page number to include.
  --page-end END        Last page number to include.
  --page-step STEP      Step interval for pages.
  --user-style STYLE    Apply custom CSS.
  --user-script SCRIPT  Run JavaScript after page loads.
  --title TITLE         Set PDF document title.
  --subject SUBJECT     Set document subject.
  --author AUTHOR       Set author metadata.
  --keywords KEYWORDS   Set PDF keywords.
  --creator CREATOR     Set PDF creator metadata.
  --version             Show program version and exit
```

## License

**PlutoPrint** is licensed under the [MIT License](https://github.com/plutoprint/plutoprint/blob/main/LICENSE), allowing for both personal and commercial use.
