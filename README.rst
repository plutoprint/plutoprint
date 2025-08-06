|build| |docs| |license| |downloads| |pypi| |pyver|

PlutoPrint
==========

PlutoPrint is a lightweight and easy-to-use Python library for generating high-quality PDFs and images directly from HTML or XML content. It is based on `PlutoBook’s <https://github.com/plutoprint/plutobook>`_ robust rendering engine and provides a simple API to convert your HTML into crisp PDF documents or vibrant image files. This makes it ideal for reports, invoices, or visual snapshots.

Installation
------------

.. code-block:: bash

   pip install plutoprint

PlutoPrint depends on `PlutoBook <https://github.com/plutoprint/plutobook>`_. For faster builds, it is highly recommended to `install PlutoBook and its dependencies manually <https://github.com/plutoprint/plutobook?tab=readme-ov-file#installation-guide>`_ beforehand. Otherwise, Meson will build them from source during installation, which can significantly increase build time.

For Windows 64-bit users, PlutoPrint provides prebuilt binaries, so no additional setup is required.

Quick Usage
-----------

Generate a PDF from the command line with the installed ``plutoprint`` script:

.. code-block:: bash

   plutoprint input.html output.pdf --size=A4

**Generate PDF with Python**

.. code-block:: python

   import plutoprint

   book = plutoprint.Book(plutoprint.PAGE_SIZE_A4)
   book.load_url("input.html")
   book.write_to_pdf("output.pdf")

**Generate PNG with Python**

.. code-block:: python

   import plutoprint
   import math

   book = plutoprint.Book(media=plutoprint.MEDIA_TYPE_SCREEN)
   book.load_html("<b>Hello World</b>", user_style="body { text-align: center }")

   width = math.ceil(book.get_document_width())
   height = math.ceil(book.get_document_height())

   with plutoprint.ImageCanvas(width, height) as canvas:
      canvas.clear_surface(1, 1, 1)
      book.render_document(canvas)
      canvas.write_to_png("hello.png")

Samples
=======

Invoices
--------

.. raw:: html

    <p align="center">
      <img src="https://github.com/sammycage/plutoprint-samples/blob/main/images/invoices.png" alt="Invoices">
    </p>

**Invoice 1**

.. code-block:: bash

   plutoprint invoice-1.html invoice-1.pdf --margin=0.5in

.. raw:: html

    <div align="center">
      <img width="800" src="https://github.com/sammycage/plutoprint-samples/blob/main/images/invoice-1.png" alt="Invoice 1">
    </div>

**Invoice 2**

.. code-block:: bash

   plutoprint invoice-2.html invoice-2.pdf --margin=0.5in

.. raw:: html

    <div align="center">
      <img width="800" src="https://github.com/sammycage/plutoprint-samples/blob/main/images/invoice-2.png" alt="Invoice 2">
    </div>

**Invoice 3**

.. code-block:: bash

   plutoprint invoice-3.html invoice-3.pdf --margin=0.5in

.. raw:: html

    <div align="center">
      <img width="800" src="https://github.com/sammycage/plutoprint-samples/blob/main/images/invoice-3.png" alt="Invoice 3">
    </div>

Tickets
-------

.. raw:: html

    <p align="center">
      <img src="https://github.com/sammycage/plutoprint-samples/blob/main/images/tickets.jpg" alt="Tickets">
    </p>

**Ticket 1**

.. code-block:: bash

   plutoprint ticket-1.html ticket-1.pdf --margin=0.5in

.. raw:: html

    <div align="center">
      <img src="https://github.com/sammycage/plutoprint-samples/blob/main/images/ticket-1.png" alt="Ticket 1">
    </div>

**Ticket 2**

.. code-block:: bash

   plutoprint ticket-2.html ticket-2.pdf --margin=0.5in

.. raw:: html

    <div align="center">
      <img src="https://github.com/sammycage/plutoprint-samples/blob/main/images/ticket-2.png" alt="Ticket 2">
    </div>

**Ticket 3**

.. code-block:: bash

   plutoprint ticket-3.html ticket-3.pdf --margin=0.5in

.. raw:: html

    <div align="center">
      <img src="https://github.com/sammycage/plutoprint-samples/blob/main/images/ticket-3.png" alt="Ticket 3">
    </div>

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
