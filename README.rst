|build| |docs| |license| |downloads| |pypi| |pyver|

PlutoPrint
==========

PlutoPrint is a lightweight and easy-to-use Python library for generating high-quality PDFs and images directly from HTML or XML content. It is based on `PlutoBook’s <https://github.com/plutoprint/plutobook>`_ robust rendering engine and provides a simple API to convert your HTML into crisp PDF documents or vibrant image files. This makes it ideal for reports, invoices, or visual snapshots.

.. list-table::
   :header-rows: 1

   * - Invoices
     - Tickets
   * - |invoices|
     - |tickets|

Installation
------------

.. code-block:: bash

   pip install plutoprint

PlutoPrint depends on `PlutoBook <https://github.com/plutoprint/plutobook>`_. For faster installation, it is highly recommended to `install PlutoBook and its dependencies manually <https://plutoprint.readthedocs.io/en/latest/getting_started.html>`_ beforehand. Otherwise, Meson will build them from source during installation, which can take significantly longer.

For Windows and Linux 64-bit users, PlutoPrint provides **prebuilt binaries**, so no additional setup is required.

Quick Usage
-----------

Generate a PDF from the command line with the installed ``plutoprint`` script:

.. code-block:: bash

   plutoprint input.html output.pdf --size=A4

Generate PDF with Python
^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: python

   import plutoprint

   book = plutoprint.Book(plutoprint.PAGE_SIZE_A4)
   book.load_url("hello.html")

   # Export the entire document to PDF
   book.write_to_pdf("hello.pdf")

   # Export pages 2 to 15 (inclusive) in order
   book.write_to_pdf("hello-range.pdf", 2, 15, 1)

   # Export pages 15 to 2 (inclusive) in reverse order
   book.write_to_pdf("hello-reverse.pdf", 15, 2, -1)

   # Render pages manually with PDFCanvas (in reverse order)
   with plutoprint.PDFCanvas("hello-canvas.pdf", book.get_page_size()) as canvas:
      canvas.scale(plutoprint.UNITS_PX, plutoprint.UNITS_PX)
      for page_index in range(book.get_page_count() - 1, -1, -1):
         canvas.set_size(book.get_page_size_at(page_index))
         book.render_page(canvas, page_index)
         canvas.show_page()

Generate PNG with Python
^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: python

   import plutoprint
   import math

   book = plutoprint.Book(media=plutoprint.MEDIA_TYPE_SCREEN)
   book.load_html("<b>Hello World</b>", user_style="body { text-align: center }")

   # Outputs an image at the document’s natural size
   book.write_to_png("hello.png")

   # Outputs a 320px wide image with auto-scaled height
   book.write_to_png("hello-width.png", width=320)

   # Outputs a 240px tall image with auto-scaled width
   book.write_to_png("hello-height.png", height=240)

   # Outputs an 800×200 pixels image (may stretch/squish content)
   book.write_to_png("hello-fixed.png", 800, 200)

   # Get the natural document size
   width = math.ceil(book.get_document_width())
   height = math.ceil(book.get_document_height())

   # Outputs a high-resolution 5x scaled image
   book.write_to_png("hello-scaled.png", width * 5, height * 5)

   # Render manually on a canvas with white background
   with plutoprint.ImageCanvas(width, height) as canvas:
      canvas.clear_surface(1, 1, 1)
      book.render_document(canvas)
      canvas.write_to_png("hello-canvas.png")

Generate Charts with Matplotlib
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: python

    import plutoprint

    import matplotlib.pyplot as plt
    import urllib.parse
    import io

    class CustomResourceFetcher(plutoprint.ResourceFetcher):
        def fetch_url(self, url):
            if not url.startswith('chart:'):
                return super().fetch_url(url)
            values = [float(v) for v in urllib.parse.unquote(url[6:]).split(',')]
            labels = [chr(65 + i) for i in range(len(values))]

            plt.bar(labels, values)
            plt.title('Bar Chart')
            plt.xlabel('Labels')
            plt.ylabel('Values')

            buffer = io.BytesIO()
            plt.savefig(buffer, format='svg', transparent=True)

            return plutoprint.ResourceData(buffer.getvalue(), "image/svg+xml", "utf-8")

    book = plutoprint.Book(plutoprint.PAGE_SIZE_A4.landscape(), plutoprint.PAGE_MARGINS_NONE)

    book.custom_resource_fetcher = CustomResourceFetcher()

    HTML_CONTENT = """
    <div>
        <img src='chart:23,45,12,36,28,50'>
        <img src='chart:5,15,25,35,45'>
        <img src='chart:50,40,30,20,10'>
        <img src='chart:10,20,30,40,50,60,70'>
    </div>
    """

    USER_STYLE = """
    div { display: flex; flex-wrap: wrap; justify-content: center; height: 98vh }
    img { flex: 0 0 45%; height: 50%; background: #fff; border: 1px solid #ccc; }
    body { background: #f7f7f7 }
    """

    book.load_html(HTML_CONTENT, USER_STYLE)
    book.write_to_png("charts.png")
    book.write_to_pdf("charts.pdf")

Expected output:

.. image:: https://raw.githubusercontent.com/plutoprint/plutoprint-samples/main/charts.png
   :alt: Charts

Samples
=======

.. list-table:: Invoices

   * - .. image:: https://raw.githubusercontent.com/plutoprint/plutoprint-samples/main/images/invoice-1.png
          :alt: Invoice 1
     - .. image:: https://raw.githubusercontent.com/plutoprint/plutoprint-samples/main/images/invoice-2.png
          :alt: Invoice 2
     - .. image:: https://raw.githubusercontent.com/plutoprint/plutoprint-samples/main/images/invoice-3.png
          :alt: Invoice 3

.. list-table:: Tickets

   * - .. image:: https://raw.githubusercontent.com/plutoprint/plutoprint-samples/main/images/ticket-1.png
          :alt: Ticket 1
     - .. image:: https://raw.githubusercontent.com/plutoprint/plutoprint-samples/main/images/ticket-2.png
          :alt: Ticket 2
   * - .. image:: https://raw.githubusercontent.com/plutoprint/plutoprint-samples/main/images/ticket-3.png
          :alt: Ticket 3
     - .. image:: https://raw.githubusercontent.com/plutoprint/plutoprint-samples/main/images/ticket-4.png
          :alt: Ticket 4

Links & Resources
=================

- Documentation: https://plutoprint.readthedocs.io
- Samples: https://github.com/plutoprint/plutoprint-samples
- Code: https://github.com/plutoprint/plutoprint
- Issues: https://github.com/plutoprint/plutoprint/issues
- Donation: https://github.com/sponsors/plutoprint

License
=======

PlutoPrint is licensed under the `MIT License <https://github.com/plutoprint/plutoprint/blob/main/LICENSE>`_, allowing for both personal and commercial use.

.. |build| image:: https://img.shields.io/github/actions/workflow/status/plutoprint/plutoprint/main.yml
   :target: https://github.com/plutoprint/plutoprint/actions
.. |docs| image:: https://img.shields.io/readthedocs/plutoprint
   :target: https://plutoprint.readthedocs.io
.. |license| image:: https://img.shields.io/pypi/l/plutoprint
   :target: https://github.com/plutoprint/plutoprint/blob/main/LICENSE
.. |downloads| image:: https://img.shields.io/pypi/dm/plutoprint
.. |pypi| image:: https://img.shields.io/pypi/v/plutoprint
   :target: https://pypi.org/project/plutoprint
.. |pyver| image:: https://img.shields.io/pypi/pyversions/plutoprint
.. |invoices| image:: https://raw.githubusercontent.com/plutoprint/plutoprint-samples/main/images/invoices.png
   :alt: Invoices
.. |tickets| image:: https://raw.githubusercontent.com/plutoprint/plutoprint-samples/main/images/tickets.jpg
   :alt: Tickets
