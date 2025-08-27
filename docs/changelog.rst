Changelog
=========

.. currentmodule:: plutoprint

.. _v0-8-0:

PlutoPrint 0.8.0 (2025-08-27)
-----------------------------

- Bump PlutoBook to v0.6.0

  - Add support for ``-pluto-qrcode()`` in CSS ``content`` property for embedding QR codes
  - Fix uninitialized table members causing large cell ``padding`` and ``border``

.. _v0-7-0:

PlutoPrint 0.7.0 (2025-08-26)
-----------------------------

- Bump PlutoBook to v0.5.0

  - Add support for ``overflow-wrap`` in inline line-breaking algorithm
  - Fix ``text-indent`` offset calculation in block-level inline formatting
  - Fix parser for ``text-decoration-line`` to return ``nullptr`` when no values are consumed
  - Fix luminance mask computation

- Provide precompiled binaries for:

  - ``cp310-macosx_14_0_arm64``
  - ``cp311-macosx_14_0_arm64``
  - ``cp312-macosx_14_0_arm64``
  - ``cp313-macosx_14_0_arm64``
  - ``cp314-macosx_14_0_arm64``

.. _v0-6-0:

PlutoPrint 0.6.0 (2025-08-24)
-----------------------------

- Bump PlutoBook to v0.4.0

  - Add support for ``text-orientation`` and ``writing-mode``
  - PNG export outputs a single continuous image (no pagination)

.. _v0-5-0:

PlutoPrint 0.5.0 (2025-08-19)
-----------------------------

- Replace the ``format`` parameter with ``width`` and ``height`` parameters in :meth:`Book.write_to_png` and :meth:`Book.write_to_png_stream`

.. _v0-4-1:

PlutoPrint 0.4.1 (2025-08-17)
-----------------------------

- Fix :class:`ResourceFetcher` instantiation error

.. _v0-4-0:

PlutoPrint 0.4.0 (2025-08-17)
-----------------------------

- Add :class:`DefaultResourceFetcher`, a default implementation of :class:`ResourceFetcher` with configuration methods for SSL and HTTP behavior:

  - :meth:`DefaultResourceFetcher.set_ssl_cainfo` - set path to a trusted CA certificate file
  - :meth:`DefaultResourceFetcher.set_ssl_capath` - set path to a trusted CA certificate directory
  - :meth:`DefaultResourceFetcher.set_ssl_verify_peer` - enable or disable SSL peer verification
  - :meth:`DefaultResourceFetcher.set_ssl_verify_host` - enable or disable SSL host name verification
  - :meth:`DefaultResourceFetcher.set_http_follow_redirects` - enable or disable automatic HTTP redirects
  - :meth:`DefaultResourceFetcher.set_http_max_redirects` - set maximum number of HTTP redirects
  - :meth:`DefaultResourceFetcher.set_http_timeout` - set maximum time for an HTTP request

- Extend ``plutoprint`` CLI with additional arguments for network configuration:

  - ``--ssl-cainfo`` - specify an SSL CA certificate file
  - ``--ssl-capath`` - specify an SSL CA certificate directory
  - ``--no-ssl`` - disable SSL verification (not recommended)
  - ``--no-redirects`` - disable following HTTP redirects
  - ``--max-redirects`` - specify maximum number of HTTP redirects
  - ``--timeout`` - specify the HTTP timeout in seconds

.. _v0-3-0:

PlutoPrint 0.3.0 (2025-08-14)
-----------------------------

- Provide precompiled binaries for:

  - **Linux**: ``cp310-manylinux_2_28_x86_64``, ``cp311-manylinux_2_28_x86_64``, ``cp312-manylinux_2_28_x86_64``, ``cp313-manylinux_2_28_x86_64``, ``cp314-manylinux_2_28_x86_64``
  - **Windows**: ``cp310-win_amd64``, ``cp311-win_amd64``, ``cp312-win_amd64``, ``cp313-win_amd64``, ``cp314-win_amd64``

- Update ``requires-python`` to ``>=3.10``

- Add functions for runtime access to version and build metadata from the underlying PlutoBook library:

  - :func:`plutobook_version`
  - :func:`plutobook_version_string`
  - :func:`plutobook_build_info`

- Add ``--info`` argument to the ``plutoprint`` CLI

.. _v0-2-0:

PlutoPrint 0.2.0 (2025-06-23)
-----------------------------

- Add Read the Docs support  
- Refactor error handling for clarity and robustness  
- Implement ``==`` and ``!=`` for :class:`PageMargins` and :class:`PageSize`  
- Update :class:`Canvas` context methods for :class:`AnyCanvas` type variable  
- Use ``is not None`` for CLI argument presence checks  
- Fix dimensions in :data:`PAGE_SIZE_LEDGER` constant  
- Add comprehensive unit tests  

.. _v0-1-0:

PlutoPrint 0.1.0 (2025-05-24)
-----------------------------

- This is the first release. Everything is new. Enjoy!
