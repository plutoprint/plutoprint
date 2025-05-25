# PlutoPrint

**PlutoPrint** is a lightweight and easy-to-use Python library for generating high-quality PDFs and images directly from HTML content. Leveraging [PlutoBook's](https://github.com/plutoprint/plutobook) robust rendering engine, PlutoPrint provides a simple API to seamlessly convert your HTML into crisp PDF documents or vibrant image files, making it perfect for reports, invoices, or visual snapshots.

## Installation

```bash
pip install plutoprint
```

> **Note:** PlutoPrint depends on [PlutoBook](https://github.com/plutoprint/plutobook). For faster builds, it is highly recommended to [install PlutoBook and its dependencies manually](https://github.com/plutoprint/plutobook?tab=readme-ov-file#installation-guide) beforehand. Otherwise, Meson will build them from source during installation, which can significantly increase build time.

For Windows 64-bit users, **PlutoPrint** provides prebuilt binaries, so no additional setup is required.

## Quick Usage

```python
import plutoprint

book = plutoprint.Book()
book.load_html("<b> Hello World </b>")
book.write_to_pdf("hello.pdf")
```

## Command Line Tool

**PlutoPrint** provides a flexible command-line interface (CLI) for converting HTML documents to PDF.

```
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
  -h, --help            show this help message and exit
  --size {a3,a4,a5,b4,b5,letter,legal,ledger}
                        Specify the page size (eg. A4).
  --margin MARGIN       Specify the page margin (eg. 72pt).
  --media {print,screen}
                        Specify the media type (eg. print, screen).
  --orientation {portrait,landscape}
                        Specify the page orientation (eg. portrait,
                        landscape).
  --margin-top MARGIN   Specify the page margin top (eg. 72pt).
  --margin-right MARGIN
                        Specify the page margin right (eg. 72pt).
  --margin-bottom MARGIN
                        Specify the page margin bottom (eg. 72pt).
  --margin-left MARGIN  Specify the page margin left (eg. 72pt).
  --width WIDTH         Specify the page width (eg. 210mm).
  --height HEIGHT       Specify the page height (eg. 297mm).
  --page-start START    Specify the starting page number to include in the
                        output PDF.
  --page-end END        Specify the ending page number to include in the
                        output PDF.
  --page-step STEP      Specify the step value when iterating through pages.
  --user-style STYLE    Specify the user-defined CSS style to apply to the
                        input document.
  --user-script SCRIPT  Specify the user-defined JavaScript to run after the
                        document has fully loaded.
  --title TITLE         Set PDF document title.
  --subject SUBJECT     Set PDF document subject.
  --author AUTHOR       Set PDF document author.
  --keywords KEYWORDS   Set PDF document keywords.
  --creator CREATOR     Set PDF document creator.
  --version             show program's version number and exit
```

## License

**PlutoPrint** is licensed under the [MIT License](https://github.com/plutoprint/plutoprint/blob/main/LICENSE), allowing for both personal and commercial use.
