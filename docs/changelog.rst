Changelog
=========

.. currentmodule:: plutoprint

.. _v0-23-0:

PlutoPrint 0.23.0 (2026-10-20)
------------------------------

- Add support for Python 3.15
- Update macOS runner and deployment target to macOS 15
- Bump PlutoBook to v0.20.0

  * Add support for fragmenting flex containers across pages and columns
  * Add support for pagination in single-column multicolumn layout
  * Add support for PDF metadata from HTML ``<meta>`` (``author``, ``description``, ``keywords``, ``generator``)
  * Add support for flex item automatic minimum size (``min-width: auto`` and ``min-height: auto``)
  * Add support for PDF title from the SVG ``<title>`` of standalone SVG documents
  * Add default styling for ``<details>``, ``<summary>``, and ``<dialog>``
  * Add support for non-ASCII CSS identifiers and escapes
  * Add automatic decompression of compressed HTTP responses
  * Add support for the case-sensitive ``s`` attribute selector flag
  * Add built-in ``disclosure-open`` and ``disclosure-closed`` list markers with RTL support
  * Fix several memory safety and crash issues in HTML parsing, CSS processing, and layout
  * Fix table row fragmentation with repeated headers and footers
  * Fix painting order of stacking context backgrounds and negative z-index children
  * Fix ``:has()`` and descendant selector matching
  * Fix flex free space distribution, gaps, auto margins, baselines, and ``wrap-reverse``
  * Fix table column widths with ``colspan``, fixed widths, and percentage columns
  * Fix table height distribution across rows, rowspans, and sections
  * Fix replaced element sizing with aspect ratios, min and max constraints, and override sizes
  * Fix block-in-inline splitting, relative positioning, and painting of split inline boxes
  * Fix float positioning and stale floats during relayout
  * Fix propagation of forced breaks from first and last children
  * Fix metadata from a previously loaded document carrying over to new content
  * Fix ``text-transform`` to use the element language and ICU word boundaries
  * Fix bidi handling for RTL blocks containing only Latin text
  * Fix ``@counter-style`` duplicates, ``extends`` fallback, and negative values
  * Fix ``list-item`` counter semantics for lists and ``<li value>``
  * Fix modern and legacy CSS color syntax parsing
  * Fix media query parsing of unknown media types and ``not`` conditions
  * Fix HTML tree construction for end tags, duplicate attributes, CDATA, and ``tfoot`` foster parenting
  * Fix ``data:`` URL parsing and MIME type detection from file extensions
  * Fix multicolumn column count, ``min-height``, and ``max-height``
  * Fix out-of-flow positioned boxes being painted as part of multicolumn content
  * Fix collapsed borders on column groups and rowspan cells
  * Fix SVG intrinsic sizing when ``width``, ``height``, or ``viewBox`` is missing
  * Fix percentage vertical margins and padding on positioned boxes
  * Fix border painting for thin ``double`` borders and short dashed or dotted sides
  * Replace custom URL parser with Ada for WHATWG-compliant URL handling
  * Fail HTTP resource fetches on 4xx and 5xx responses
  * Stop resolving relative URLs against the current working directory when no base URL is given
  * Resolve custom properties on the declaring element and treat invalid ``var()`` substitutions as ``unset``
  * Load ``file://`` URLs natively instead of through curl
  * Resolve logical and physical properties by cascade order
  * Handle the HTML ``dir`` attribute as a presentational hint
  * Clip overflow content to rounded borders
  * Apply the user-agent stylesheet to the root document only
  * Render unsupported ``<input>`` types as text fields
  * Limit CSS variable substitution to 65536 tokens

Backers and sponsors:

- `Sveltware Solutions <https://github.com/sveltware>`_
- `Dino Maric <https://github.com/dixpac>`_
- `Ashish Kulkarni <https://github.com/ashkulz>`_

.. _v0-22-0:

PlutoPrint 0.22.0 (2026-08-04)
------------------------------

- Bump PlutoBook to v0.19.0

  * Fix several security vulnerabilities
  * Add support for the legacy ``nowrap`` attribute on table cells
  * Remove ICU i18n dependency
  * Remove incomplete ``target-counter`` and ``target-counters`` implementation
  * Reduce default resource request timeout to 30 seconds
  * Reject invalid ``calc()`` expressions at parse time
  * Reject trailing garbage in An+B dimension values
  * Prevent ``rules=rows`` from applying column borders

Backers and sponsors:

- `Sveltware Solutions <https://github.com/sveltware>`_
- `Dino Maric <https://github.com/dixpac>`_
- `Ashish Kulkarni <https://github.com/ashkulz>`_

.. _v0-21-0:

PlutoPrint 0.21.0 (2026-06-30)
------------------------------

- Bump PlutoBook to v0.18.0

  * Add support for CSS Logical Properties
  * Add support for SVG ``textPath``
  * Add support for SVG ``textLength`` and ``lengthAdjust`` attributes
  * Add support for SVG text stroke rendering
  * Fix SVG ``unicode-bidi`` handling
  * Fix rendering of invisible SVG text fragments
  * Fix double application of SVG ``baseline-shift`` offset

Backers and sponsors:

- `Sveltware Solutions <https://github.com/sveltware>`_
- `Dino Maric <https://github.com/dixpac>`_
- `Ashish Kulkarni <https://github.com/ashkulz>`_

.. _v0-20-0:

PlutoPrint 0.20.0 (2026-04-14)
------------------------------

- Bump PlutoBook to v0.17.0

  * Add support for ``inset`` shorthand property
  * Add support for ``lh``, ``rlh``, ``cap``, ``rcap``, ``ic``, ``ric``, ``rex``, and ``rch`` units
  * Allow flexible emoji selection for primary font
  * Allow ``none`` in background shorthand parsing
  * Reject invalid CSS value types
  * Reject trailing tokens in ``border-radius`` shorthand parsing
  * Defer font shorthand property emission until full parsing succeeds
  * Improve media query parsing, error recovery, and feature comparison
  * Remove unnecessary whitespace from SVG string properties

Backers and sponsors:

- `Sveltware Solutions <https://github.com/sveltware>`_
- `Ashish Kulkarni <https://github.com/ashkulz>`_

.. _v0-19-0:

PlutoPrint 0.19.0 (2026-03-19)
------------------------------

- Bump PlutoBook to v0.16.0

  * Add full CSS ``:lang()`` locale support
  * Add language-specific default quotes
  * Fix ``calc()`` not preserving unitless results
  * Fix font fallback for grapheme clusters
  * Fix emoji variation selector detection
  * Fallback to monochrome when color glyphs are unavailable
  * Force layout during pagination to fix mismatched layouts
  * Include query component in base URL resolution
  * Enforce strict parsing for CSS ``matrix()`` and ``rect()``
  * Reduce memory usage by avoiding redundant CSS property storage

Backers and sponsors:

- `Sveltware Solutions <https://github.com/sveltware>`_
- `Ashish Kulkarni <https://github.com/ashkulz>`_

.. _v0-18-0:

PlutoPrint 0.18.0 (2026-02-17)
------------------------------

- Bump PlutoBook to v0.15.0

  * Add support for emoji variation selectors
  * Fast skip painting off-screen table content
  * Fix synthetic oblique slope range check
  * Fix table cell border attribute mapping
  * Fix ``empty-cells`` painting in separate border model

Backers and sponsors:

- `Peter Nguyen <https://github.com/jupetern>`_
- `Ashish Kulkarni <https://github.com/ashkulz>`_

.. _v0-17-0:

PlutoPrint 0.17.0 (2026-02-09)
------------------------------

- Bump PlutoBook to v0.14.0

  * Add selector filter for fast CSS selector rejection
  * Add lazy loading support for CSS ``@font-face`` sources
  * Add support for padding in page boxes
  * Fix double slanting of remote CSS ``@font-face`` fonts
  * Fix fallback handling in SVG paint application
  * Fix rounding errors in fragment offsets, line, and flex layout
  * Apply page scale to page margin boxes
  * Reorder header and footer painting to fix collapsed border rendering
  * Revert change ensuring empty list items with outside markers generate boxes

Backers and sponsors:

- `Peter Nguyen <https://github.com/jupetern>`_
- `Ashish Kulkarni <https://github.com/ashkulz>`_

.. _v0-16-0:

PlutoPrint 0.16.0 (2026-01-14)
------------------------------

- Bump PlutoBook to v0.13.0

  * Support repeating table headers and footers
  * Support column group background painting and border resolution
  * Support absolute and fixed positioning inside page margin boxes
  * Fix table row and cell height sizing
  * Fix table column and row span width and padding calculations
  * Fix collapsed table border resolution order for adjacent columns
  * Prevent page breaks inside table rows
  * Remove table padding for collapsed border

- Refactor fontconfig path initialization
- Add custom Meson search for plutobook library and headers

Backers and sponsors:

- `Peter Nguyen <https://github.com/jupetern>`_
- `Ashish Kulkarni <https://github.com/ashkulz>`_

.. _v0-15-0:

PlutoPrint 0.15.0 (2025-12-23)
------------------------------

- Bump PlutoBook to v0.12.0

  * Add support for the ``width`` style attribute on ``td``, ``th``, ``col``, and ``colgroup`` elements
  * Support outline painting for table rows and sections
  * Fix unnecessary pseudo-element box generation when content is ``none`` or ``normal``

Backers and sponsors:

- `Peter Nguyen <https://github.com/jupetern>`_
- `Ashish Kulkarni <https://github.com/ashkulz>`_

.. _v0-14-0:

PlutoPrint 0.14.0 (2025-12-05)
------------------------------

- Bump PlutoBook to v0.11.2

  * Fix ``:has()`` matching by preventing premature return so all sub-selectors are evaluated
  * Handle UTF-8 filenames on Windows when opening output files
  * Skip zero-width spaces during text rendering to prevent invisible characters in PDF output

- Add :func:`plutobook_set_fontconfig_path` to set ``FONTCONFIG_PATH`` for PlutoBook
- Fix UTF-8 path handling on Windows

Backers and sponsors:

- `Ashish Kulkarni <https://github.com/ashkulz>`_

.. _v0-13-1:

PlutoPrint 0.13.1 (2025-11-23)
------------------------------

- Bump PlutoBook to v0.11.1

  * Fix URL resolution for Windows absolute paths by mapping them to proper ``file://`` URLs
  * Add ``cairo-fix-font-options-leaks.patch`` to address memory leaks in Cairo

Backers and sponsors:

- `Ashish Kulkarni <https://github.com/ashkulz>`_

.. _v0-13-0:

PlutoPrint 0.13.0 (2025-11-17)
------------------------------

- Bump PlutoBook to v0.11.0

  * Add support for ``<base>`` tag to resolve relative URLs
  * Add support for ``font-variant-emoji``
  * Add support for ``min-content``, ``max-content``, and ``fit-content`` in ``flex`` shorthand
  * Add support for ``:local-link`` selector
  * Add support for ``:has`` selector
  * Add support for ``:where`` selector
  * Add ``line-height: normal`` to ``::marker`` to prevent inherited ``line-height`` issues
  * Fix ``:nth-of-type`` and ``:nth-last-of-type`` sibling counting
  * Fix ``:nth()`` page selector matching
  * Fix CSS ``:lang()`` selector matching
  * Fix CSS selector specificity calculation to match W3C specification
  * Fix Windows Fontconfig failing to load its default config files
  * Refactor ``align`` and ``hidden`` presentational attributes
  * Reset form control ``font-size`` to match most browsers
  * Fully implement ``format()`` support in ``@font-face`` to skip unsupported font sources
  * Add some subset of ready-made counter styles (``binary``, ``octal``, ``lower-hexadecimal``, ``upper-hexadecimal``)
  * Fix default border value for table elements
  * Account for relative positioning offsets when computing static distances
  * Handle RTL direction when computing horizontal relative offsets

Backers and sponsors:

- `Ashish Kulkarni <https://github.com/ashkulz>`_

.. _v0-12-0:

PlutoPrint 0.12.0 (2025-10-03)
------------------------------

- Bump PlutoBook to v0.10.0

  * Add support for running headers and footers
  * Add support for CSS ``min()``, ``max()`` and ``clamp()`` functions
  * Add support for ``unicode-range`` in ``@font-face`` for selective font coverage
  * Add support for ``type`` and ``fallback`` in ``attr()`` function
  * Prioritize color emoji fonts during font selection
  * Use ``serif`` as the last-resort fallback font
  * Handle UTF-8 BOM

Backers and sponsors:

- `Woza Labs <https://github.com/wozalabs>`_
- `Ashish Kulkarni <https://github.com/ashkulz>`_
- `Nap2016 <https://github.com/Nap2016>`_

.. _v0-11-0:

PlutoPrint 0.11.0 (2025-09-20)
------------------------------

- Bump PlutoBook to v0.9.0

  * Add support for CSS Custom Properties
  * Add support for CSS ``calc()`` function with length values
  * Add support for extended ``rgb()`` and ``hsl()`` functions with whitespace and alpha slash syntax
  * Add support for CSS ``hwb()`` color function
  * Add support for CSS wide keyword ``unset``

Backers and sponsors

- `Woza Labs <https://github.com/wozalabs>`_
- `Ashish Kulkarni <https://github.com/ashkulz>`_

.. _v0-10-0:

PlutoPrint 0.10.0 (2025-09-09)
------------------------------

- Bump PlutoBook to v0.8.0

  - Add support for ``space-evenly`` in flex layout
  - Add support for presentational attributes on ``<li>`` and ``<ol>``
  - Fix table height computation for positioned tables
  - Ensure empty list items with outside markers generate boxes

- Set PDF creation date metadata in CLI to current timestamp
- PlutoPrint is now available via Homebrew :)

.. _v0-9-0:

PlutoPrint 0.9.0 (2025-08-30)
-----------------------------

- Bump PlutoBook to v0.7.0

  - Add support for ``row-gap``, ``column-gap``, and ``gap`` in flex layout
  - Add support for CSS hex alpha notation
  - Fix flex layout to avoid shrinking table boxes below min preferred width
  - Fix flex layout to avoid shrinking table height
  - Fix table section height calculation to avoid double-counting border spacing
  - Fix preferred width calculation for replaced boxes

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
