import plutoprint
import pytest

def test_book_new():
    assert isinstance(plutoprint.Book(), plutoprint.Book)
    assert isinstance(plutoprint.Book(plutoprint.PAGE_SIZE_A4), plutoprint.Book)
    assert isinstance(plutoprint.Book(plutoprint.PAGE_SIZE_A4, plutoprint.PAGE_MARGINS_NORMAL), plutoprint.Book)
    assert isinstance(plutoprint.Book(plutoprint.PAGE_SIZE_A4, plutoprint.PAGE_MARGINS_NORMAL, plutoprint.MEDIA_TYPE_PRINT), plutoprint.Book)

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

HTML_CONTENT = "<b> Hello World </b>"

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
    assert(book.get_page_size_at(0) == PAGE_SIZE.landscape())

    book.load_html(HTML_CONTENT, user_style="@page { size: a4 }")
    assert(book.get_page_size_at(0) == plutoprint.PAGE_SIZE_A4)

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

def test_book_clear_content(book):
    assert book.get_page_count() == 0

    book.load_html(HTML_CONTENT)
    assert book.get_page_count() != 0;

    book.clear_content()
    assert book.get_page_count() == 0;
