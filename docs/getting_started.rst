Getting Started
===============

.. currentmodule:: plutoprint

Installation
------------

PlutoPrint is available on `PyPI <https://pypi.org/project/plutoprint>`_, and can be installed directly via:

.. code-block:: bash

   pip install plutoprint

When building PlutoPrint from source, it is recommended to install precompiled versions of the required libraries using your system’s package manager.  
If these libraries are not found, Meson will attempt to build them from source, which can significantly increase build time.

- **Required:** ``cairo``, ``expat``, ``fontconfig``, ``freetype``, ``harfbuzz``, ``icu``
- **Optional:** ``curl``, ``turbojpeg``, ``webp`` (enable additional features)

The commands below install the required, optional, and build dependencies.

Ubuntu/Debian
^^^^^^^^^^^^^

.. code-block:: bash

   sudo apt-get install -y \
      build-essential pkg-config \
      meson ninja-build \
      libcairo2-dev libexpat1-dev libfontconfig1-dev libfreetype6-dev \
      libharfbuzz-dev libicu-dev \
      libcurl4-openssl-dev libturbojpeg0-dev libwebp-dev

macOS/Homebrew
^^^^^^^^^^^^^^

Install the packages using `Homebrew <https://brew.sh>`_:

.. code-block:: bash

   brew install llvm pkg-config \
      meson ninja \
      cairo expat fontconfig freetype harfbuzz icu4c \
      curl jpeg-turbo webp

Windows/MSYS2
^^^^^^^^^^^^^

Install `MSYS2 <https://www.msys2.org>`_, launch the **MSYS2 MinGW 64-bit** shell, and run:

.. code-block:: bash

   pacman -S --needed \
      mingw-w64-x86_64-gcc \
      mingw-w64-x86_64-pkgconf \
      mingw-w64-x86_64-meson \
      mingw-w64-x86_64-ninja \
      mingw-w64-x86_64-expat \
      mingw-w64-x86_64-icu \
      mingw-w64-x86_64-freetype \
      mingw-w64-x86_64-harfbuzz \
      mingw-w64-x86_64-fontconfig \
      mingw-w64-x86_64-cairo \
      mingw-w64-x86_64-curl-winssl \
      mingw-w64-x86_64-libjpeg-turbo \
      mingw-w64-x86_64-libwebp

Verify Installation
-------------------

Run the following command to check that PlutoPrint is installed and accessible:

.. code-block:: bash

   python -c "import plutoprint; print(plutoprint.__build_info__)"
