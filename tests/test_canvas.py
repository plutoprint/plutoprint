import plutoprint
import pytest
import io

def test_canvas_new():
    with pytest.raises(TypeError):
        plutoprint.Canvas()

def test_canvas_context_manager():
    with plutoprint.ImageCanvas(1, 1) as canvas:
        assert isinstance(canvas, plutoprint.Canvas)

@pytest.fixture
def canvas():
    return plutoprint.ImageCanvas(8, 8)

def test_canvas_flush(canvas):
    canvas.flush()

def test_canvas_finish(canvas):
    canvas.finish()

def test_canvas_translate(canvas):
    canvas.translate(1, 2)

def test_canvas_scale(canvas):
    canvas.scale(1, 2)

def test_canvas_rotate(canvas):
    canvas.rotate(1)

def test_canvas_transform(canvas):
    canvas.transform(1, 2, 3, 4, 5, 6)

def test_canvas_set_matrix(canvas):
    canvas.set_matrix(1, 2, 3, 4, 5, 6)

def test_canvas_clip_rect(canvas):
    canvas.clip_rect(1, 2, 3, 4)

def test_canvas_clear_surface(canvas):
    canvas.clear_surface(0.1, 0.2, 0.3)
    canvas.clear_surface(0.1, 0.2, 0.3, 0.4)

def test_canvas_clip_rect(canvas):
    canvas.clip_rect(1, 2, 3, 4)

def test_canvas_save_state(canvas):
    canvas.save_state()

def test_canvas_restore_state(canvas):
    canvas.restore_state()

def test_imagecanvas_new():
    canvas = plutoprint.ImageCanvas(1, 2)

    assert isinstance(canvas, plutoprint.ImageCanvas)
    assert isinstance(canvas, plutoprint.Canvas)

    assert isinstance(plutoprint.ImageCanvas(1, 2, plutoprint.IMAGE_FORMAT_ARGB32), plutoprint.ImageCanvas)

    with pytest.raises(plutoprint.Error):
        plutoprint.ImageCanvas(1, 2, plutoprint.IMAGE_FORMAT_INVALID)

def test_imagecanvas_create_for_data():
    width, height = 1, 2
    stride, invalid_stride = width * 4, width
    data, invalid_data = bytearray(stride * height), bytearray(invalid_stride * height)
    format, invalid_format = plutoprint.IMAGE_FORMAT_ARGB32, plutoprint.IMAGE_FORMAT_INVALID

    assert isinstance(plutoprint.ImageCanvas.create_for_data(data, width, height, stride, format), plutoprint.ImageCanvas)

    with pytest.raises(ValueError):
        plutoprint.ImageCanvas.create_for_data(invalid_data, width, height, stride, format)

    with pytest.raises(plutoprint.Error):
        plutoprint.ImageCanvas.create_for_data(data, width, height, invalid_stride, format)

    with pytest.raises(plutoprint.Error):
        plutoprint.ImageCanvas.create_for_data(data, width, height, stride, invalid_format)

@pytest.fixture
def imagecanvas():
    return plutoprint.ImageCanvas(1, 2)

def test_imagecanvas_get_data(imagecanvas):
    data = imagecanvas.get_data()

    assert isinstance(data, memoryview)
    assert bytes(data) == b'\x00\x00\x00\x00\x00\x00\x00\x00'

    for i in range(len(data)):
        data[i] = 0xFF

    assert imagecanvas.get_data() == b'\xff\xff\xff\xff\xff\xff\xff\xff'

def test_imagecanvas_get_width(imagecanvas):
    assert isinstance(imagecanvas.get_width(), int)
    assert imagecanvas.get_width() == 1

def test_imagecanvas_get_height(imagecanvas):
    assert isinstance(imagecanvas.get_height(), int)
    assert imagecanvas.get_height() == 2

def test_imagecanvas_get_stride(imagecanvas):
    assert isinstance(imagecanvas.get_stride(), int)
    assert imagecanvas.get_stride() == 1 * 4

def test_imagecanvas_get_format(imagecanvas):
    assert isinstance(imagecanvas.get_format(), plutoprint.ImageFormat)
    assert imagecanvas.get_format() == plutoprint.IMAGE_FORMAT_ARGB32

def test_imagecanvas_write_to_png(imagecanvas, tmp_path):
    png_file = tmp_path / "hello.png"
    imagecanvas.write_to_png(png_file)
    assert png_file.read_bytes().startswith(b'\x89PNG\r\n\x1a\n')

def test_imagecanvas_write_to_png_stream(imagecanvas):
    png_stream = io.BytesIO()
    imagecanvas.write_to_png_stream(png_stream)
    assert png_stream.getvalue().startswith(b'\x89PNG\r\n\x1a\n')

def test_pdfcanvas_new(tmp_path):
    pdf_file = tmp_path / "hello.pdf"
    with plutoprint.PDFCanvas(pdf_file, plutoprint.PAGE_SIZE_A4) as canvas:
        assert isinstance(canvas, plutoprint.PDFCanvas)
        assert isinstance(canvas, plutoprint.Canvas)
    assert pdf_file.read_bytes().startswith(b'%PDF')

def test_pdfcanvas_create_for_stream():
    pdf_stream = io.BytesIO()
    with plutoprint.PDFCanvas.create_for_stream(pdf_stream, plutoprint.PAGE_SIZE_A4) as canvas:
        assert isinstance(canvas, plutoprint.PDFCanvas)
        assert isinstance(canvas, plutoprint.Canvas)
    assert pdf_stream.getvalue().startswith(b'%PDF')

@pytest.fixture
def pdfcanvas(tmp_path):
    return plutoprint.PDFCanvas(tmp_path / "hello.pdf", plutoprint.PAGE_SIZE_A4)

def test_pdfcanvas_set_metadata(pdfcanvas):
    pdfcanvas.set_metadata(plutoprint.PDF_METADATA_TITLE, "Hello World")

def test_pdfcanvas_set_size(pdfcanvas):
    pdfcanvas.set_size(plutoprint.PageSize(1, 2))

def test_pdfcanvas_show_page(pdfcanvas):
    pdfcanvas.show_page()
