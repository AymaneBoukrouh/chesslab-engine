#include <Python.h>
#include "fen.h"
#include <string>
#include <sstream>

typedef struct {
    PyObject_HEAD
    FEN* fen;
} PyFENObject;

static int PyFEN_init(PyFENObject* self, PyObject* args, PyObject* kwds) {
    const char* fen_str;
    if (!PyArg_ParseTuple(args, "s", &fen_str)) return -1;

    self->fen = new FEN(fen_str);
    return 0;
}

static void PyFEN_dealloc(PyFENObject* self) {
    delete self->fen;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* PyFEN_toMatrix(PyFENObject* self, PyObject* Py_UNUSED(ignored)) {
    Matrix matrix = self->fen->toMatrix();
    PyObject* py_matrix = PyDict_New();
    if (!py_matrix) return NULL;

    for (const auto& kv : matrix) {
        PyObject* py_value = PyUnicode_FromString(std::string(1, kv.second).c_str());
        PyDict_SetItemString(py_matrix, kv.first.c_str(), py_value);
        Py_DECREF(py_value);
    }

    return py_matrix;
}

static PyMethodDef PyFEN_methods[] = {
    {"toMatrix", (PyCFunction)PyFEN_toMatrix, METH_NOARGS, "Convert FEN to a board matrix"},
    {NULL}
};

static PyTypeObject PyFENType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "chesslab_engine.FEN",       // updated tp_name to reflect chesslab_engine
    sizeof(PyFENObject),         // tp_basicsize
    0,                           // tp_itemsize
    (destructor)PyFEN_dealloc,   // tp_dealloc
    0,                           // tp_vectorcall_offset
    0,                           // tp_getattr
    0,                           // tp_setattr
    0,                           // tp_as_async
    0,                           // tp_repr
    0,                           // tp_as_number
    0,                           // tp_as_sequence
    0,                           // tp_as_mapping
    0,                           // tp_hash 
    0,                           // tp_call
    0,                           // tp_str
    0,                           // tp_getattro
    0,                           // tp_setattro
    0,                           // tp_as_buffer
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, // tp_flags
    "FEN objects",               // tp_doc 
    0,                           // tp_traverse 
    0,                           // tp_clear 
    0,                           // tp_richcompare 
    0,                           // tp_weaklistoffset 
    0,                           // tp_iter 
    0,                           // tp_iternext 
    PyFEN_methods,               // tp_methods 
    0,                           // tp_members 
    0,                           // tp_getset 
    0,                           // tp_base 
    0,                           // tp_dict 
    0,                           // tp_descr_get 
    0,                           // tp_descr_set 
    0,                           // tp_dictoffset 
    (initproc)PyFEN_init,        // tp_init 
    0,                           // tp_alloc 
    PyType_GenericNew,           // tp_new 
};

// module methods
static PyMethodDef module_methods[] = {
    {NULL, NULL, 0, NULL} // Sentinel
};

// module definition
static struct PyModuleDef chesslab_engine_module = {
    PyModuleDef_HEAD_INIT,
    "chesslab_engine",
    "Module for parsing FEN notation in chess",
    -1,
    module_methods
};

// module initialization
PyMODINIT_FUNC PyInit_chesslab_engine(void) {
    PyObject* m;
    if (PyType_Ready(&PyFENType) < 0) return NULL;

    m = PyModule_Create(&chesslab_engine_module);
    if (m == NULL) return NULL;

    Py_INCREF(&PyFENType);
    PyModule_AddObject(m, "FEN", (PyObject*)&PyFENType);
    return m;
}
