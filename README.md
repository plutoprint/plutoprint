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

## License

**PlutoPrint** is licensed under the [MIT License](https://github.com/plutoprint/plutoprint/blob/main/LICENSE), allowing for both personal and commercial use.
