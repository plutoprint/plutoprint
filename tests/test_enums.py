import plutoprint
import pytest

def test_mediatype():
    with pytest.raises(TypeError):
        plutoprint.MediaType()

    with pytest.raises(TypeError):
        plutoprint.MediaType(int())

    assert isinstance(plutoprint.MEDIA_TYPE_PRINT,  plutoprint.MediaType)
    assert isinstance(plutoprint.MEDIA_TYPE_SCREEN, plutoprint.MediaType)

    assert repr(plutoprint.MEDIA_TYPE_PRINT)  == "plutoprint.MEDIA_TYPE_PRINT"
    assert repr(plutoprint.MEDIA_TYPE_SCREEN) == "plutoprint.MEDIA_TYPE_SCREEN"

def test_pdfmetadata():
    with pytest.raises(TypeError):
        plutoprint.PDFMetadata()

    with pytest.raises(TypeError):
        plutoprint.PDFMetadata(int())

    assert isinstance(plutoprint.PDF_METADATA_TITLE,             plutoprint.PDFMetadata)
    assert isinstance(plutoprint.PDF_METADATA_AUTHOR,            plutoprint.PDFMetadata)
    assert isinstance(plutoprint.PDF_METADATA_SUBJECT,           plutoprint.PDFMetadata)
    assert isinstance(plutoprint.PDF_METADATA_KEYWORDS,          plutoprint.PDFMetadata)
    assert isinstance(plutoprint.PDF_METADATA_CREATOR,           plutoprint.PDFMetadata)
    assert isinstance(plutoprint.PDF_METADATA_CREATION_DATE,     plutoprint.PDFMetadata)
    assert isinstance(plutoprint.PDF_METADATA_MODIFICATION_DATE, plutoprint.PDFMetadata)

    assert repr(plutoprint.PDF_METADATA_TITLE)             == "plutoprint.PDF_METADATA_TITLE"
    assert repr(plutoprint.PDF_METADATA_AUTHOR)            == "plutoprint.PDF_METADATA_AUTHOR"
    assert repr(plutoprint.PDF_METADATA_SUBJECT)           == "plutoprint.PDF_METADATA_SUBJECT"
    assert repr(plutoprint.PDF_METADATA_KEYWORDS)          == "plutoprint.PDF_METADATA_KEYWORDS"
    assert repr(plutoprint.PDF_METADATA_CREATOR)           == "plutoprint.PDF_METADATA_CREATOR"
    assert repr(plutoprint.PDF_METADATA_CREATION_DATE)     == "plutoprint.PDF_METADATA_CREATION_DATE"
    assert repr(plutoprint.PDF_METADATA_MODIFICATION_DATE) == "plutoprint.PDF_METADATA_MODIFICATION_DATE"

def test_imageformat():
    with pytest.raises(TypeError):
        plutoprint.ImageFormat()

    with pytest.raises(TypeError):
        plutoprint.ImageFormat(int())

    assert isinstance(plutoprint.IMAGE_FORMAT_INVALID, plutoprint.ImageFormat)
    assert isinstance(plutoprint.IMAGE_FORMAT_ARGB32,  plutoprint.ImageFormat)
    assert isinstance(plutoprint.IMAGE_FORMAT_RGB24,   plutoprint.ImageFormat)
    assert isinstance(plutoprint.IMAGE_FORMAT_A8,      plutoprint.ImageFormat)
    assert isinstance(plutoprint.IMAGE_FORMAT_A1,      plutoprint.ImageFormat)

    assert repr(plutoprint.IMAGE_FORMAT_INVALID) == "plutoprint.IMAGE_FORMAT_INVALID"
    assert repr(plutoprint.IMAGE_FORMAT_ARGB32)  == "plutoprint.IMAGE_FORMAT_ARGB32"
    assert repr(plutoprint.IMAGE_FORMAT_RGB24)   == "plutoprint.IMAGE_FORMAT_RGB24"
    assert repr(plutoprint.IMAGE_FORMAT_A8)      == "plutoprint.IMAGE_FORMAT_A8"
    assert repr(plutoprint.IMAGE_FORMAT_A1)      == "plutoprint.IMAGE_FORMAT_A1"
