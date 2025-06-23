import plutoprint
import pytest
import base64
import io

def test_book_new():
    assert isinstance(plutoprint.Book(), plutoprint.Book)
    assert isinstance(plutoprint.Book(plutoprint.PAGE_SIZE_A4), plutoprint.Book)
    assert isinstance(plutoprint.Book(plutoprint.PAGE_SIZE_A4, plutoprint.PAGE_MARGINS_NORMAL), plutoprint.Book)
    assert isinstance(plutoprint.Book(plutoprint.PAGE_SIZE_A4, plutoprint.PAGE_MARGINS_NORMAL, plutoprint.MEDIA_TYPE_PRINT), plutoprint.Book)

    assert isinstance(plutoprint.Book(size=plutoprint.PAGE_SIZE_A4), plutoprint.Book)
    assert isinstance(plutoprint.Book(margins=plutoprint.PAGE_MARGINS_NORMAL), plutoprint.Book)
    assert isinstance(plutoprint.Book(media=plutoprint.MEDIA_TYPE_PRINT), plutoprint.Book)

PAGE_WIDTH  = 10
PAGE_HEIGHT = 20

MARGIN_TOP    = 1
MARGIN_RIGHT  = 2
MARGIN_BOTTOM = 3
MARGIN_LEFT   = 4

PAGE_SIZE    = plutoprint.PageSize(PAGE_WIDTH, PAGE_HEIGHT)
PAGE_MARGINS = plutoprint.PageMargins(MARGIN_TOP, MARGIN_RIGHT, MARGIN_BOTTOM, MARGIN_LEFT)

@pytest.fixture
def book():
    return plutoprint.Book(PAGE_SIZE, PAGE_MARGINS, plutoprint.MEDIA_TYPE_PRINT)

def test_book_get_viewport_width(book):
    assert PAGE_WIDTH - MARGIN_LEFT - MARGIN_RIGHT == pytest.approx(book.get_viewport_width() * plutoprint.UNITS_PX)

def test_book_get_viewport_height(book):
    assert PAGE_HEIGHT - MARGIN_TOP - MARGIN_BOTTOM == pytest.approx(book.get_viewport_height() * plutoprint.UNITS_PX)

HTML_CONTENT = "<p>Hello <br> World</p>"

def test_book_get_document_width(book):
    assert book.get_document_width() == 0.0

    book.load_html(HTML_CONTENT)
    assert book.get_document_width() != 0.0

def test_book_get_document_height(book):
    assert book.get_document_height() == 0.0

    book.load_html(HTML_CONTENT)
    assert book.get_document_height() != 0.0

def test_book_get_page_count(book):
    assert book.get_page_count() == 0

    book.load_html(HTML_CONTENT)
    assert book.get_page_count() != 0

def test_book_get_page_size(book):
    assert book.get_page_size() == PAGE_SIZE

def test_book_get_page_size_at(book):
    with pytest.raises(IndexError):
        book.get_page_size_at(0)

    book.load_html(HTML_CONTENT)
    assert book.get_page_size_at(0) == PAGE_SIZE

    with pytest.raises(IndexError):
        book.get_page_size_at(1)

    book.load_html(HTML_CONTENT, user_style="@page { size: landscape }")
    assert book.get_page_size_at(0) == PAGE_SIZE.landscape()

    book.load_html(HTML_CONTENT, user_style="@page { size: a4 }")
    assert book.get_page_size_at(0) == plutoprint.PAGE_SIZE_A4

def test_book_get_page_margins(book):
    assert book.get_page_margins() == PAGE_MARGINS

def test_book_get_media_type(book):
    assert book.get_media_type() == plutoprint.MEDIA_TYPE_PRINT

def test_book_metadata(book):
    TITLE = "Alice’s Adventures in Wonderland"
    book.set_metadata(plutoprint.PDF_METADATA_TITLE, TITLE)
    assert book.get_metadata(plutoprint.PDF_METADATA_TITLE) == TITLE

    AUTHOR = "Lewis Carroll"
    book.set_metadata(plutoprint.PDF_METADATA_AUTHOR, AUTHOR)
    assert book.get_metadata(plutoprint.PDF_METADATA_AUTHOR) == AUTHOR

    SUBJECT = "Children's Literature"
    book.set_metadata(plutoprint.PDF_METADATA_SUBJECT, SUBJECT)
    assert book.get_metadata(plutoprint.PDF_METADATA_SUBJECT) == SUBJECT

    KEYWORDS = "alice, wonderland, fantasy"
    book.set_metadata(plutoprint.PDF_METADATA_KEYWORDS, KEYWORDS)
    assert book.get_metadata(plutoprint.PDF_METADATA_KEYWORDS) == KEYWORDS

    CREATOR = "plutoprint"
    book.set_metadata(plutoprint.PDF_METADATA_CREATOR, CREATOR)
    assert book.get_metadata(plutoprint.PDF_METADATA_CREATOR) == CREATOR

    CREATION_DATE = "2025-01-01T12:34:56"
    book.set_metadata(plutoprint.PDF_METADATA_CREATION_DATE, CREATION_DATE)
    assert book.get_metadata(plutoprint.PDF_METADATA_CREATION_DATE) == CREATION_DATE

    MOD_DATE = "2025-06-21T10:39:46"
    book.set_metadata(plutoprint.PDF_METADATA_MODIFICATION_DATE, MOD_DATE)
    assert book.get_metadata(plutoprint.PDF_METADATA_MODIFICATION_DATE) == MOD_DATE

def test_book_metadata_from_html(book):
    assert not book.get_metadata(plutoprint.PDF_METADATA_TITLE)

    TITLE = "Alice’s Adventures in Wonderland"
    book.load_html(f"<title>{TITLE}</title>")
    assert book.get_metadata(plutoprint.PDF_METADATA_TITLE) == TITLE

def test_book_load_url(book, tmp_path):
    path = tmp_path / "hello.html"
    with pytest.raises(plutoprint.Error):
        book.load_url(path.as_posix())

    path.write_text(HTML_CONTENT)
    book.load_url(path.as_posix())
    book.load_url(path.as_uri())

XHTML_CONTENT = (
    "<html xmlns='http://www.w3.org/1999/xhtml'>"
    "<body><p>Hello <br/> World</p></body>"
    "</html>"
)

SVG_CONTENT = (
    "<svg width='10' height='10' xmlns='http://www.w3.org/2000/svg'>"
    "<circle style='fill:red' cx='5' cy='5' r='5'/>"
    "</svg>"
)

PNG_DATA_BASE64 = (
    b"iVBORw0KGgoAAAANSUhEUgAAAAUAAAAFCAYAAACNbyblAAAAHElEQVQI12P4//8/"
    b"w38GIAXDIBKE0DHxgljNBAAO9TXL0Y4OHwAAAABJRU5ErkJggg=="
)

def test_book_load_data(book):
    book.load_data(SVG_CONTENT, mime_type="image/svg+xml")
    with pytest.raises(plutoprint.Error):
        book.load_data(SVG_CONTENT, mime_type="image/webp")

    with pytest.raises(plutoprint.Error):
        book.load_data(PNG_DATA_BASE64, mime_type="image/png")
    book.load_data(base64.b64decode(PNG_DATA_BASE64), mime_type="image/png")

    book.load_data(HTML_CONTENT)
    with pytest.raises(plutoprint.Error):
        book.load_data(HTML_CONTENT, mime_type="text/xml")
    book.load_data(XHTML_CONTENT)

def test_book_load_image(book):
    book.load_image(SVG_CONTENT, mime_type="image/svg+xml")
    with pytest.raises(plutoprint.Error):
        book.load_image(SVG_CONTENT)

    with pytest.raises(plutoprint.Error):
        book.load_image(HTML_CONTENT)

    with pytest.raises(plutoprint.Error):
        book.load_image(XHTML_CONTENT)

    with pytest.raises(plutoprint.Error):
        book.load_image(PNG_DATA_BASE64)
    book.load_image(base64.b64decode(PNG_DATA_BASE64))

def test_book_load_xml(book):
    with pytest.raises(plutoprint.Error):
        book.load_xml(HTML_CONTENT)
    book.load_xml(XHTML_CONTENT)
    book.load_xml(SVG_CONTENT)

def test_book_load_html(book):
    book.load_html(HTML_CONTENT)
    book.load_html(XHTML_CONTENT)
    book.load_html(SVG_CONTENT)

def test_book_clear_content(book):
    assert book.get_page_count() == 0

    book.load_html(HTML_CONTENT)
    assert book.get_page_count() != 0

    book.clear_content()
    assert book.get_page_count() == 0

def test_book_render_page(book):
    canvas = plutoprint.ImageCanvas(1, 1)
    with pytest.raises(IndexError):
        book.render_page(canvas, 0)

    assert canvas.get_data() == b'\x00\x00\x00\x00'

    book.load_html(HTML_CONTENT, user_style="@page { background: red }")
    book.render_page(canvas, 0)

    assert canvas.get_data() == b'\x00\x00\xff\xff'

def test_book_render_document(book):
    canvas = plutoprint.ImageCanvas(1, 1)

    assert canvas.get_data() == b'\x00\x00\x00\x00'

    book.load_html(HTML_CONTENT, user_style="body { background: yellow }")
    book.render_document(canvas)

    assert canvas.get_data() == b'\x00\xff\xff\xff'

def test_book_write_to_pdf(book, tmp_path):
    pdf_file = tmp_path / "hello.pdf"
    book.load_html(HTML_CONTENT)
    book.write_to_pdf(pdf_file)
    assert pdf_file.read_bytes().startswith(b'%PDF')

def test_book_write_to_pdf_stream(book):
    pdf_stream = io.BytesIO()
    book.load_html(HTML_CONTENT)
    book.write_to_pdf_stream(pdf_stream)
    assert pdf_stream.getvalue().startswith(b'%PDF')

def test_book_write_to_png(book, tmp_path):
    png_file = tmp_path / "hello.png"
    book.load_html(HTML_CONTENT)
    book.write_to_png(png_file)
    assert png_file.read_bytes().startswith(b'\x89PNG\r\n\x1a\n')

def test_book_write_to_png_stream(book):
    png_stream = io.BytesIO()
    book.load_html(HTML_CONTENT)
    book.write_to_png_stream(png_stream)
    assert png_stream.getvalue().startswith(b'\x89PNG\r\n\x1a\n')

class CustomResourceFetcher(plutoprint.ResourceFetcher):
    def __init__(self):
        super().__init__()

    def fetch_url(self, url):
        if url.startswith("custom:"):
            return plutoprint.ResourceData(f"<code>{url}</code>", "text/html")
        if url.startswith("file:"):
            return None
        return super().fetch_url(url)

def test_book_custom_resource_fetcher(book, tmp_path):
    with pytest.raises(TypeError):
        book.custom_resource_fetcher = object()

    assert book.custom_resource_fetcher is None

    with pytest.raises(plutoprint.Error):
        book.load_url("custom:hello")

    path = tmp_path / "hello.html"
    path.write_text(HTML_CONTENT)

    assert book.load_url(path.as_uri()) is None

    book.custom_resource_fetcher = CustomResourceFetcher()

    assert book.load_url("custom:hello") is None

    with pytest.raises(plutoprint.Error):
        book.load_url(path.as_uri())

    book.custom_resource_fetcher = None

    with pytest.raises(plutoprint.Error):
        book.load_url("custom:hello")

    assert book.load_url(path.as_uri()) is None
