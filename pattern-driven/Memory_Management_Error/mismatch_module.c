// mismatch_module.c
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdlib.h>
#ifdef MOPSA
#include "python_stubs.c"  // ✅ 添加 MOPSA 分析支持
#endif
// M2.1 测例1：malloc + PyMem_Free
static PyObject* demo_malloc_pymemfree(PyObject *self, PyObject *args) {
    char *buf = (char*)malloc(32);
    if (!buf) return PyErr_NoMemory(), NULL;
    PyMem_Free(buf);  // 错误释放
    Py_RETURN_NONE;
}

// M2.1 测例2：PyMem_Malloc + free
static PyObject* demo_pymem_malloc_free(PyObject *self, PyObject *args) {
    char *buf = PyMem_Malloc(32);
    if (!buf) return PyErr_NoMemory(), NULL;
    free(buf);  // 错误释放
    Py_RETURN_NONE;
}

// M2.1 测例3：PyMem_RawMalloc + PyMem_Free
static PyObject* demo_rawmalloc_pymemfree(PyObject *self, PyObject *args) {
    void *buf = PyMem_RawMalloc(64);
    if (!buf) return PyErr_NoMemory(), NULL;
    PyMem_Free(buf);  // 错误释放
    Py_RETURN_NONE;
}

// M2.1 测例4：PyObject_Malloc + PyMem_RawFree
static PyObject* demo_objmalloc_rawfree(PyObject *self, PyObject *args) {
    void *buf = PyObject_Malloc(64);
    if (!buf) return PyErr_NoMemory(), NULL;
    PyMem_RawFree(buf);  // 错误释放
    Py_RETURN_NONE;
}

// M2.1 测例5（正确）：PyObject_New + PyObject_Del
static PyObject* demo_objnew_objdel(PyObject *self, PyObject *args) {
    PyObject *obj = PyObject_New(PyObject, &PyBaseObject_Type);
    if (!obj) return PyErr_NoMemory(), NULL;
    PyObject_Del(obj);  // 正确释放
    Py_RETURN_NONE;
}

// M2.1 测例6：PyObject_New + PyMem_Free
static PyObject* demo_objnew_pymemfree(PyObject *self, PyObject *args) {
    PyObject *obj = PyObject_New(PyObject, &PyBaseObject_Type);
    if (!obj) return PyErr_NoMemory(), NULL;
    PyMem_Free(obj);  // 错误释放
    Py_RETURN_NONE;
}

// M2.1 测例7：PyMem_RawCalloc + free
static PyObject* demo_rawcalloc_free(PyObject *self, PyObject *args) {
    void *buf = PyMem_RawCalloc(1, 64);
    if (!buf) return PyErr_NoMemory(), NULL;
    free(buf);  // 错误释放
    Py_RETURN_NONE;
}

// M2.1 测例8：malloc + PyObject_Free
static PyObject* demo_malloc_objfree(PyObject *self, PyObject *args) {
    void *buf = malloc(64);
    if (!buf) return PyErr_NoMemory(), NULL;
    PyObject_Free(buf);  // 错误释放
    Py_RETURN_NONE;
}

// M2.1 测例9：PyObject_Malloc + free
static PyObject* demo_objmalloc_free(PyObject *self, PyObject *args) {
    void *buf = PyObject_Malloc(64);
    if (!buf) return PyErr_NoMemory(), NULL;
    free(buf);  // 错误释放
    Py_RETURN_NONE;
}

static PyMethodDef MismatchMethods[] = {
    {"malloc_pymemfree",      demo_malloc_pymemfree,    METH_NOARGS, "M2.1 malloc + PyMem_Free"},
    {"pymem_malloc_free",     demo_pymem_malloc_free,   METH_NOARGS, "M2.1 PyMem_Malloc + free"},
    {"rawmalloc_pymemfree",   demo_rawmalloc_pymemfree, METH_NOARGS, "M2.1 PyMem_RawMalloc + PyMem_Free"},
    {"objmalloc_rawfree",     demo_objmalloc_rawfree,   METH_NOARGS, "M2.1 PyObject_Malloc + PyMem_RawFree"},
    {"objnew_objdel",         demo_objnew_objdel,       METH_NOARGS, "M2.1 PyObject_New + PyObject_Del (correct)"},
    {"objnew_pymemfree",      demo_objnew_pymemfree,    METH_NOARGS, "M2.1 PyObject_New + PyMem_Free"},
    {"rawcalloc_free",        demo_rawcalloc_free,      METH_NOARGS, "M2.1 PyMem_RawCalloc + free"},
    {"malloc_objfree",        demo_malloc_objfree,      METH_NOARGS, "M2.1 malloc + PyObject_Free"},
    {"objmalloc_free",        demo_objmalloc_free,      METH_NOARGS, "M2.1 PyObject_Malloc + free"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef mismatchmodule = {
    PyModuleDef_HEAD_INIT,
    "mismatch",
    NULL,
    -1,
    MismatchMethods
};

PyMODINIT_FUNC PyInit_mismatch(void) {
    return PyModule_Create(&mismatchmodule);
}
