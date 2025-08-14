Changelog
=========

.. currentmodule:: plutoprint

.. _v0-3-0:

PlutoPrint 0.3.0 (2025-08-14)
-----------------------------

- Provide precompiled binaries for:

  - **Linux**: ``cp310-manylinux_x86_64``, ``cp311-manylinux_x86_64``, ``cp312-manylinux_x86_64``, ``cp313-manylinux_x86_64``, ``cp314-manylinux_x86_64``
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
- Implement `==` and `!=` for :class:`PageMargins` and :class:`PageSize`  
- Update :class:`Canvas` context methods for :class:`AnyCanvas` type variable  
- Use `is not None` for CLI argument presence checks  
- Fix dimensions in :data:`PAGE_SIZE_LEDGER` constant  
- Add comprehensive unit tests  

.. _v0-1-0:

PlutoPrint 0.1.0 (2025-05-24)
-----------------------------

- This is the first release. Everything is new. Enjoy!
