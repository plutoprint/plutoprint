from ._plutoprint import (
    __version__,
    __version_info__,
    __build_info__,

    plutobook_version,
    plutobook_version_string,
    plutobook_build_info,
    plutobook_set_fontconfig_path,

    Error,

    PageSize,
    PageMargins,
    MediaType,
    PDFMetadata,
    ImageFormat,
    Canvas,
    ImageCanvas,
    PDFCanvas,
    ResourceData,
    ResourceFetcher,
    DefaultResourceFetcher,
    Book,

    default_resource_fetcher,

    PAGE_SIZE_NONE,
    PAGE_SIZE_LETTER,
    PAGE_SIZE_LEGAL,
    PAGE_SIZE_LEDGER,
    PAGE_SIZE_A3,
    PAGE_SIZE_A4,
    PAGE_SIZE_A5,
    PAGE_SIZE_B4,
    PAGE_SIZE_B5,

    PAGE_MARGINS_NONE,
    PAGE_MARGINS_NORMAL,
    PAGE_MARGINS_NARROW,
    PAGE_MARGINS_MODERATE,
    PAGE_MARGINS_WIDE,

    MEDIA_TYPE_PRINT,
    MEDIA_TYPE_SCREEN,

    PDF_METADATA_TITLE,
    PDF_METADATA_AUTHOR,
    PDF_METADATA_SUBJECT,
    PDF_METADATA_KEYWORDS,
    PDF_METADATA_CREATOR,
    PDF_METADATA_CREATION_DATE,
    PDF_METADATA_MODIFICATION_DATE,

    IMAGE_FORMAT_INVALID,
    IMAGE_FORMAT_ARGB32,
    IMAGE_FORMAT_RGB24,
    IMAGE_FORMAT_A8,
    IMAGE_FORMAT_A1,

    MIN_PAGE_COUNT,
    MAX_PAGE_COUNT,

    UNITS_PT,
    UNITS_PC,
    UNITS_IN,
    UNITS_CM,
    UNITS_MM,
    UNITS_PX,

    PLUTOBOOK_VERSION,
    PLUTOBOOK_VERSION_MAJOR,
    PLUTOBOOK_VERSION_MINOR,
    PLUTOBOOK_VERSION_MICRO,
    PLUTOBOOK_VERSION_STRING
)

def _init_default_fontconfig_path():
    import os
    import sys

    fontconfig_dirs = []
    if value := os.environ.get('FONTCONFIG_PATH'):
        fontconfig_dirs.append(value);
    if sys.platform == 'linux' and os.path.exists(baseconfig_file := '/etc/fonts/fonts.conf'):
        fontconfig_dirs.append(os.path.dirname(baseconfig_file))
    if os.path.exists(fontconfig_file := os.path.join(os.path.dirname(os.path.abspath(__file__)), 'fontconfig', 'fonts.conf')):
        fontconfig_dirs.append(os.path.dirname(fontconfig_file))
    if fontconfig_dirs:
        fontconfig_sep = ';' if sys.platform == 'win32' else ':'
        plutobook_set_fontconfig_path(fontconfig_sep.join(fontconfig_dirs))

_init_default_fontconfig_path()
del _init_default_fontconfig_path
