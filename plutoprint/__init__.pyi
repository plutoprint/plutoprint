from __future__ import annotations
from typing import Type, Union, Optional, BinaryIO, Tuple
import os

version: str = ...
"""
Represents the version of plutoprint as a string in the format "major.minor.micro".
"""

version_info: Tuple[int, int, int] = ...
"""
Represents the version of plutoprint as a tuple of three integers: (major, minor, micro).
"""

PLUTOBOOK_VERSION: int = ...
"""
Represents the version of the plutobook library encoded as a single integer.
"""

PLUTOBOOK_VERSION_MAJOR: int = ...
"""
Represents the major version number of the plutobook library.
"""

PLUTOBOOK_VERSION_MICRO: int = ...
"""
Represents the micro version number of the plutobook library.
"""

PLUTOBOOK_VERSION_MINOR: int = ...
"""
Represents the minor version number of the plutobook library.
"""

PLUTOBOOK_VERSION_STRING: str = ...
"""
Represents the version of the plutobook library as a string in the format "major.minor.micro".
"""

UNITS_PT: float = ...
"""
Represents the conversion factor for points (pt).
"""

UNITS_PC: float = ...
"""
Represents the conversion factor for picas (12 pt).
"""

UNITS_IN: float = ...
"""
Represents the conversion factor for inches (72 pt).
"""

UNITS_CM: float = ...
"""
Represents the conversion factor for centimeters (72 / 2.54 pt).
"""

UNITS_MM: float = ...
"""
Represents the conversion factor for millimeters (72 / 25.4 pt).
"""

UNITS_PX: float = ...
"""
Represents the conversion factor for pixels (72 / 96 pt).
"""

class PageSize:
    """
    The `PageSize` class represents the dimensions of a page in points (1 / 72 inch).
    """
    def __init__(self, width: float = 0.0, height: float = 0.0) -> None:
        """
        Initializes a new instance of the `PageSize` class.

        :param width: The width of the page in points.
        :param height: The height of the page in points.
        """

    def __getitem__(self, index: int) -> float:
        """
        Allows access to the dimensions of the page using an index.

        :param index: The index to access (0 for width, 1 for height).
        :returns: The width if `index` is 0, the height if `index` is 1.
        :raises IndexError: If the index is out of range (not 0 or 1).
        """

    def landscape(self) -> PageSize:
        """
        Returns a `PageSize` instance with width and height swapped if the current orientation is portrait (width < height).

        :returns: A `PageSize` instance with swapped dimensions if in portrait mode, otherwise the original dimensions.
        """

    def portrait(self) -> PageSize:
        """
        Returns a `PageSize` instance with width and height swapped if the current orientation is landscape (width > height).

        :returns: A `PageSize` instance with swapped dimensions if in landscape mode, otherwise the original dimensions.
        """

    width: float = ...
    """
    The width of the page in points (1 / 72 inch).
    """

    height: float = ...
    """
    The width of the page in points (1 / 72 inch).
    """

PAGE_SIZE_NONE: PageSize = ...
"""
Represents a page size with zero dimensions on all sides.
"""

PAGE_SIZE_LETTER: PageSize = ...
"""
Represents the Letter page size (8.5 x 11 inches).
"""

PAGE_SIZE_LEGAL: PageSize = ...
"""
Represents the Legal page size (8.5 x 14 inches).
"""

PAGE_SIZE_LEDGER: PageSize = ...
"""
Represents the Ledger page size (11 x 17 inches).
"""

PAGE_SIZE_A3: PageSize = ...
"""
Represents the A3 page size (297 x 420 mm).
"""

PAGE_SIZE_A4: PageSize = ...
"""
Represents the A4 page size (210 x 297 mm).
"""

PAGE_SIZE_A5: PageSize = ...
"""
Represents the B4 page size (148 x 210 mm).
"""

PAGE_SIZE_B4: PageSize = ...
"""
Represents the B4 page size (250 x 353 mm).
"""

PAGE_SIZE_B5: PageSize = ...
"""
Represents the B5 page size (176 x 250 mm).
"""

class PageMargins:
    """
    The `PageMargins` class represents the margins of a page in points (1 / 72 inch)
    """
    def __init__(self, top: float = 0.0, right: float = 0.0, bottom: float = 0.0, left: float = 0.0) -> None:
        """
        Initializes a new instance of the `PageMargins` class.

        :param top: The top margin of the page in points.
        :param right: The right margin of the page in points.
        :param bottom: The bottom margin of the page in points.
        :param left: The left margin of the page in points.
        """

    def __getitem__(self, index: int) -> float:
        """
        Allows access to the margins of the page using an index.

        :param index: The index to access (0 for top, 1 for right, 2 for bottom, 3 for left).
        :returns: The top if `index` is 0, the right if `index` is 1, the bottom if `index` is 2, the left if `index` is 3.
        :raises IndexError: If the index is out of range (not 0, 1, 2, or 3).
        """

    top: float = ...
    """
    The top margin of the page in points (1 / 72 inch).
    """

    right: float = ...
    """
    The top margin of the page in points (1 / 72 inch).
    """

    bottom: float = ...
    """
    The top margin of the page in points (1 / 72 inch).
    """

    left: float = ...
    """
    The top margin of the page in points (1 / 72 inch).
    """

PAGE_MARGINS_NONE: PageMargins = ...
"""
Represents page margins with zero dimensions on all sides.
"""

PAGE_MARGINS_NORMAL: PageMargins = ...
"""
Represents normal page margins (72 points or 1 inch on all sides).

- Top: 72 points (1 inch)
- Right: 72 points (1 inch)
- Bottom: 72 points (1 inch)
- Left: 72 points (1 inch)
"""

PAGE_MARGINS_NARROW: PageMargins = ...
"""
Represents narrow page margins (36 points or 0.5 inches on all sides).

- Top: 36 points (0.5 inches)
- Right: 36 points (0.5 inches)
- Bottom: 36 points (0.5 inches)
- Left: 36 points (0.5 inches)
"""

PAGE_MARGINS_MODERATE: PageMargins = ...
"""
Represents moderate page margins.

- Top: 72 points (1 inch)
- Right: 54 points (0.75 inches)
- Bottom: 72 points (1 inch)
- Left: 54 points (0.75 inches)
"""

PAGE_MARGINS_WIDE: PageMargins = ...
"""
Represents wide page margins.

- Top: 72 points (1 inch)
- Right: 144 points (2 inches)
- Bottom: 72 points (1 inch)
- Left: 144 points (2 inches)
"""

class MediaType:
    """
    An enumeration class representing different media types.
    """

MEDIA_TYPE_PRINT: MediaType = ...
"""
Represents the print media type.
"""

MEDIA_TYPE_SCREEN: MediaType = ...
"""
Represents the screen media type.
"""

class PDFMetadata:
    """
    An enumeration class representing different types of metadata for PDF documents.
    """

PDF_METADATA_TITLE: PDFMetadata = ...
"""
Represents the title metadata of a PDF document.
"""

PDF_METADATA_AUTHOR: PDFMetadata = ...
"""
Represents the author metadata of a PDF document.
"""

PDF_METADATA_SUBJECT: PDFMetadata = ...
"""
Represents the subject metadata of a PDF document.
"""

PDF_METADATA_KEYWORDS: PDFMetadata = ...
"""
Represents the keywords metadata of a PDF document.
"""

PDF_METADATA_CREATOR: PDFMetadata = ...
"""
Represents the creator metadata of a PDF document.
"""

PDF_METADATA_CREATION_DATE: PDFMetadata = ...
"""
Represents the creation date metadata of a PDF document.
"""

PDF_METADATA_MODIFICATION_DATE: PDFMetadata = ...
"""
Represents the modification date metadata of a PDF document.
"""

class ImageFormat:
    """
    An enumeration class representing different image formats.
    """

IMAGE_FORMAT_INVALID: ImageFormat = ...
"""
Represents an invalid image format.
"""

IMAGE_FORMAT_ARGB32: ImageFormat = ...
"""
Represents the ARGB32 image format.

Each pixel is a 32-bit quantity, with alpha in the upper 8 bits, then red, then green, then blue.
The 32-bit quantities are stored native-endian.
Pre-multiplied alpha is used. (That is, 50% transparent red is 0x80800000, not 0x80ff0000.)
"""

IMAGE_FORMAT_RGB24: ImageFormat = ...
"""
Represents the RGB24 image format.

Each pixel is a 32-bit quantity, with the upper 8 bits unused.
Red, Green, and Blue are stored in the remaining 24 bits in that order. 
"""

IMAGE_FORMAT_A8: ImageFormat = ...
"""
Represents the A8 image format.

Each pixel is a 8-bit quantity holding an alpha value. 
"""

IMAGE_FORMAT_A1: ImageFormat = ...
"""
Represents the A1 image format.

Each pixel is a 1-bit quantity holding an alpha value.
Pixels are packed together into 32-bit quantities.
The ordering of the bits matches the endianess of the platform.
On a big-endian machine, the first pixel is in the uppermost bit,
on a little-endian machine the first pixel is in the least-significant bit.
"""

class LoadError(Exception):
    """
    An exception class representing errors that occur during loading operations.
    """

class WriteError(Exception):
    """
    An exception class representing errors that occur during writing operations.
    """

class CanvasError(Exception):
    """
    An exception class representing errors related to canvas operations.
    """

class Canvas:
    """
    An abstract base class that provides an interface for drawing and transforming graphics on a canvas.
    """

    def __enter__(self) -> Type[Canvas]:
        """
        Enters a runtime context related to this object. Used to support the context management protocol.

        :returns: The canvas instance.
        """

    def __exit__(self, *exc_info) -> None:
        """
        Exits the runtime context related to this object. Used to support the context management protocol.

        :param exc_info: Exception information.
        """

    def flush(self) -> None:
        """
        Flushes any pending drawing operations.
        """

    def finish(self) -> None:
        """
        Finishes all drawing operations and cleans up the canvas.
        """

    def translate(self, tx: float, ty: float) -> None:
        """
        Moves the canvas and its origin to a different point.

        :param tx: The translation offset in the x-direction.
        :param ty: The translation offset in the y-direction.
        """

    def scale(self, sx: float, sy: float) -> None:
        """
        Scales the canvas units by the specified factors.

        :param sx: The scaling factor in the x-direction.
        :param sy: The scaling factor in the y-direction.
        """

    def rotate(self, angle: float) -> None:
        """
        Rotates the canvas around the current origin.

        :param angle: The rotation angle in radians.
        """

    def transform(self, a: float, b: float, c: float, d: float, e: float, f: float) -> None:
        """
        Multiplies the current transformation matrix with the specified matrix.

        :param a: The element at position (1, 1) of the transformation matrix.
        :param b: The element at position (1, 2) of the transformation matrix.
        :param c: The element at position (2, 1) of the transformation matrix.
        :param d: The element at position (2, 2) of the transformation matrix.
        :param e: The element at position (3, 1) of the transformation matrix.
        :param f: The element at position (3, 2) of the transformation matrix.
        """

    def set_matrix(self, a: float, b: float, c: float, d: float, e: float, f: float) -> None:
        """
        Resets the transformation matrix to the specified matrix.

        :param a: The element at position (1, 1) of the transformation matrix.
        :param b: The element at position (1, 2) of the transformation matrix.
        :param c: The element at position (2, 1) of the transformation matrix.
        :param d: The element at position (2, 2) of the transformation matrix.
        :param e: The element at position (3, 1) of the transformation matrix.
        :param f: The element at position (3, 2) of the transformation matrix.
        """

    def reset_matrix(self) -> None:
        """
        Resets the current transformation to the identity matrix.
        """

    def clip_rect(self, x: float, y: float, width: float, height: float) -> None:
        """
        Intersects the current clip with the specified rectangle.

        :param x: The x-coordinate of the top-left corner of the rectangle.
        :param y: The y-coordinate of the top-left corner of the rectangle.
        :param width: The width of the rectangle.
        :param height: The height of the rectangle.
        """

    def clear_surface(self, red: float, green: float, blue: float, alpha: float = 1.0) -> None:
        """
        Clears the canvas surface with the specified color.

        :param red: The red component of the color.
        :param green: The green component of the color.
        :param blue: The blue component of the color.
        :param alpha: The alpha component of the color.
        """

    def save_state(self) -> None:
        """
        Saves the current state of the canvas.
        """

    def restore_state(self) -> None:
        """
        Restores the most recently saved state of the canvas.
        """

class ImageCanvas(Canvas):
    def __init__(self, width: int, height: int, format: ImageFormat = IMAGE_FORMAT_ARGB32) -> None: ...
    @classmethod
    def create_for_data(cls, data: memoryview, width: int, height: int, stride: int, format: ImageFormat = IMAGE_FORMAT_ARGB32) -> ImageCanvas: ...
    def get_data(self) -> memoryview: ...
    def get_width(self) -> int: ...
    def get_height(self) -> int: ...
    def get_stride(self) -> int: ...
    def get_format(self) -> ImageFormat: ...
    def write_to_png(self, path: Union[str, bytes, os.PathLike]) -> None: ...
    def write_to_png_stream(self, stream: BinaryIO) -> None: ...

class PDFCanvas(Canvas):
    def __init__(self, path: Union[str, bytes, os.PathLike], size: PageSize) -> None: ...
    @classmethod
    def create_for_stream(cls, stream: BinaryIO, size: PageSize) -> PDFCanvas: ...
    def set_metadata(self, metadata: PDFMetadata, value: str) -> None: ...
    def set_size(self, size: PageSize) -> None: ...
    def show_page(self) -> None: ...

MIN_PAGE_COUNT: int = ...
MAX_PAGE_COUNT: int = ...

class Book:
    def __init__(self, size: PageSize = PAGE_SIZE_A4, margins: PageMargins = PAGE_MARGINS_NORMAL, media: MediaType = MEDIA_TYPE_PRINT) -> None: ...
    def get_viewport_width(self) -> float: ...
    def get_viewport_height(self) -> float: ...
    def get_document_width(self) -> float: ...
    def get_document_height(self) -> float: ...
    def get_page_count(self) -> int: ...
    def get_page_size(self) -> PageSize: ...
    def get_page_size_at(self, page_index: int) -> PageSize: ...
    def get_page_margins(self) -> PageMargins: ...
    def get_media_type(self) -> MediaType: ...
    def set_metadata(self, metadata: PDFMetadata, value: str) -> None: ...
    def get_metadata(self, metadata: PDFMetadata) -> str: ...
    def load_url(self, url: str, user_style: str = ..., user_script: str = ...) -> None: ...
    def load_data(self, data: Union[str, bytes], mime_type: str = ..., text_encoding: str = ..., user_style: str = ..., user_script: str = ..., base_url: str = ...) -> None: ...
    def load_image(self, data: Union[str, bytes], mime_type: str = ..., text_encoding: str = ..., user_style: str = ..., user_script: str = ..., base_url: str = ...) -> None: ...
    def load_xml(self, data: str, user_style: str = ..., user_script: str = ..., base_url: str = ...) -> None: ...
    def load_html(self, data: str, user_style: str = ..., user_script: str = ..., base_url: str = ...) -> None: ...
    def render_page(self, canvas: Canvas, page_index: int) -> None: ...
    def render_document(self, canvas: Canvas, rect: Tuple[float, float, float, float] = ...) -> None: ...
    def write_to_pdf(self, path: Union[str, bytes, os.PathLike], from_page: int = MIN_PAGE_COUNT, to_page: int = MAX_PAGE_COUNT, page_step: int = 1) -> None: ...
    def write_to_pdf_stream(self, stream: BinaryIO, from_page: int = MIN_PAGE_COUNT, to_page: int = MAX_PAGE_COUNT, page_step: int = 1) -> None: ...
    def write_to_png(self, path: Union[str, bytes, os.PathLike], format: ImageFormat = IMAGE_FORMAT_ARGB32) -> None: ...
    def write_to_png_stream(self, stream: BinaryIO, format: ImageFormat = IMAGE_FORMAT_ARGB32) -> None: ...

class ResourceData:
    def __init__(self, content: Union[str, bytes], mime_type: str = ..., text_encoding: str = ...) -> None: ...
    def get_content(self) -> memoryview: ...
    def get_mime_type(self) -> str: ...
    def get_text_encoding(self) -> str: ...

class ResourceFetcher:
    def __init__(self) -> None: ...
    def load_url(self, url: str) -> ResourceData: ...

class ResourceLoader:
    default_fetcher: ResourceFetcher = ...
    custom_fetcher: Optional[ResourceFetcher] = None

resource_loader: ResourceLoader = ...
