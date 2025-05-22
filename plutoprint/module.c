#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#include <plutobook.h>

#ifndef PLUTOPRINT_VERSION_MAJOR
#define PLUTOPRINT_VERSION_MAJOR 0
#endif
#ifndef PLUTOPRINT_VERSION_MINOR
#define PLUTOPRINT_VERSION_MINOR 0
#endif
#ifndef PLUTOPRINT_VERSION_MICRO
#define PLUTOPRINT_VERSION_MICRO 0
#endif

#define PLUTOPRINT_VERSION_STRING PLUTOBOOK_VERSION_STRINGIZE(PLUTOPRINT_VERSION_MAJOR, PLUTOPRINT_VERSION_MINOR, PLUTOPRINT_VERSION_MICRO)

#define Object_New(obj, type) ((obj*)(type)->tp_alloc(type, 0))
#define Object_Del(obj) (Py_TYPE(obj)->tp_free(obj))

typedef struct {
    PyObject_HEAD
    plutobook_page_size_t size;
} PageSize_Object;

static PyObject* PageSize_Create(plutobook_page_size_t size);

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
    Object_Del(self);
}

static PyObject* PageSize_repr(PageSize_Object* self)
{
    char buf[256];
    PyOS_snprintf(buf, sizeof(buf), "plutoprint.PageSize(%g, %g)", self->size.width, self->size.height);
    return PyUnicode_FromString(buf);
}

static PyObject* PageSize_landscape(PageSize_Object* self, PyObject* args)
{
    plutobook_page_size_t size = self->size;
    if(size.width < size.height) {
        size.width = self->size.height;
        size.height = self->size.width;
    }

    return PageSize_Create(size);
}

static PyObject* PageSize_portrait(PageSize_Object* self, PyObject* args)
{
    plutobook_page_size_t size = self->size;
    if(size.width > size.height){
        size.width = self->size.height;
        size.height = self->size.width;
    }

    return PageSize_Create(size);
}

static Py_ssize_t PageSize_length(PageSize_Object* self)
{
    return 2;
}

static PyObject* PageSize_item(PageSize_Object* self, Py_ssize_t index)
{
    switch(index) {
    case 0:
        return PyFloat_FromDouble(self->size.width);
    case 1:
        return PyFloat_FromDouble(self->size.height);
    default:
        PyErr_SetString(PyExc_IndexError, "PageSize index out of range");
        return NULL;
    }
}

static PySequenceMethods PageSize_as_sequence = {
    .sq_length = (lenfunc)PageSize_length,
    .sq_item = (ssizeargfunc)PageSize_item
};

static PyMethodDef PageSize_methods[] = {
    {"landscape", (PyCFunction)PageSize_landscape, METH_NOARGS},
    {"portrait", (PyCFunction)PageSize_portrait, METH_NOARGS},
    {NULL}
};

static PyMemberDef PageSize_members[] = {
    {"width", T_FLOAT, offsetof(PageSize_Object, size.width), READONLY, NULL},
    {"height", T_FLOAT, offsetof(PageSize_Object, size.height), READONLY, NULL},
    {NULL}
};

static PyTypeObject PageSize_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plutoprint.PageSize",
    .tp_basicsize = sizeof(PageSize_Object),
    .tp_dealloc = (destructor)PageSize_dealloc,
    .tp_repr = (reprfunc)PageSize_repr,
    .tp_as_sequence = &PageSize_as_sequence,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_methods = PageSize_methods,
    .tp_members = PageSize_members,
    .tp_new = (newfunc)PageSize_new
};

static PyObject* PageSize_Create(plutobook_page_size_t size)
{
    PageSize_Object* size_ob = Object_New(PageSize_Object, &PageSize_Type);
    size_ob->size = size;
    return (PyObject*)size_ob;
}

typedef struct {
    PyObject_HEAD
    plutobook_page_margins_t margins;
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
    Object_Del(self);
}

static PyObject* PageMargins_repr(PageMargins_Object* self)
{
    char buf[256];
    PyOS_snprintf(buf, sizeof(buf), "plutoprint.PageMargins(%g, %g, %g, %g)", self->margins.top, self->margins.right, self->margins.bottom, self->margins.left);
    return PyUnicode_FromString(buf);
}

static Py_ssize_t PageMargins_length(PageMargins_Object* self)
{
    return 4;
}

static PyObject* PageMargins_item(PageMargins_Object* self, Py_ssize_t index)
{
    switch(index) {
    case 0:
        return PyFloat_FromDouble(self->margins.top);
    case 1:
        return PyFloat_FromDouble(self->margins.right);
    case 2:
        return PyFloat_FromDouble(self->margins.bottom);
    case 3:
        return PyFloat_FromDouble(self->margins.left);
    default:
        PyErr_SetString(PyExc_IndexError, "PageMargins index out of range");
        return NULL;
    }
}

static PySequenceMethods PageMargins_as_sequence = {
    .sq_length = (lenfunc)PageMargins_length,
    .sq_item = (ssizeargfunc)PageMargins_item
};

static PyMemberDef PageMargins_members[] = {
    {"top", T_FLOAT, offsetof(PageMargins_Object, margins.top), READONLY, NULL},
    {"right", T_FLOAT, offsetof(PageMargins_Object, margins.right), READONLY, NULL},
    {"bottom", T_FLOAT, offsetof(PageMargins_Object, margins.bottom), READONLY, NULL},
    {"left", T_FLOAT, offsetof(PageMargins_Object, margins.left), READONLY, NULL},
    {NULL}
};

static PyTypeObject PageMargins_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plutoprint.PageMargins",
    .tp_basicsize = sizeof(PageMargins_Object),
    .tp_dealloc = (destructor)PageMargins_dealloc,
    .tp_repr = (reprfunc)PageMargins_repr,
    .tp_as_sequence = &PageMargins_as_sequence,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_members = PageMargins_members,
    .tp_new = (newfunc)PageMargins_new
};

static PyObject* PageMargins_Create(plutobook_page_margins_t margins)
{
    PageMargins_Object* margins_ob = Object_New(PageMargins_Object, &PageMargins_Type);
    margins_ob->margins = margins;
    return (PyObject*)margins_ob;
}

typedef struct {
    PyObject_HEAD
    plutobook_media_type_t value;
} MediaType_Object;

static void MediaType_dealloc(MediaType_Object* self)
{
    Object_Del(self);
}

static PyObject* MediaType_repr(MediaType_Object* self)
{
    switch(self->value) {
    case PLUTOBOOK_MEDIA_TYPE_PRINT:
        return PyUnicode_FromString("plutoprint.MEDIA_TYPE_PRINT");
    case PLUTOBOOK_MEDIA_TYPE_SCREEN:
        return PyUnicode_FromString("plutoprint.MEDIA_TYPE_SCREEN");
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
    .tp_name = "plutoprint.MediaType",
    .tp_basicsize = sizeof(MediaType_Object),
    .tp_dealloc = (destructor)MediaType_dealloc,
    .tp_repr = (reprfunc)MediaType_repr,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_richcompare = (richcmpfunc)MediaType_richcompare
};

static PyObject* MediaType_Create(plutobook_media_type_t value)
{
    MediaType_Object* media_ob = Object_New(MediaType_Object, &MediaType_Type);
    media_ob->value = value;
    return (PyObject*)media_ob;
}

typedef struct {
    PyObject_HEAD
    plutobook_pdf_metadata_t value;
} PDFMetadata_Object;

static void PDFMetadata_dealloc(PDFMetadata_Object* self)
{
    Object_Del(self);
}

static PyObject* PDFMetadata_repr(PDFMetadata_Object* self)
{
    switch(self->value) {
    case PLUTOBOOK_PDF_METADATA_TITLE:
        return PyUnicode_FromString("plutoprint.PDF_METADATA_TITLE");
    case PLUTOBOOK_PDF_METADATA_AUTHOR:
        return PyUnicode_FromString("plutoprint.PDF_METADATA_AUTHOR");
    case PLUTOBOOK_PDF_METADATA_SUBJECT:
        return PyUnicode_FromString("plutoprint.PDF_METADATA_SUBJECT");
    case PLUTOBOOK_PDF_METADATA_KEYWORDS:
        return PyUnicode_FromString("plutoprint.PDF_METADATA_KEYWORDS");
    case PLUTOBOOK_PDF_METADATA_CREATOR:
        return PyUnicode_FromString("plutoprint.PDF_METADATA_CREATOR");
    case PLUTOBOOK_PDF_METADATA_CREATION_DATE:
        return PyUnicode_FromString("plutoprint.PDF_METADATA_CREATION_DATE");
    case PLUTOBOOK_PDF_METADATA_MODIFICATION_DATE:
        return PyUnicode_FromString("plutoprint.PDF_METADATA_MODIFICATION_DATE");
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
    .tp_name = "plutoprint.PDFMetadata",
    .tp_basicsize = sizeof(PDFMetadata_Object),
    .tp_dealloc = (destructor)PDFMetadata_dealloc,
    .tp_repr = (reprfunc)PDFMetadata_repr,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_richcompare = (richcmpfunc)PDFMetadata_richcompare
};

static PyObject* PDFMetadata_Create(plutobook_pdf_metadata_t value)
{
    PDFMetadata_Object* metadata_ob = Object_New(PDFMetadata_Object, &PDFMetadata_Type);
    metadata_ob->value = value;
    return (PyObject*)metadata_ob;
}

typedef struct {
    PyObject_HEAD
    plutobook_image_format_t value;
} ImageFormat_Object;

static void ImageFormat_dealloc(ImageFormat_Object* self)
{
    Object_Del(self);
}

static PyObject* ImageFormat_repr(ImageFormat_Object* self)
{
    switch(self->value) {
    case PLUTOBOOK_IMAGE_FORMAT_INVALID:
        return PyUnicode_FromString("plutoprint.IMAGE_FORMAT_INVALID");
    case PLUTOBOOK_IMAGE_FORMAT_ARGB32:
        return PyUnicode_FromString("plutoprint.IMAGE_FORMAT_ARGB32");
    case PLUTOBOOK_IMAGE_FORMAT_RGB24:
        return PyUnicode_FromString("plutoprint.IMAGE_FORMAT_RGB24");
    case PLUTOBOOK_IMAGE_FORMAT_A8:
        return PyUnicode_FromString("plutoprint.IMAGE_FORMAT_A8");
    case PLUTOBOOK_IMAGE_FORMAT_A1:
        return PyUnicode_FromString("plutoprint.IMAGE_FORMAT_A1");
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
    .tp_name = "plutoprint.ImageFormat",
    .tp_basicsize = sizeof(ImageFormat_Object),
    .tp_dealloc = (destructor)ImageFormat_dealloc,
    .tp_repr = (reprfunc)ImageFormat_repr,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_richcompare = (richcmpfunc)ImageFormat_richcompare
};

static PyObject* ImageFormat_Create(plutobook_image_format_t value)
{
    ImageFormat_Object* format_ob = Object_New(ImageFormat_Object, &ImageFormat_Type);
    format_ob->value = value;
    return (PyObject*)format_ob;
}

typedef struct {
    PyObject_HEAD
    plutobook_canvas_t* canvas;
    PyObject* data;
} Canvas_Object;

static void Canvas_dealloc(Canvas_Object* self)
{
    plutobook_canvas_destroy(self->canvas);
    Py_XDECREF(self->data);
    Object_Del(self);
}

static PyObject* Canvas__enter__(Canvas_Object* self, PyObject* args)
{
    Py_INCREF(self);
    return (PyObject*)self;
}

static PyObject* Canvas__exit__(Canvas_Object* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS
    plutobook_canvas_finish(self->canvas);
    Py_END_ALLOW_THREADS
    Py_RETURN_NONE;
}

static PyObject* Canvas_flush(Canvas_Object* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS
    plutobook_canvas_flush(self->canvas);
    Py_END_ALLOW_THREADS
    Py_RETURN_NONE;
}

static PyObject* Canvas_finish(Canvas_Object* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS
    plutobook_canvas_finish(self->canvas);
    Py_END_ALLOW_THREADS
    Py_RETURN_NONE;
}

static PyObject* Canvas_translate(Canvas_Object* self, PyObject* args)
{
    float tx, ty;
    if(!PyArg_ParseTuple(args, "ff", &tx, &ty)) {
        return NULL;
    }

    plutobook_canvas_translate(self->canvas, tx, ty);
    Py_RETURN_NONE;
}

static PyObject* Canvas_scale(Canvas_Object* self, PyObject* args)
{
    float sx, sy;
    if(!PyArg_ParseTuple(args, "ff", &sx, &sy)) {
        return NULL;
    }

    plutobook_canvas_scale(self->canvas, sx, sy);
    Py_RETURN_NONE;
}

static PyObject* Canvas_rotate(Canvas_Object* self, PyObject* args)
{
    float angle;
    if(!PyArg_ParseTuple(args, "f", &angle)) {
        return NULL;
    }

    plutobook_canvas_rotate(self->canvas, angle);
    Py_RETURN_NONE;
}

static PyObject* Canvas_transform(Canvas_Object* self, PyObject* args)
{
    float a, b, c, d, e, f;
    if(!PyArg_ParseTuple(args, "ffffff", &a, &b, &c, &d, &e, &f)) {
        return NULL;
    }

    plutobook_canvas_transform(self->canvas, a, b, c, d, e, f);
    Py_RETURN_NONE;
}

static PyObject* Canvas_set_matrix(Canvas_Object* self, PyObject* args)
{
    float a, b, c, d, e, f;
    if(!PyArg_ParseTuple(args, "ffffff", &a, &b, &c, &d, &e, &f)) {
        return NULL;
    }

    plutobook_canvas_set_matrix(self->canvas, a, b, c, d, e, f);
    Py_RETURN_NONE;
}

static PyObject* Canvas_reset_matrix(Canvas_Object* self, PyObject* args)
{
    plutobook_canvas_reset_matrix(self->canvas);
    Py_RETURN_NONE;
}

static PyObject* Canvas_clip_rect(Canvas_Object* self, PyObject* args)
{
    float x, y, width, height;
    if(!PyArg_ParseTuple(args, "ffff", &x, &y, &width, &height)) {
        return NULL;
    }

    Py_BEGIN_ALLOW_THREADS
    plutobook_canvas_clip_rect(self->canvas, x, y, width, height);
    Py_END_ALLOW_THREADS
    Py_RETURN_NONE;
}

static PyObject* Canvas_clear_surface(Canvas_Object* self, PyObject* args)
{
    float red, green, blue, alpha = 1.f;
    if(!PyArg_ParseTuple(args, "fff|f", &red, &green, &blue, &alpha)) {
        return NULL;
    }

    Py_BEGIN_ALLOW_THREADS
    plutobook_canvas_clear_surface(self->canvas, red, blue, green, alpha);
    Py_END_ALLOW_THREADS
    Py_RETURN_NONE;
}

static PyObject* Canvas_save_state(Canvas_Object* self, PyObject* args)
{
    plutobook_canvas_save_state(self->canvas);
    Py_RETURN_NONE;
}

static PyObject* Canvas_restore_state(Canvas_Object* self, PyObject* args)
{
    plutobook_canvas_restore_state(self->canvas);
    Py_RETURN_NONE;
}

static PyMethodDef Canvas_methods[] = {
    {"__enter__", (PyCFunction)Canvas__enter__, METH_NOARGS},
    {"__exit__", (PyCFunction)Canvas__exit__, METH_VARARGS},
    {"flush", (PyCFunction)Canvas_flush, METH_NOARGS},
    {"finish", (PyCFunction)Canvas_finish, METH_NOARGS},
    {"translate", (PyCFunction)Canvas_translate, METH_VARARGS},
    {"scale", (PyCFunction)Canvas_scale, METH_VARARGS},
    {"rotate", (PyCFunction)Canvas_rotate, METH_VARARGS},
    {"transform", (PyCFunction)Canvas_transform, METH_VARARGS},
    {"set_matrix", (PyCFunction)Canvas_set_matrix, METH_VARARGS},
    {"reset_matrix", (PyCFunction)Canvas_reset_matrix, METH_NOARGS},
    {"clip_rect", (PyCFunction)Canvas_clip_rect, METH_VARARGS},
    {"clear_surface", (PyCFunction)Canvas_clear_surface, METH_VARARGS},
    {"save_state", (PyCFunction)Canvas_save_state, METH_NOARGS},
    {"restore_state", (PyCFunction)Canvas_restore_state, METH_NOARGS},
    {NULL}
};

static PyTypeObject Canvas_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plutoprint.Canvas",
    .tp_basicsize = sizeof(Canvas_Object),
    .tp_dealloc = (destructor)Canvas_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_methods = Canvas_methods
};

static PyObject* Error_Object;

#define TRAP_ERROR(variable, function) \
    bool variable; \
    Py_BEGIN_ALLOW_THREADS \
    variable = (function); \
    Py_END_ALLOW_THREADS \

#define RETURN_NULL_IF_ERROR(variable) \
    if (!(variable)) { \
        PyErr_SetString(Error_Object, plutobook_get_error_message()); \
        return NULL; \
    } \

typedef Canvas_Object ImageCanvas_Object;

static PyObject* ImageCanvas_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
    int width, height;
    ImageFormat_Object* format_ob = NULL;
    if(!PyArg_ParseTuple(args, "ii|O!:ImageCanvas.__init__", &width, &height, &ImageFormat_Type, &format_ob))
        return NULL;
    plutobook_image_format_t format = PLUTOBOOK_IMAGE_FORMAT_ARGB32;
    if(format_ob) {
        format = format_ob->value;
    }

    plutobook_canvas_t* canvas = plutobook_image_canvas_create(width, height, format);
    if(canvas == NULL) {
        PyErr_SetString(Error_Object, plutobook_get_error_message());
        return NULL;
    }

    ImageCanvas_Object* canvas_ob = Object_New(ImageCanvas_Object, type);
    canvas_ob->canvas = canvas;
    canvas_ob->data = NULL;
    return (PyObject*)canvas_ob;
}

static PyObject* ImageCanvas_create_for_data(PyTypeObject* type, PyObject* args)
{
    PyObject* data;
    int width, height, stride;
    ImageFormat_Object* format_ob = NULL;
    if(!PyArg_ParseTuple(args, "Oiii|O!", &data, &width, &height, &stride, &ImageFormat_Type, &format_ob))
        return NULL;
    plutobook_image_format_t format = PLUTOBOOK_IMAGE_FORMAT_ARGB32;
    if(format_ob) {
        format = format_ob->value;
    }

    Py_buffer buffer;
    if(PyObject_GetBuffer(data, &buffer, PyBUF_WRITABLE) == -1)
        return NULL;
    if(height * stride > buffer.len) {
        PyBuffer_Release(&buffer);
        PyErr_SetString(PyExc_ValueError, "buffer is not long enough");
        return NULL;
    }

    plutobook_canvas_t* canvas = plutobook_image_canvas_create_for_data(buffer.buf, width, height, stride, format);
    if(canvas == NULL) {
        PyBuffer_Release(&buffer);
        PyErr_SetString(Error_Object, plutobook_get_error_message());
        return NULL;
    }

    ImageCanvas_Object* canvas_ob = Object_New(ImageCanvas_Object, type);
    canvas_ob->canvas = canvas;
    canvas_ob->data = data;
    Py_INCREF(canvas_ob->data);
    PyBuffer_Release(&buffer);
    return (PyObject*)canvas_ob;
}

static PyObject* ImageCanvas_get_data(ImageCanvas_Object* self, PyObject* args)
{
    return PyMemoryView_FromObject((PyObject*)self);
}

static PyObject* ImageCanvas_get_width(ImageCanvas_Object* self, PyObject* args)
{
    return PyLong_FromLong(plutobook_image_canvas_get_width(self->canvas));
}

static PyObject* ImageCanvas_get_height(ImageCanvas_Object* self, PyObject* args)
{
    return PyLong_FromLong(plutobook_image_canvas_get_height(self->canvas));
}

static PyObject* ImageCanvas_get_stride(ImageCanvas_Object* self, PyObject* args)
{
    return PyLong_FromLong(plutobook_image_canvas_get_stride(self->canvas));
}

static PyObject* ImageCanvas_get_format(ImageCanvas_Object* self, PyObject* args)
{
    return ImageFormat_Create(plutobook_image_canvas_get_format(self->canvas));
}

static plutobook_stream_status_t stream_write_func(void* closure, const char* data, unsigned int length)
{
    PyGILState_STATE gstate = PyGILState_Ensure();
    PyObject* result = PyObject_CallFunction((PyObject*)closure, "(y#)", data, length);
    if(result == NULL) {
        PyGILState_Release(gstate);
        return PLUTOBOOK_STREAM_STATUS_SUCCESS;
    }

    Py_DECREF(result);
    PyGILState_Release(gstate);
    return PLUTOBOOK_STREAM_STATUS_SUCCESS;
}

static int stream_write_conv(PyObject* ob, PyObject** target)
{
    if(PyObject_HasAttrString(ob, "write")) {
        PyObject* write_method = PyObject_GetAttrString(ob, "write");
        if(write_method && PyCallable_Check(write_method)) {
            *target = write_method;
            return 1;
        }

        Py_XDECREF(write_method);
    }

    PyErr_SetString(PyExc_TypeError, "stream must have a \"write\" method");
    return 0;
}

static PyObject* ImageCanvas_write_to_png(ImageCanvas_Object* self, PyObject* args)
{
    PyObject* file_ob;
    if(!PyArg_ParseTuple(args, "O&", PyUnicode_FSConverter, &file_ob)) {
        return NULL;
    }

    const char* filename = PyBytes_AS_STRING(file_ob);
    TRAP_ERROR(success, plutobook_image_canvas_write_to_png(self->canvas, filename));
    Py_DECREF(file_ob);
    RETURN_NULL_IF_ERROR(success);
    Py_RETURN_NONE;
}

static PyObject* ImageCanvas_write_to_png_stream(ImageCanvas_Object* self, PyObject* args)
{
    PyObject* write_ob;
    if(!PyArg_ParseTuple(args, "O&", stream_write_conv, &write_ob)) {
        return NULL;
    }

    TRAP_ERROR(success, plutobook_image_canvas_write_to_png_stream(self->canvas, stream_write_func, write_ob));
    Py_DECREF(write_ob);
    RETURN_NULL_IF_ERROR(success);
    Py_RETURN_NONE;
}

static int ImageCanvas_get_buffer(ImageCanvas_Object* self, Py_buffer* view, int flags)
{
    void* data = plutobook_image_canvas_get_data(self->canvas);
    int height = plutobook_image_canvas_get_height(self->canvas);
    int stride = plutobook_image_canvas_get_stride(self->canvas);
    return PyBuffer_FillInfo(view, (PyObject*)self, data, height * stride, 0, flags);
}

static PyBufferProcs ImageCanvas_as_buffer = {
    (getbufferproc)ImageCanvas_get_buffer,
    NULL
};

static PyMethodDef ImageCanvas_methods[] = {
    {"create_for_data", (PyCFunction)ImageCanvas_create_for_data, METH_VARARGS | METH_CLASS},
    {"get_data", (PyCFunction)ImageCanvas_get_data, METH_NOARGS},
    {"get_width", (PyCFunction)ImageCanvas_get_width, METH_NOARGS},
    {"get_height", (PyCFunction)ImageCanvas_get_height, METH_NOARGS},
    {"get_stride", (PyCFunction)ImageCanvas_get_stride, METH_NOARGS},
    {"get_format", (PyCFunction)ImageCanvas_get_format, METH_NOARGS},
    {"write_to_png", (PyCFunction)ImageCanvas_write_to_png, METH_VARARGS},
    {"write_to_png_stream", (PyCFunction)ImageCanvas_write_to_png_stream, METH_VARARGS},
    {NULL}
};

static PyTypeObject ImageCanvas_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plutoprint.ImageCanvas",
    .tp_basicsize = sizeof(ImageCanvas_Object),
    .tp_as_buffer = &ImageCanvas_as_buffer,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_methods = ImageCanvas_methods,
    .tp_base = &Canvas_Type,
    .tp_new = (newfunc)ImageCanvas_new
};

typedef Canvas_Object PDFCanvas_Object;

static PyObject* PDFCanvas_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
    PyObject* file_ob;
    PageSize_Object* size_ob;
    if(!PyArg_ParseTuple(args, "O&O!:PDFCanvas.__init__", PyUnicode_FSConverter, &file_ob, &PageSize_Type, &size_ob))
        return NULL;
    const char* filename = PyBytes_AS_STRING(file_ob);
    plutobook_canvas_t* canvas = plutobook_pdf_canvas_create(filename, size_ob->size);
    if(canvas == NULL) {
        Py_DECREF(file_ob);
        PyErr_SetString(Error_Object, plutobook_get_error_message());
        return NULL;
    }

    PDFCanvas_Object* canvas_ob = Object_New(PDFCanvas_Object, type);
    canvas_ob->canvas = canvas;
    canvas_ob->data = NULL;
    Py_DECREF(file_ob);
    return (PyObject*)canvas_ob;
}

static PyObject* PDFCanvas_create_for_stream(PyTypeObject* type, PyObject* args)
{
    PyObject* write_ob;
    PageSize_Object* size_ob = NULL;
    if(!PyArg_ParseTuple(args, "O&O!", stream_write_conv, &write_ob, &PageSize_Type, &size_ob))
        return NULL;
    plutobook_canvas_t* canvas = plutobook_pdf_canvas_create_for_stream(stream_write_func, write_ob, size_ob->size);
    if(canvas == NULL) {
        Py_DECREF(write_ob);
        PyErr_SetString(Error_Object, plutobook_get_error_message());
        return NULL;
    }

    PDFCanvas_Object* canvas_ob = Object_New(PDFCanvas_Object, type);
    canvas_ob->canvas = canvas;
    canvas_ob->data = write_ob;
    return (PyObject*)canvas_ob;
}

static PyObject* PDFCanvas_set_metadata(PDFCanvas_Object* self, PyObject* args)
{
    PDFMetadata_Object* metadata_ob;
    const char* value;
    if(!PyArg_ParseTuple(args, "O!s", &PDFMetadata_Type, &metadata_ob, &value))
        return NULL;
    plutobook_pdf_canvas_set_metadata(self->canvas, metadata_ob->value, value);
    Py_RETURN_NONE;
}

static PyObject* PDFCanvas_set_size(PDFCanvas_Object* self, PyObject* args)
{
    PageSize_Object* size_ob;
    if(!PyArg_ParseTuple(args, "O!", &PageSize_Type, &size_ob))
        return NULL;
    plutobook_pdf_canvas_set_size(self->canvas, size_ob->size);
    Py_RETURN_NONE;
}

static PyObject* PDFCanvas_show_page(PDFCanvas_Object* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS
    plutobook_pdf_canvas_show_page(self->canvas);
    Py_END_ALLOW_THREADS
    Py_RETURN_NONE;
}

static PyMethodDef PDFCanvas_methods[] = {
    {"create_for_stream", (PyCFunction)PDFCanvas_create_for_stream, METH_VARARGS | METH_CLASS},
    {"set_metadata", (PyCFunction)PDFCanvas_set_metadata, METH_VARARGS},
    {"set_size", (PyCFunction)PDFCanvas_set_size, METH_VARARGS},
    {"show_page", (PyCFunction)PDFCanvas_show_page, METH_NOARGS},
    {NULL}
};

static PyTypeObject PDFCanvas_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plutoprint.PDFCanvas",
    .tp_basicsize = sizeof(PDFCanvas_Object),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_methods = PDFCanvas_methods,
    .tp_base = &Canvas_Type,
    .tp_new = (newfunc)PDFCanvas_new
};

typedef struct {
    PyObject_HEAD
    plutobook_resource_data_t* resource;
} ResourceData_Object;

static PyObject* ResourceData_Create(plutobook_resource_data_t* resource);

static void resource_destroy_func(void* data)
{
    Py_buffer* buffer = (Py_buffer*)data;
    PyGILState_STATE gstate = PyGILState_Ensure();
    PyBuffer_Release(buffer);
    PyMem_Free(buffer);
    PyGILState_Release(gstate);
}

static PyObject* ResourceData_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
    static char* kwlist[] = { "content", "mime_type", "text_encoding", NULL };
    Py_buffer* content = PyMem_Malloc(sizeof(Py_buffer));
    const char* mime_type = "";
    const char* text_encoding = "";
    if(!PyArg_ParseTupleAndKeywords(args, kwds, "s*|ss:ResourceData.__init__", kwlist, content, &mime_type, &text_encoding)) {
        PyMem_Free(content);
        return NULL;
    }

    plutobook_resource_data_t* resource;
    Py_BEGIN_ALLOW_THREADS
    resource = plutobook_resource_data_create_without_copy(content->buf, content->len, mime_type, text_encoding, resource_destroy_func, content);
    Py_END_ALLOW_THREADS
    if(resource == NULL) {
        PyErr_SetString(Error_Object, plutobook_get_error_message());
        PyBuffer_Release(content);
        PyMem_Free(content);
        return NULL;
    }

    return ResourceData_Create(resource);
}

static void ResourceData_dealloc(ResourceData_Object* self)
{
    plutobook_resource_data_destroy(self->resource);
    Object_Del(self);
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
    .tp_name = "plutoprint.ResourceData",
    .tp_basicsize = sizeof(ResourceData_Object),
    .tp_dealloc = (destructor)ResourceData_dealloc,
    .tp_as_buffer = &ResourceData_as_buffer,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_methods = ResourceData_methods,
    .tp_new = (newfunc)ResourceData_new
};

static PyObject* ResourceData_Create(plutobook_resource_data_t* resource)
{
    ResourceData_Object* resource_ob = Object_New(ResourceData_Object, &ResourceData_Type);
    resource_ob->resource = resource;
    return (PyObject*)resource_ob;
}

typedef PyObject ResourceFetcher_Object;

static PyObject* ResourceFetcher_fetch_url(ResourceFetcher_Object* self, PyObject* args)
{
    const char* url;
    if(!PyArg_ParseTuple(args, "s", &url)) {
        return NULL;
    }

    plutobook_resource_data_t* resource;
    Py_BEGIN_ALLOW_THREADS
    resource = plutobook_fetch_url(url);
    Py_END_ALLOW_THREADS
    if(resource == NULL) {
        PyErr_SetString(Error_Object, plutobook_get_error_message());
        return NULL;
    }

    return ResourceData_Create(resource);
}

static PyMethodDef ResourceFetcher_methods[] = {
    {"fetch_url", (PyCFunction)ResourceFetcher_fetch_url, METH_VARARGS},
    {NULL}
};

static PyTypeObject ResourceFetcher_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plutoprint.ResourceFetcher",
    .tp_basicsize = sizeof(ResourceFetcher_Object),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_methods = ResourceFetcher_methods,
    .tp_new = PyType_GenericNew
};

static PyObject* ResourceFetcher_Create(void)
{
    return Object_New(ResourceFetcher_Object, &ResourceFetcher_Type);
}

static plutobook_resource_data_t* resource_fetch_func(void* closure, const char* url)
{
    PyGILState_STATE gstate = PyGILState_Ensure();
    PyObject* result = PyObject_CallMethod((PyObject*)closure, "fetch_url", "(s)", url);
    if(result == NULL || !PyObject_TypeCheck(result, &ResourceData_Type)) {
        Py_XDECREF(result);
        PyGILState_Release(gstate);
        return NULL;
    }

    ResourceData_Object* resource_ob = (ResourceData_Object*)(result);
    plutobook_resource_data_t* resource = plutobook_resource_data_reference(resource_ob->resource);
    Py_DECREF(resource_ob);
    PyGILState_Release(gstate);
    return resource;
}

typedef struct {
    PyObject_HEAD
    plutobook_t* book;
    PyObject* custom_resource_fetcher;
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
        size = size_ob->size;
    }

    plutobook_page_margins_t margins = PLUTOBOOK_PAGE_MARGINS_NORMAL;
    if(margins_ob) {
        margins = margins_ob->margins;
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
    Py_XDECREF(self->custom_resource_fetcher);
    Object_Del(self);
}

static PyObject* Book_get_viewport_width(Book_Object* self, PyObject* args)
{
    return PyFloat_FromDouble(plutobook_get_viewport_width(self->book));
}

static PyObject* Book_get_viewport_height(Book_Object* self, PyObject* args)
{
    return PyFloat_FromDouble(plutobook_get_viewport_height(self->book));
}

static PyObject* Book_get_document_width(Book_Object* self, PyObject* args)
{
    float document_width;
    Py_BEGIN_ALLOW_THREADS
    document_width = plutobook_get_document_width(self->book);
    Py_END_ALLOW_THREADS
    return PyFloat_FromDouble(document_width);
}

static PyObject* Book_get_document_height(Book_Object* self, PyObject* args)
{
    float document_height;
    Py_BEGIN_ALLOW_THREADS
    document_height = plutobook_get_document_height(self->book);
    Py_END_ALLOW_THREADS
    return PyFloat_FromDouble(document_height);
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

static PyObject* Book_load_url(Book_Object* self, PyObject* args, PyObject* kwds)
{
    static char* kwlist[] = { "url", "user_style", "user_script", NULL };
    const char* url;
    const char* user_style = "";
    const char* user_script = "";
    if(!PyArg_ParseTupleAndKeywords(args, kwds, "s|ss", kwlist, &url, &user_style, &user_script)) {
        return NULL;
    }

    TRAP_ERROR(success, plutobook_load_url(self->book, url, user_style, user_script));
    RETURN_NULL_IF_ERROR(success);
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

    TRAP_ERROR(success, plutobook_load_data(self->book, data.buf, data.len, mime_type, text_encoding, user_style, user_script, base_url));
    PyBuffer_Release(&data);
    RETURN_NULL_IF_ERROR(success);
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

    TRAP_ERROR(success, plutobook_load_image(self->book, data.buf, data.len, mime_type, text_encoding, user_style, user_script, base_url));
    PyBuffer_Release(&data);
    RETURN_NULL_IF_ERROR(success);
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

    TRAP_ERROR(success, plutobook_load_xml(self->book, data, -1, user_style, user_script, base_url));
    RETURN_NULL_IF_ERROR(success);
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

    TRAP_ERROR(success, plutobook_load_html(self->book, data, -1, user_style, user_script, base_url));
    RETURN_NULL_IF_ERROR(success);
    Py_RETURN_NONE;
}

static PyObject* Book_clear_content(Book_Object* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS
    plutobook_clear_content(self->book);
    Py_END_ALLOW_THREADS
    Py_RETURN_NONE;
}

static PyObject* Book_render_page(Book_Object* self, PyObject* args)
{
    Canvas_Object* canvas_ob;
    unsigned int page_index;
    if(!PyArg_ParseTuple(args, "O!I", &Canvas_Type, &canvas_ob, &page_index)) {
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

    Py_BEGIN_ALLOW_THREADS
    plutobook_render_page(self->book, canvas_ob->canvas, page_index);
    Py_END_ALLOW_THREADS
    Py_RETURN_NONE;
}

static PyObject* Book_render_document(Book_Object* self, PyObject* args)
{
    Canvas_Object* canvas_ob;
    float x, y, width, height;
    if(!PyArg_ParseTuple(args, "O!|(ffff)", &Canvas_Type, &canvas_ob, &x, &y, &width, &height)) {
        return NULL;
    }

    Py_BEGIN_ALLOW_THREADS
    if(PyTuple_Size(args) == 1) {
        plutobook_render_document(self->book, canvas_ob->canvas);
    } else {
        plutobook_render_document_rect(self->book, canvas_ob->canvas, x, y, width, height);
    }

    Py_END_ALLOW_THREADS
    Py_RETURN_NONE;
}

static PyObject* Book_write_to_pdf(Book_Object* self, PyObject* args, PyObject* kwds)
{
    static char* kwlist[] = { "filename", "from_page", "to_page", "page_step", NULL };
    PyObject* file_ob;
    unsigned int from_page = PLUTOBOOK_MIN_PAGE_COUNT;
    unsigned int to_page = PLUTOBOOK_MAX_PAGE_COUNT;
    int page_step = 1;
    if(!PyArg_ParseTupleAndKeywords(args, kwds, "O&|IIi", kwlist, PyUnicode_FSConverter, &file_ob, &from_page, &to_page, &page_step)) {
        return NULL;
    }

    const char* filename = PyBytes_AS_STRING(file_ob);
    TRAP_ERROR(success, plutobook_write_to_pdf_range(self->book, filename, from_page, to_page, page_step));
    Py_DECREF(file_ob);
    RETURN_NULL_IF_ERROR(success);
    Py_RETURN_NONE;
}

static PyObject* Book_write_to_pdf_stream(Book_Object* self, PyObject* args, PyObject* kwds)
{
    static char* kwlist[] = { "stream", "from_page", "to_page", "page_step", NULL };
    PyObject* write_ob;
    unsigned int from_page = PLUTOBOOK_MIN_PAGE_COUNT;
    unsigned int to_page = PLUTOBOOK_MAX_PAGE_COUNT;
    int page_step = 1;
    if(!PyArg_ParseTupleAndKeywords(args, kwds, "O&|IIi", kwlist, stream_write_conv, &write_ob, &from_page, &to_page, &page_step)) {
        return NULL;
    }

    TRAP_ERROR(success, plutobook_write_to_pdf_stream_range(self->book, stream_write_func, write_ob, from_page, to_page, page_step));
    Py_DECREF(write_ob);
    RETURN_NULL_IF_ERROR(success);
    Py_RETURN_NONE;
}

static PyObject* Book_write_to_png(Book_Object* self, PyObject* args)
{
    PyObject* file_ob;
    ImageFormat_Object* format_ob = NULL;
    if(!PyArg_ParseTuple(args, "O&|O!", PyUnicode_FSConverter, &file_ob, &ImageFormat_Type, &format_ob)) {
        return NULL;
    }

    plutobook_image_format_t format = PLUTOBOOK_IMAGE_FORMAT_ARGB32;
    if(format_ob) {
        format = format_ob->value;
    }

    const char* filename = PyBytes_AS_STRING(file_ob);
    TRAP_ERROR(success, plutobook_write_to_png(self->book, filename, format));
    Py_DECREF(file_ob);
    RETURN_NULL_IF_ERROR(success);
    Py_RETURN_NONE;
}

static PyObject* Book_write_to_png_stream(Book_Object* self, PyObject* args)
{
    PyObject* write_ob;
    ImageFormat_Object* format_ob = NULL;
    if(!PyArg_ParseTuple(args, "O&|O!", stream_write_conv, &write_ob, &ImageFormat_Type, &format_ob)) {
        return NULL;
    }

    plutobook_image_format_t format = PLUTOBOOK_IMAGE_FORMAT_ARGB32;
    if(format_ob) {
        format = format_ob->value;
    }

    TRAP_ERROR(success, plutobook_write_to_png_stream(self->book, stream_write_func, write_ob, format));
    Py_DECREF(write_ob);
    RETURN_NULL_IF_ERROR(success);
    Py_RETURN_NONE;
}

static PyObject* Book_get_custom_resource_fetcher(Book_Object* self, void* closure)
{
    if(self->custom_resource_fetcher == NULL)
        Py_RETURN_NONE;
    Py_INCREF(self->custom_resource_fetcher);
    return self->custom_resource_fetcher;
}

static int Book_set_custom_resource_fetcher(Book_Object* self, PyObject* value, void* closure)
{
    if(value && value != Py_None && !PyObject_TypeCheck(value, &ResourceFetcher_Type)) {
        PyErr_SetString(PyExc_TypeError, "value must be None or an instance of plutoprint.ResourceFetcher");
        return -1;
    }

    if(value == NULL || value == Py_None) {
        plutobook_set_custom_resource_fetcher(self->book, NULL, NULL);
    } else {
        plutobook_set_custom_resource_fetcher(self->book, resource_fetch_func, value);
    }

    Py_XINCREF(value);
    Py_XDECREF(self->custom_resource_fetcher);
    self->custom_resource_fetcher = value;
    return 0;
}

static PyGetSetDef Book_getset[] = {
    {"custom_resource_fetcher", (getter)Book_get_custom_resource_fetcher, (setter)Book_set_custom_resource_fetcher},
    {NULL}
};

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
    {"clear_content", (PyCFunction)Book_clear_content, METH_NOARGS},
    {"render_page", (PyCFunction)Book_render_page, METH_VARARGS},
    {"render_document", (PyCFunction)Book_render_document, METH_VARARGS},
    {"write_to_pdf", (PyCFunction)Book_write_to_pdf, METH_VARARGS | METH_KEYWORDS},
    {"write_to_pdf_stream", (PyCFunction)Book_write_to_pdf_stream, METH_VARARGS | METH_KEYWORDS},
    {"write_to_png", (PyCFunction)Book_write_to_png, METH_VARARGS},
    {"write_to_png_stream", (PyCFunction)Book_write_to_png_stream, METH_VARARGS},
    {NULL}
};

static PyTypeObject Book_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plutoprint.Book",
    .tp_basicsize = sizeof(Book_Object),
    .tp_dealloc = (destructor)Book_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_methods = Book_methods,
    .tp_getset = Book_getset,
    .tp_new = (newfunc)Book_new
};

static PyObject* Book_Create(plutobook_t* book)
{
    Book_Object* book_ob = Object_New(Book_Object, &Book_Type);
    book_ob->book = book;
    book_ob->custom_resource_fetcher = NULL;
    return (PyObject*)book_ob;
}

static struct PyModuleDef module_definition = {
    PyModuleDef_HEAD_INIT,
    "plutoprint",
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

PyMODINIT_FUNC PyInit__plutoprint(void)
{
    if(PyType_Ready(&PageSize_Type) < 0
        || PyType_Ready(&PageMargins_Type) < 0
        || PyType_Ready(&MediaType_Type) < 0
        || PyType_Ready(&PDFMetadata_Type) < 0
        || PyType_Ready(&ImageFormat_Type) < 0
        || PyType_Ready(&Canvas_Type) < 0
        || PyType_Ready(&ImageCanvas_Type) < 0
        || PyType_Ready(&PDFCanvas_Type) < 0
        || PyType_Ready(&ResourceData_Type) < 0
        || PyType_Ready(&ResourceFetcher_Type) < 0
        || PyType_Ready(&Book_Type) < 0) {
        return NULL;
    }

    PyObject* module = PyModule_Create(&module_definition);
    if(module == NULL) {
        return NULL;
    }

    Error_Object = PyErr_NewException("plutoprint.Error", NULL, NULL);

    PyModule_AddStringConstant(module, "__version__", PLUTOPRINT_VERSION_STRING);
    PyModule_AddObject(module, "__version_info__", Py_BuildValue("(iii)", PLUTOPRINT_VERSION_MAJOR, PLUTOPRINT_VERSION_MINOR, PLUTOPRINT_VERSION_MICRO));
    PyModule_AddObject(module, "__build_info__", PyUnicode_FromFormat("%s\nPlutoPrint version: %s\nPython version: %s\n", plutobook_build_info(), PLUTOPRINT_VERSION_STRING, PY_VERSION));

    Py_INCREF(Error_Object);
    PyModule_AddObject(module, "Error", Error_Object);

    Py_INCREF(&PageSize_Type);
    PyModule_AddObject(module, "PageSize", (PyObject*)&PageSize_Type);

    Py_INCREF(&PageMargins_Type);
    PyModule_AddObject(module, "PageMargins", (PyObject*)&PageMargins_Type);

    Py_INCREF(&MediaType_Type);
    PyModule_AddObject(module, "MediaType", (PyObject*)&MediaType_Type);

    Py_INCREF(&PDFMetadata_Type);
    PyModule_AddObject(module, "PDFMetadata", (PyObject*)&PDFMetadata_Type);

    Py_INCREF(&ImageFormat_Type);
    PyModule_AddObject(module, "ImageFormat", (PyObject*)&ImageFormat_Type);

    Py_INCREF(&Canvas_Type);
    PyModule_AddObject(module, "Canvas", (PyObject*)&Canvas_Type);

    Py_INCREF(&ImageCanvas_Type);
    PyModule_AddObject(module, "ImageCanvas", (PyObject*)&ImageCanvas_Type);

    Py_INCREF(&PDFCanvas_Type);
    PyModule_AddObject(module, "PDFCanvas", (PyObject*)&PDFCanvas_Type);

    Py_INCREF(&ResourceData_Type);
    PyModule_AddObject(module, "ResourceData", (PyObject*)&ResourceData_Type);

    Py_INCREF(&ResourceFetcher_Type);
    PyModule_AddObject(module, "ResourceFetcher", (PyObject*)&ResourceFetcher_Type);

    Py_INCREF(&Book_Type);
    PyModule_AddObject(module, "Book", (PyObject*)&Book_Type);

    PyModule_AddObject(module, "default_resource_fetcher", ResourceFetcher_Create());

    PyModule_AddObject(module, "PAGE_SIZE_NONE", PageSize_Create(PLUTOBOOK_PAGE_SIZE_NONE));
    PyModule_AddObject(module, "PAGE_SIZE_LETTER", PageSize_Create(PLUTOBOOK_PAGE_SIZE_LETTER));
    PyModule_AddObject(module, "PAGE_SIZE_LEGAL", PageSize_Create(PLUTOBOOK_PAGE_SIZE_LEGAL));
    PyModule_AddObject(module, "PAGE_SIZE_LEDGER", PageSize_Create(PLUTOBOOK_PAGE_SIZE_LETTER));

    PyModule_AddObject(module, "PAGE_SIZE_A3", PageSize_Create(PLUTOBOOK_PAGE_SIZE_A3));
    PyModule_AddObject(module, "PAGE_SIZE_A4", PageSize_Create(PLUTOBOOK_PAGE_SIZE_A4));
    PyModule_AddObject(module, "PAGE_SIZE_A5", PageSize_Create(PLUTOBOOK_PAGE_SIZE_A5));
    PyModule_AddObject(module, "PAGE_SIZE_B4", PageSize_Create(PLUTOBOOK_PAGE_SIZE_B4));
    PyModule_AddObject(module, "PAGE_SIZE_B5", PageSize_Create(PLUTOBOOK_PAGE_SIZE_B5));

    PyModule_AddObject(module, "PAGE_MARGINS_NONE", PageMargins_Create(PLUTOBOOK_PAGE_MARGINS_NONE));
    PyModule_AddObject(module, "PAGE_MARGINS_NORMAL", PageMargins_Create(PLUTOBOOK_PAGE_MARGINS_NORMAL));
    PyModule_AddObject(module, "PAGE_MARGINS_NARROW", PageMargins_Create(PLUTOBOOK_PAGE_MARGINS_NARROW));
    PyModule_AddObject(module, "PAGE_MARGINS_MODERATE", PageMargins_Create(PLUTOBOOK_PAGE_MARGINS_MODERATE));
    PyModule_AddObject(module, "PAGE_MARGINS_WIDE", PageMargins_Create(PLUTOBOOK_PAGE_MARGINS_WIDE));

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

    PyModule_AddIntConstant(module, "PLUTOBOOK_VERSION", PLUTOBOOK_VERSION);
    PyModule_AddIntConstant(module, "PLUTOBOOK_VERSION_MINOR", PLUTOBOOK_VERSION_MINOR);
    PyModule_AddIntConstant(module, "PLUTOBOOK_VERSION_MICRO", PLUTOBOOK_VERSION_MICRO);
    PyModule_AddIntConstant(module, "PLUTOBOOK_VERSION_MAJOR", PLUTOBOOK_VERSION_MAJOR);
    PyModule_AddStringConstant(module, "PLUTOBOOK_VERSION_STRING", PLUTOBOOK_VERSION_STRING);

    return module;
}
