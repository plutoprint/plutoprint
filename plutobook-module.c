#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#include <plutobook.h>

typedef struct {
    PyObject_HEAD
    float width;
    float height;
} PageSize_Object;

static PyObject* PageSize_Create2(float width, float height);
static PyObject* PageSize_Create(plutobook_page_size_t size)
{
    return PageSize_Create2(size.width, size.height);
}

static PyObject* PageSize_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
    plutobook_page_size_t size = PLUTOBOOK_PAGE_SIZE_NONE;
    if(!PyArg_ParseTuple(args, "|ff:PageSize.__init__", &size.width, &size.height))
        return NULL;
    Py_ssize_t num_args = PyTuple_Size(args);
    if(num_args == 1) {
        size.height = size.width;
    }

    return PageSize_Create(size);
}

static void PageSize_dealloc(PageSize_Object* self)
{
    PyObject_Del(self);
}

static PyObject* PageSize_repr(PageSize_Object* self)
{
    char buf[256];
    PyOS_snprintf(buf, sizeof(buf), "plutobook.PageSize(%g, %g)", self->width, self->height);
    return PyUnicode_FromString(buf);
}

static PyObject* PageSize_landscape(PageSize_Object* self, PyObject* args)
{
    if(self->width < self->height)
        return PageSize_Create2(self->height, self->width);
    return PageSize_Create2(self->width, self->height);
}

static PyObject* PageSize_portrait(PageSize_Object* self, PyObject* args)
{
    if(self->width > self->height)
        return PageSize_Create2(self->height, self->width);
    return PageSize_Create2(self->width, self->height);
}

static PyMethodDef PageSize_methods[] = {
    {"landscape", (PyCFunction)PageSize_landscape, METH_NOARGS},
    {"portrait", (PyCFunction)PageSize_portrait, METH_NOARGS},
    {NULL}
};

static PyMemberDef PageSize_members[] = {
    {"width", T_FLOAT, offsetof(PageSize_Object, width), 0, NULL},
    {"height", T_FLOAT, offsetof(PageSize_Object, height), 0, NULL},
    {NULL}
};

static PyTypeObject PageSize_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plutobook.PageSize",
    .tp_basicsize = sizeof(PageSize_Object),
    .tp_dealloc = (destructor)PageSize_dealloc,
    .tp_repr = (reprfunc)PageSize_repr,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_methods = PageSize_methods,
    .tp_members = PageSize_members,
    .tp_new = (newfunc)PageSize_new
};

static PyObject* PageSize_Create2(float width, float height)
{
    PageSize_Object* size_ob = PyObject_New(PageSize_Object, &PageSize_Type);
    size_ob->width = width;
    size_ob->height = height;
    return (PyObject*)size_ob;
}

typedef struct {
    PyObject_HEAD
    float top;
    float right;
    float bottom;
    float left;
} PageMargins_Object;

static PyObject* PageMargins_Create(plutobook_page_margins_t margins);

static PyObject* PageMargins_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
    plutobook_page_margins_t margins = PLUTOBOOK_PAGE_MARGINS_NONE;
    if(!PyArg_ParseTuple(args, "|ffff:PageMargins.__init__", &margins.top, &margins.right, &margins.bottom, &margins.left))
        return NULL;
    Py_ssize_t num_args = PyTuple_Size(args);
    if(num_args == 1) {
        margins.right = margins.bottom = margins.left = margins.top;
    } else if(num_args == 2) {
        margins.bottom = margins.top;
        margins.left = margins.right;
    } else if(num_args == 3) {
        margins.left = margins.right;
    }

    return PageMargins_Create(margins);
}

static void PageMargins_dealloc(PageMargins_Object* self)
{
    PyObject_Del(self);
}

static PyObject* PageMargins_repr(PageMargins_Object* self)
{
    char buf[256];
    PyOS_snprintf(buf, sizeof(buf), "plutobook.PageMargins(%g, %g, %g, %g)", self->top, self->right, self->bottom, self->left);
    return PyUnicode_FromString(buf);
}

static PyMemberDef PageMargins_members[] = {
    {"top", T_FLOAT, offsetof(PageMargins_Object, top), 0, NULL},
    {"right", T_FLOAT, offsetof(PageMargins_Object, right), 0, NULL},
    {"bottom", T_FLOAT, offsetof(PageMargins_Object, bottom), 0, NULL},
    {"left", T_FLOAT, offsetof(PageMargins_Object, left), 0, NULL},
    {NULL}
};

static PyTypeObject PageMargins_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plutobook.PageMargins",
    .tp_basicsize = sizeof(PageMargins_Object),
    .tp_dealloc = (destructor)PageMargins_dealloc,
    .tp_repr = (reprfunc)PageMargins_repr,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_members = PageMargins_members,
    .tp_new = (newfunc)PageMargins_new
};

static PyObject* PageMargins_Create(plutobook_page_margins_t margins)
{
    PageMargins_Object* margins_ob = PyObject_New(PageMargins_Object, &PageMargins_Type);
    margins_ob->top = margins.top;
    margins_ob->right = margins.right;
    margins_ob->bottom = margins.bottom;
    margins_ob->left = margins.left;
    return (PyObject*)margins_ob;
}

typedef struct {
    PyObject_HEAD
    plutobook_media_type_t value;
} MediaType_Object;

static void MediaType_dealloc(MediaType_Object* self)
{
    PyObject_Del(self);
}

static PyObject* MediaType_repr(MediaType_Object* self)
{
    switch(self->value) {
    case PLUTOBOOK_MEDIA_TYPE_PRINT:
        return PyUnicode_FromString("plutobook.MEDIA_TYPE_PRINT");
    case PLUTOBOOK_MEDIA_TYPE_SCREEN:
        return PyUnicode_FromString("plutobook.MEDIA_TYPE_SCREEN");
    default:
        Py_UNREACHABLE();
    }

    return NULL;
}

static PyObject* MediaType_richcompare(MediaType_Object* self, PyObject* other, int op)
{
    if(Py_TYPE(self) == Py_TYPE(other))
        Py_RETURN_RICHCOMPARE(self->value, ((MediaType_Object*)other)->value, op);
    Py_RETURN_NOTIMPLEMENTED;
}

static PyTypeObject MediaType_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plutobook.MediaType",
    .tp_basicsize = sizeof(MediaType_Object),
    .tp_dealloc = (destructor)MediaType_dealloc,
    .tp_repr = (reprfunc)MediaType_repr,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_richcompare = (richcmpfunc)MediaType_richcompare
};

static PyObject* MediaType_Create(plutobook_media_type_t value)
{
    MediaType_Object* media_ob = PyObject_New(MediaType_Object, &MediaType_Type);
    media_ob->value = value;
    return (PyObject*)media_ob;
}

typedef struct {
    PyObject_HEAD
    plutobook_pdf_metadata_t value;
} PDFMetadata_Object;

static void PDFMetadata_dealloc(PDFMetadata_Object* self)
{
    PyObject_Del(self);
}

static PyObject* PDFMetadata_repr(PDFMetadata_Object* self)
{
    switch(self->value) {
    case PLUTOBOOK_PDF_METADATA_TITLE:
        return PyUnicode_FromString("plutobook.PDF_METADATA_TITLE");
    case PLUTOBOOK_PDF_METADATA_AUTHOR:
        return PyUnicode_FromString("plutobook.PDF_METADATA_AUTHOR");
    case PLUTOBOOK_PDF_METADATA_SUBJECT:
        return PyUnicode_FromString("plutobook.PDF_METADATA_SUBJECT");
    case PLUTOBOOK_PDF_METADATA_KEYWORDS:
        return PyUnicode_FromString("plutobook.PDF_METADATA_KEYWORDS");
    case PLUTOBOOK_PDF_METADATA_CREATOR:
        return PyUnicode_FromString("plutobook.PDF_METADATA_CREATOR");
    case PLUTOBOOK_PDF_METADATA_CREATION_DATE:
        return PyUnicode_FromString("plutobook.PDF_METADATA_CREATION_DATE");
    case PLUTOBOOK_PDF_METADATA_MODIFICATION_DATE:
        return PyUnicode_FromString("plutobook.PDF_METADATA_MODIFICATION_DATE");
    default:
        Py_UNREACHABLE();
    }

    return NULL;
}

static PyObject* PDFMetadata_richcompare(PDFMetadata_Object* self, PyObject* other, int op)
{
    if(Py_TYPE(self) == Py_TYPE(other))
        Py_RETURN_RICHCOMPARE(self->value, ((PDFMetadata_Object*)other)->value, op);
    Py_RETURN_NOTIMPLEMENTED;
}

static PyTypeObject PDFMetadata_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plutobook.PDFMetadata",
    .tp_basicsize = sizeof(PDFMetadata_Object),
    .tp_dealloc = (destructor)PDFMetadata_dealloc,
    .tp_repr = (reprfunc)PDFMetadata_repr,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_richcompare = (richcmpfunc)PDFMetadata_richcompare
};

static PyObject* PDFMetadata_Create(plutobook_pdf_metadata_t value)
{
    PDFMetadata_Object* metadata_ob = PyObject_New(PDFMetadata_Object, &PDFMetadata_Type);
    metadata_ob->value = value;
    return (PyObject*)metadata_ob;
}

typedef struct {
    PyObject_HEAD
    plutobook_image_format_t value;
} ImageFormat_Object;

static void ImageFormat_dealloc(ImageFormat_Object* self)
{
    PyObject_Del(self);
}

static PyObject* ImageFormat_repr(ImageFormat_Object* self)
{
    switch(self->value) {
    case PLUTOBOOK_IMAGE_FORMAT_INVALID:
        return PyUnicode_FromString("plutobook.IMAGE_FORMAT_INVALID");
    case PLUTOBOOK_IMAGE_FORMAT_ARGB32:
        return PyUnicode_FromString("plutobook.IMAGE_FORMAT_ARGB32");
    case PLUTOBOOK_IMAGE_FORMAT_RGB24:
        return PyUnicode_FromString("plutobook.IMAGE_FORMAT_RGB24");
    case PLUTOBOOK_IMAGE_FORMAT_A8:
        return PyUnicode_FromString("plutobook.IMAGE_FORMAT_A8");
    case PLUTOBOOK_IMAGE_FORMAT_A1:
        return PyUnicode_FromString("plutobook.IMAGE_FORMAT_A1");
    default:
        Py_UNREACHABLE();
    }

    return NULL;
}

static PyObject* ImageFormat_richcompare(ImageFormat_Object* self, PyObject* other, int op)
{
    if(Py_TYPE(self) == Py_TYPE(other))
        Py_RETURN_RICHCOMPARE(self->value, ((ImageFormat_Object*)other)->value, op);
    Py_RETURN_NOTIMPLEMENTED;
}

static PyTypeObject ImageFormat_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plutobook.ImageFormat",
    .tp_basicsize = sizeof(ImageFormat_Object),
    .tp_dealloc = (destructor)ImageFormat_dealloc,
    .tp_repr = (reprfunc)ImageFormat_repr,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_richcompare = (richcmpfunc)ImageFormat_richcompare
};

static PyObject* ImageFormat_Create(plutobook_image_format_t value)
{
    ImageFormat_Object* format_ob = PyObject_New(ImageFormat_Object, &ImageFormat_Type);
    format_ob->value = value;
    return (PyObject*)format_ob;
}

typedef struct {
    PyObject_HEAD
    plutobook_t* book;
} Book_Object;

static PyObject* Book_Create(plutobook_t* book);

static PyObject* Book_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
    static char* kwlist[] = { "size", "margins", "media", NULL };
    PageSize_Object* size_ob = NULL;
    PageMargins_Object* margins_ob = NULL;
    MediaType_Object* media_ob = NULL;
    if(!PyArg_ParseTupleAndKeywords(args, kwds, "|O!O!O!:Book.__init__", kwlist,
        &PageSize_Type, &size_ob, &PageMargins_Type, &margins_ob, &MediaType_Type, &media_ob)) {
        return NULL;
    }

    plutobook_page_size_t size = PLUTOBOOK_PAGE_SIZE_A4;
    if(size_ob) {
        size.width = size_ob->width;
        size.height = size_ob->height;
    }

    plutobook_page_margins_t margins = PLUTOBOOK_PAGE_MARGINS_NORMAL;
    if(margins_ob) {
        margins.top = margins_ob->top;
        margins.right = margins_ob->right;
        margins.bottom = margins_ob->bottom;
        margins.left = margins_ob->left;
    }

    plutobook_media_type_t media = PLUTOBOOK_MEDIA_TYPE_PRINT;
    if(media_ob) {
        media = media_ob->value;
    }

    return Book_Create(plutobook_create(size, margins, media));
}

static void Book_dealloc(Book_Object* self)
{
    plutobook_destroy(self->book);
    PyObject_Del(self);
}

static PyObject* Book_get_viewport_width(Book_Object* self, PyObject* args)
{
    return Py_BuildValue("f", plutobook_get_viewport_width(self->book));
}

static PyObject* Book_get_viewport_height(Book_Object* self, PyObject* args)
{
    return Py_BuildValue("f", plutobook_get_viewport_height(self->book));
}

static PyObject* Book_get_document_width(Book_Object* self, PyObject* args)
{
    float document_width;
    Py_BEGIN_ALLOW_THREADS
    document_width = plutobook_get_document_width(self->book);
    Py_END_ALLOW_THREADS
    return Py_BuildValue("f", document_width);
}

static PyObject* Book_get_document_height(Book_Object* self, PyObject* args)
{
    float document_height;
    Py_BEGIN_ALLOW_THREADS
    document_height = plutobook_get_document_height(self->book);
    Py_END_ALLOW_THREADS
    return Py_BuildValue("f", document_height);
}

static PyObject* Book_get_page_count(Book_Object* self, PyObject* args)
{
    unsigned int page_count;
    Py_BEGIN_ALLOW_THREADS
    page_count = plutobook_get_page_count(self->book);
    Py_END_ALLOW_THREADS
    return PyLong_FromLong(page_count);
}

static PyObject* Book_get_page_size(Book_Object* self, PyObject* args)
{
    return PageSize_Create(plutobook_get_page_size(self->book));
}

static PyObject* Book_get_page_size_at(Book_Object* self, PyObject* args)
{
    unsigned int page_index;
    if(!PyArg_ParseTuple(args, "I", &page_index)) {
        return NULL;
    }

    unsigned int page_count;
    Py_BEGIN_ALLOW_THREADS
    page_count = plutobook_get_page_count(self->book);
    Py_END_ALLOW_THREADS

    if(page_index >= page_count) {
        PyErr_SetString(PyExc_IndexError, "page index out of range");
        return NULL;
    }

    plutobook_page_size_t page_size;
    Py_BEGIN_ALLOW_THREADS
    page_size = plutobook_get_page_size_at(self->book, page_index);
    Py_END_ALLOW_THREADS
    return PageSize_Create(page_size);
}

static PyObject* Book_get_page_margins(Book_Object* self, PyObject* args)
{
    return PageMargins_Create(plutobook_get_page_margins(self->book));
}

static PyObject* Book_get_media_type(Book_Object* self, PyObject* args)
{
    return MediaType_Create(plutobook_get_media_type(self->book));
}

static PyObject* Book_set_metadata(Book_Object* self, PyObject* args)
{
    PDFMetadata_Object* metadata_ob;
    const char* value;
    if(!PyArg_ParseTuple(args, "O!s", &PDFMetadata_Type, &metadata_ob, &value))
        return NULL;
    plutobook_set_metadata(self->book, metadata_ob->value, value);
    Py_RETURN_NONE;
}

static PyObject* Book_get_metadata(Book_Object* self, PyObject* args)
{
    PDFMetadata_Object* metadata_ob;
    if(!PyArg_ParseTuple(args, "O!", &PDFMetadata_Type, &metadata_ob))
        return NULL;
    return PyUnicode_FromString(plutobook_get_metadata(self->book, metadata_ob->value));
}

#define RETURN_NULL_IF_ERROR(status) \
    do { \
    if(status == PLUTOBOOK_STATUS_MEMORY_ERROR) { \
        PyErr_SetString(PyExc_MemoryError, "memory error");\
        return NULL; \
    } \
    if(status == PLUTOBOOK_STATUS_LOAD_ERROR) { \
        PyErr_SetString(PyExc_ValueError, "load error");\
        return NULL; \
    } \
    if(status == PLUTOBOOK_STATUS_WRITE_ERROR) { \
        PyErr_SetString(PyExc_IOError, "write error");\
        return NULL; \
    } \
    } while(0)

static PyObject* Book_load_url(Book_Object* self, PyObject* args, PyObject* kwds)
{
    static char* kwlist[] = { "url", "user_style", "user_script", NULL };
    const char* url;
    const char* user_style = "";
    const char* user_script = "";
    if(!PyArg_ParseTupleAndKeywords(args, kwds, "s|ss", kwlist, &url, &user_style, &user_script)) {
        return NULL;
    }

    plutobook_status_t status;
    Py_BEGIN_ALLOW_THREADS
    status = plutobook_load_url(self->book, url, user_style, user_script);
    Py_END_ALLOW_THREADS
    RETURN_NULL_IF_ERROR(status);
    Py_RETURN_NONE;
}

static PyObject* Book_load_data(Book_Object* self, PyObject* args, PyObject* kwds)
{
    static char* kwlist[] = { "data", "mime_type", "text_encoding", "user_style", "user_script", "base_url", NULL };
    Py_buffer data;
    const char* mime_type = "";
    const char* text_encoding = "";
    const char* user_style = "";
    const char* user_script = "";
    const char* base_url = "";
    if(!PyArg_ParseTupleAndKeywords(args, kwds, "s*|sssss", kwlist, &data, &mime_type, &text_encoding, &user_style, &user_script, &base_url)) {
        return NULL;
    }

    plutobook_status_t status;
    Py_BEGIN_ALLOW_THREADS
    status = plutobook_load_data(self->book, data.buf, data.len, mime_type, text_encoding, user_style, user_script, base_url);
    Py_END_ALLOW_THREADS
    PyBuffer_Release(&data);
    RETURN_NULL_IF_ERROR(status);
    Py_RETURN_NONE;
}

static PyObject* Book_load_image(Book_Object* self, PyObject* args, PyObject* kwds)
{
    static char* kwlist[] = { "data", "mime_type", "text_encoding", "user_style", "user_script", "base_url", NULL };
    Py_buffer data;
    const char* mime_type = "";
    const char* text_encoding = "";
    const char* user_style = "";
    const char* user_script = "";
    const char* base_url = "";
    if(!PyArg_ParseTupleAndKeywords(args, kwds, "s*|sssss", kwlist, &data, &mime_type, &text_encoding, &user_style, &user_script, &base_url)) {
        return NULL;
    }

    plutobook_status_t status;
    Py_BEGIN_ALLOW_THREADS
    status = plutobook_load_image(self->book, data.buf, data.len, mime_type, text_encoding, user_style, user_script, base_url);
    Py_END_ALLOW_THREADS
    PyBuffer_Release(&data);
    RETURN_NULL_IF_ERROR(status);
    Py_RETURN_NONE;
}

static PyObject* Book_load_xml(Book_Object* self, PyObject* args, PyObject* kwds)
{
    static char* kwlist[] = { "data", "user_style", "user_script", "base_url", NULL };
    const char* data;
    const char* user_style = "";
    const char* user_script = "";
    const char* base_url = "";
    if(!PyArg_ParseTupleAndKeywords(args, kwds, "s|sss", kwlist, &data, &user_style, &user_script, &base_url)) {
        return NULL;
    }

    plutobook_status_t status;
    Py_BEGIN_ALLOW_THREADS
    status = plutobook_load_xml(self->book, data, -1, user_style, user_script, base_url);
    Py_END_ALLOW_THREADS
    RETURN_NULL_IF_ERROR(status);
    Py_RETURN_NONE;
}

static PyObject* Book_load_html(Book_Object* self, PyObject* args, PyObject* kwds)
{
    static char* kwlist[] = { "data", "user_style", "user_script", "base_url", NULL };
    const char* data;
    const char* user_style = "";
    const char* user_script = "";
    const char* base_url = "";
    if(!PyArg_ParseTupleAndKeywords(args, kwds, "s|sss", kwlist, &data, &user_style, &user_script, &base_url)) {
        return NULL;
    }

    plutobook_status_t status;
    Py_BEGIN_ALLOW_THREADS
    status = plutobook_load_html(self->book, data, -1, user_style, user_script, base_url);
    Py_END_ALLOW_THREADS
    RETURN_NULL_IF_ERROR(status);
    Py_RETURN_NONE;
}

static PyObject* Book_write_to_pdf(Book_Object* self, PyObject* args, PyObject* kwds)
{
    static char* kwlist[] = { "filename", "from_page", "to_page", "page_step", NULL };
    const char* filename;
    unsigned int from_page = PLUTOBOOK_MIN_PAGE_COUNT;
    unsigned int to_page = PLUTOBOOK_MAX_PAGE_COUNT;
    unsigned int page_step = 1;
    if(!PyArg_ParseTupleAndKeywords(args, kwds, "s|III", kwlist, &filename, &from_page, &to_page, &page_step)) {
        return NULL;
    }

    plutobook_status_t status;
    Py_BEGIN_ALLOW_THREADS
    status = plutobook_write_to_pdf_range(self->book, filename, from_page, to_page, page_step);
    Py_END_ALLOW_THREADS
    RETURN_NULL_IF_ERROR(status);
    Py_RETURN_NONE;
}

static PyObject* Book_write_to_png(Book_Object* self, PyObject* args)
{
    const char* filename;
    ImageFormat_Object* format_ob = NULL;
    if(!PyArg_ParseTuple(args, "s|O!", &filename, &ImageFormat_Type, &format_ob)) {
        return NULL;
    }

    plutobook_image_format_t format = PLUTOBOOK_IMAGE_FORMAT_ARGB32;
    if(format_ob) {
        format = format_ob->value;
    }

    plutobook_status_t status;
    Py_BEGIN_ALLOW_THREADS
    status = plutobook_write_to_png(self->book, filename, format);
    Py_END_ALLOW_THREADS
    RETURN_NULL_IF_ERROR(status);
    Py_RETURN_NONE;
}

static PyMethodDef Book_methods[] = {
    {"get_viewport_width", (PyCFunction)Book_get_viewport_width, METH_NOARGS},
    {"get_viewport_height", (PyCFunction)Book_get_viewport_height, METH_NOARGS},
    {"get_document_width", (PyCFunction)Book_get_document_width, METH_NOARGS},
    {"get_document_height", (PyCFunction)Book_get_document_height, METH_NOARGS},
    {"get_page_count", (PyCFunction)Book_get_page_count, METH_NOARGS},
    {"get_page_size", (PyCFunction)Book_get_page_size, METH_NOARGS},
    {"get_page_size_at", (PyCFunction)Book_get_page_size_at, METH_VARARGS},
    {"get_page_margins", (PyCFunction)Book_get_page_margins, METH_NOARGS},
    {"get_media_type", (PyCFunction)Book_get_media_type, METH_NOARGS},
    {"set_metadata", (PyCFunction)Book_set_metadata, METH_VARARGS},
    {"get_metadata", (PyCFunction)Book_get_metadata, METH_VARARGS},
    {"load_url", (PyCFunction)Book_load_url, METH_VARARGS | METH_KEYWORDS},
    {"load_data", (PyCFunction)Book_load_data, METH_VARARGS | METH_KEYWORDS},
    {"load_image", (PyCFunction)Book_load_image, METH_VARARGS | METH_KEYWORDS},
    {"load_xml", (PyCFunction)Book_load_xml, METH_VARARGS | METH_KEYWORDS},
    {"load_html", (PyCFunction)Book_load_html, METH_VARARGS | METH_KEYWORDS},
    {"write_to_pdf", (PyCFunction)Book_write_to_pdf, METH_VARARGS | METH_KEYWORDS},
    {"write_to_png", (PyCFunction)Book_write_to_png, METH_VARARGS},
    {NULL}
};

static PyTypeObject Book_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plutobook.Book",
    .tp_basicsize = sizeof(Book_Object),
    .tp_dealloc = (destructor)Book_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_methods = Book_methods,
    .tp_new = (newfunc)Book_new
};

static PyObject* Book_Create(plutobook_t* book)
{
    if(book == NULL) {
        PyErr_SetString(PyExc_MemoryError, "out of memory");
        return NULL;
    }

    Book_Object* book_ob = PyObject_New(Book_Object, &Book_Type);
    book_ob->book = book;
    return (PyObject*)book_ob;
}

typedef struct {
    PyObject_HEAD
    plutobook_resource_data_t* resource;
} ResourceData_Object;

static PyObject* ResourceData_Create(plutobook_resource_data_t* resource);

static PyObject* ResourceData_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
    static char* kwlist[] = { "content", "mime_type", "text_encoding", NULL };
    Py_buffer content;
    const char* mime_type = "";
    const char* text_encoding = "";
    if(!PyArg_ParseTupleAndKeywords(args, kwds, "s*|ss:ResourceData.__init__", kwlist, &content, &mime_type, &text_encoding)) {
        return NULL;
    }

    plutobook_resource_data_t* resource;
    Py_BEGIN_ALLOW_THREADS
    resource = plutobook_resource_data_create(content.buf, content.len, mime_type, text_encoding);
    Py_END_ALLOW_THREADS
    PyBuffer_Release(&content);
    if(resource == NULL) {
        PyErr_SetString(PyExc_MemoryError, "out of memory");
        return NULL;
    }

    return ResourceData_Create(resource);
}

static void ResourceData_dealloc(ResourceData_Object* self)
{
    plutobook_resource_data_destroy(self->resource);
    PyObject_Del(self);
}

static PyObject* ResourceData_get_content(ResourceData_Object* self, PyObject* args)
{
    return PyMemoryView_FromObject((PyObject*)self);
}

static PyObject* ResourceData_get_mime_type(ResourceData_Object* self, PyObject* args)
{
    return PyUnicode_FromString(plutobook_resource_data_get_mime_type(self->resource));
}

static PyObject* ResourceData_get_text_encoding(ResourceData_Object* self, PyObject* args)
{
    return PyUnicode_FromString(plutobook_resource_data_get_text_encoding(self->resource));
}

static int ResourceData_get_buffer(ResourceData_Object* self, Py_buffer* view, int flags)
{
    const char* content = plutobook_resource_data_get_content(self->resource);
    unsigned int content_length = plutobook_resource_data_get_content_length(self->resource);
    return PyBuffer_FillInfo(view, (PyObject*)self, (void*)content, content_length, 1, flags);
}

static PyBufferProcs ResourceData_as_buffer = {
    (getbufferproc)ResourceData_get_buffer,
    NULL
};

static PyMethodDef ResourceData_methods[] = {
    {"get_content", (PyCFunction)ResourceData_get_content, METH_NOARGS},
    {"get_mime_type", (PyCFunction)ResourceData_get_mime_type, METH_NOARGS},
    {"get_text_encoding", (PyCFunction)ResourceData_get_text_encoding, METH_NOARGS},
    {NULL}
};

static PyTypeObject ResourceData_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plutobook.ResourceData",
    .tp_basicsize = sizeof(ResourceData_Object),
    .tp_dealloc = (destructor)ResourceData_dealloc,
    .tp_as_buffer = &ResourceData_as_buffer,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_methods = ResourceData_methods,
    .tp_new = (newfunc)ResourceData_new
};

static PyObject* ResourceData_Create(plutobook_resource_data_t* resource)
{
    ResourceData_Object* resource_ob = PyObject_New(ResourceData_Object, &ResourceData_Type);
    resource_ob->resource = resource;
    return (PyObject*)resource_ob;
}

static PyObject* ResourceFetcher_load_url(ResourceData_Object* self, PyObject* args)
{
    const char* url;
    if(!PyArg_ParseTuple(args, "s", &url)) {
        return NULL;
    }

    plutobook_resource_data_t* resource;
    Py_BEGIN_ALLOW_THREADS
    resource = plutobook_default_resource_fetcher_load_url(url);
    Py_END_ALLOW_THREADS
    if(resource == NULL) {
        PyErr_SetString(PyExc_ValueError, "unable to load url");
        return NULL;
    }

    return ResourceData_Create(resource);
}

static PyMethodDef ResourceFetcher_methods[] = {
    {"load_url", (PyCFunction)ResourceFetcher_load_url, METH_VARARGS},
    {NULL}
};

static PyTypeObject ResourceFetcher_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plutobook.ResourceFetcher",
    .tp_basicsize = sizeof(PyObject),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_methods = ResourceFetcher_methods,
    .tp_new = PyType_GenericNew
};

typedef struct {
    PyObject_HEAD
    PyObject* default_fetcher;
    PyObject* custom_fetcher;
} ResourceLoader_Object;

static PyObject* ResourceLoader_Create(void);

static void ResourceLoader_dealloc(ResourceLoader_Object* self)
{
    Py_XDECREF(self->default_fetcher);
    Py_XDECREF(self->custom_fetcher);
    PyObject_Del(self);
}

static PyObject* ResourceLoader_get_default_fetcher(ResourceLoader_Object* self, void* closure)
{
    if(self->default_fetcher == NULL)
        self->default_fetcher = PyObject_New(PyObject, &ResourceFetcher_Type);
    Py_INCREF(self->default_fetcher);
    return self->default_fetcher;
}

static PyObject* ResourceLoader_get_custom_fetcher(ResourceLoader_Object* self, void* closure)
{
    if(self->custom_fetcher == NULL)
        Py_RETURN_NONE;
    Py_INCREF(self->custom_fetcher);
    return self->custom_fetcher;
}

plutobook_resource_data_t* resource_load_func(void* closure, const char* url)
{
    PyGILState_STATE gstate = PyGILState_Ensure();
    PyObject* result = PyObject_CallMethod((PyObject*)closure, "load_url", "(s)", url);
    if(result == NULL || !PyObject_TypeCheck(result, &ResourceData_Type)) {
        PyGILState_Release(gstate);
        Py_XDECREF(result);
        return NULL;
    }

    PyGILState_Release(gstate);
    ResourceData_Object* resource_ob = (ResourceData_Object*)(result);
    plutobook_resource_data_t* resource = plutobook_resource_data_reference(resource_ob->resource);
    Py_DECREF(resource_ob);
    return resource;
}

static int ResourceLoader_set_custom_fetcher(ResourceLoader_Object* self, PyObject* value, void* closure)
{
    if(value && !Py_IsNone(value) && !PyObject_TypeCheck(value, &ResourceFetcher_Type)) {
        PyErr_SetString(PyExc_TypeError, "value must be None or an instance of plutobook.ResourceFetcher");
        return -1;
    }

    if(value == NULL || Py_IsNone(value)) {
        plutobook_set_custom_resource_fetcher(NULL, NULL);
    } else {
        plutobook_set_custom_resource_fetcher(resource_load_func, value);
    }

    Py_XINCREF(value);
    Py_XDECREF(self->custom_fetcher);
    self->custom_fetcher = value;
    return 0;
}

static PyGetSetDef ResourceLoader_getset[] = {
    {"default_fetcher", (getter)ResourceLoader_get_default_fetcher, (setter)NULL},
    {"custom_fetcher", (getter)ResourceLoader_get_custom_fetcher, (setter)ResourceLoader_set_custom_fetcher},
    {NULL}
};

static PyTypeObject ResourceLoader_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plutobook.ResourceLoader",
    .tp_basicsize = sizeof(ResourceLoader_Object),
    .tp_dealloc = (destructor)ResourceLoader_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_getset = ResourceLoader_getset
};

static PyObject* ResourceLoader_Create(void)
{
    ResourceLoader_Object* loader_ob = PyObject_New(ResourceLoader_Object, &ResourceLoader_Type);
    loader_ob->custom_fetcher = NULL;
    loader_ob->default_fetcher = NULL;
    return (PyObject*)loader_ob;
}

static PyObject* module_version(PyObject* self, PyObject* args)
{
    return PyLong_FromLong(plutobook_version());
}

static PyObject* module_version_string(PyObject* self, PyObject* args)
{
    return PyUnicode_FromString(plutobook_version_string());
}

static PyMethodDef module_methods[] = {
    {"version", (PyCFunction)module_version, METH_NOARGS},
    {"version_string", (PyCFunction)module_version_string, METH_NOARGS},
    {NULL},
};

static struct PyModuleDef module_definition = {
    PyModuleDef_HEAD_INIT,
    "plutobook",
    0,
    0,
    module_methods,
    0,
    0,
    0,
    0,
};

PyMODINIT_FUNC PyInit_plutobook(void)
{
    if(PyType_Ready(&PageSize_Type) < 0
        || PyType_Ready(&PageMargins_Type) < 0
        || PyType_Ready(&MediaType_Type) < 0
        || PyType_Ready(&Book_Type) < 0
        || PyType_Ready(&PDFMetadata_Type) < 0
        || PyType_Ready(&ImageFormat_Type) < 0
        || PyType_Ready(&ResourceData_Type) < 0
        || PyType_Ready(&ResourceFetcher_Type) < 0
        || PyType_Ready(&ResourceLoader_Type) < 0) {
        return NULL;
    }

    PyObject* module = PyModule_Create(&module_definition);
    if(module == NULL) {
        return NULL;
    }

    Py_INCREF(&PageSize_Type);
    Py_INCREF(&PageMargins_Type);
    Py_INCREF(&MediaType_Type);
    Py_INCREF(&Book_Type);
    Py_INCREF(&PDFMetadata_Type);
    Py_INCREF(&ImageFormat_Type);
    Py_INCREF(&ResourceData_Type);
    Py_INCREF(&ResourceFetcher_Type);
    Py_INCREF(&ResourceLoader_Type);

    PyModule_AddObject(module, "PageSize", (PyObject*)&PageSize_Type);
    PyModule_AddObject(module, "PageMargins", (PyObject*)&PageMargins_Type);
    PyModule_AddObject(module, "MediaType", (PyObject*)&MediaType_Type);
    PyModule_AddObject(module, "Book", (PyObject*)&Book_Type);
    PyModule_AddObject(module, "PDFMetadata", (PyObject*)&PDFMetadata_Type);
    PyModule_AddObject(module, "ImageFormat", (PyObject*)&ImageFormat_Type);
    PyModule_AddObject(module, "ResourceData", (PyObject*)&ResourceData_Type);
    PyModule_AddObject(module, "ResourceFetcher", (PyObject*)&ResourceFetcher_Type);
    PyModule_AddObject(module, "ResourceLoader", (PyObject*)&ResourceLoader_Type);

    PyModule_AddObject(module, "PAGE_SIZE_NONE", PageSize_Create(PLUTOBOOK_PAGE_SIZE_NONE));
    PyModule_AddObject(module, "PAGE_SIZE_LETTER", PageSize_Create(PLUTOBOOK_PAGE_SIZE_LETTER));
    PyModule_AddObject(module, "PAGE_SIZE_LEGAL", PageSize_Create(PLUTOBOOK_PAGE_SIZE_LEGAL));
    PyModule_AddObject(module, "PAGE_SIZE_LEDGER", PageSize_Create(PLUTOBOOK_PAGE_SIZE_LETTER));

    PyModule_AddObject(module, "PAGE_SIZE_A3", PageSize_Create(PLUTOBOOK_PAGE_SIZE_A3));
    PyModule_AddObject(module, "PAGE_SIZE_A4", PageSize_Create(PLUTOBOOK_PAGE_SIZE_A3));
    PyModule_AddObject(module, "PAGE_SIZE_A5", PageSize_Create(PLUTOBOOK_PAGE_SIZE_A5));
    PyModule_AddObject(module, "PAGE_SIZE_B4", PageSize_Create(PLUTOBOOK_PAGE_SIZE_B4));
    PyModule_AddObject(module, "PAGE_SIZE_B5", PageSize_Create(PLUTOBOOK_PAGE_SIZE_B5));

    PyModule_AddObject(module, "PAGE_MARGINS_NONE", PageMargins_Create(PLUTOBOOK_PAGE_MARGINS_NONE));
    PyModule_AddObject(module, "PAGE_MARGINS_NORMAL", PageMargins_Create(PLUTOBOOK_PAGE_MARGINS_NORMAL));
    PyModule_AddObject(module, "PAGE_MARGINS_NARROW", PageMargins_Create(PLUTOBOOK_PAGE_MARGINS_NARROW));
    PyModule_AddObject(module, "PAGE_MARGINS_MODERATE", PageMargins_Create(PLUTOBOOK_PAGE_MARGINS_MODERATE));

    PyModule_AddObject(module, "MEDIA_TYPE_PRINT", MediaType_Create(PLUTOBOOK_MEDIA_TYPE_PRINT));
    PyModule_AddObject(module, "MEDIA_TYPE_SCREEN", MediaType_Create(PLUTOBOOK_MEDIA_TYPE_SCREEN));

    PyModule_AddObject(module, "PDF_METADATA_TITLE", PDFMetadata_Create(PLUTOBOOK_PDF_METADATA_TITLE));
    PyModule_AddObject(module, "PDF_METADATA_AUTHOR", PDFMetadata_Create(PLUTOBOOK_PDF_METADATA_AUTHOR));
    PyModule_AddObject(module, "PDF_METADATA_SUBJECT", PDFMetadata_Create(PLUTOBOOK_PDF_METADATA_SUBJECT));
    PyModule_AddObject(module, "PDF_METADATA_KEYWORDS", PDFMetadata_Create(PLUTOBOOK_PDF_METADATA_KEYWORDS));
    PyModule_AddObject(module, "PDF_METADATA_CREATOR", PDFMetadata_Create(PLUTOBOOK_PDF_METADATA_CREATOR));
    PyModule_AddObject(module, "PDF_METADATA_CREATION_DATE", PDFMetadata_Create(PLUTOBOOK_PDF_METADATA_CREATION_DATE));
    PyModule_AddObject(module, "PDF_METADATA_MODIFICATION_DATE", PDFMetadata_Create(PLUTOBOOK_PDF_METADATA_MODIFICATION_DATE));

    PyModule_AddObject(module, "IMAGE_FORMAT_INVALID", ImageFormat_Create(PLUTOBOOK_IMAGE_FORMAT_INVALID));
    PyModule_AddObject(module, "IMAGE_FORMAT_ARGB32", ImageFormat_Create(PLUTOBOOK_IMAGE_FORMAT_ARGB32));
    PyModule_AddObject(module, "IMAGE_FORMAT_RGB24", ImageFormat_Create(PLUTOBOOK_IMAGE_FORMAT_RGB24));
    PyModule_AddObject(module, "IMAGE_FORMAT_A8", ImageFormat_Create(PLUTOBOOK_IMAGE_FORMAT_A8));
    PyModule_AddObject(module, "IMAGE_FORMAT_A1", ImageFormat_Create(PLUTOBOOK_IMAGE_FORMAT_A1));

    PyModule_AddIntConstant(module, "MIN_PAGE_COUNT", PLUTOBOOK_MIN_PAGE_COUNT);
    PyModule_AddIntConstant(module, "MAX_PAGE_COUNT", PLUTOBOOK_MAX_PAGE_COUNT);

    PyModule_AddObject(module, "UNITS_PT", PyFloat_FromDouble(PLUTOBOOK_UNITS_PT));
    PyModule_AddObject(module, "UNITS_PC", PyFloat_FromDouble(PLUTOBOOK_UNITS_PC));
    PyModule_AddObject(module, "UNITS_IN", PyFloat_FromDouble(PLUTOBOOK_UNITS_IN));
    PyModule_AddObject(module, "UNITS_CM", PyFloat_FromDouble(PLUTOBOOK_UNITS_CM));
    PyModule_AddObject(module, "UNITS_MM", PyFloat_FromDouble(PLUTOBOOK_UNITS_MM));
    PyModule_AddObject(module, "UNITS_PX", PyFloat_FromDouble(PLUTOBOOK_UNITS_PX));

    PyModule_AddObject(module, "resource_loader", ResourceLoader_Create());
    PyModule_AddObject(module, "__version__", PyUnicode_FromString("0.0.12"));
    return module;
}
