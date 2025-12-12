#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdlib.h>
#ifdef MOPSA
#include "python_stubs.c"  // ✅ 添加 MOPSA 分析支持
#endif
// M2.2 测例1：Double Free
static PyObject* demo_double_free(PyObject *self, PyObject *args) {
    char *buf = PyMem_Malloc(16);
    if (!buf) return PyErr_NoMemory(), NULL;
    PyMem_Free(buf);
    PyMem_Free(buf);  // 二次释放
    Py_RETURN_NONE;
}

// M2.2 测例2：Use-After-Free
static PyObject* demo_use_after_free(PyObject *self, PyObject *args) {
    char *buf = PyMem_Malloc(16);
    if (!buf) return PyErr_NoMemory(), NULL;
    PyMem_Free(buf);
    buf[0] = 'X';  // 释放后访问
    Py_RETURN_NONE;
}

// M2.2 测例3：Memory Leak
static PyObject* demo_memory_leak(PyObject *self, PyObject *args) {
    char *buf = PyMem_Malloc(16);
    if (!buf) return PyErr_NoMemory(), NULL;
    return Py_BuildValue("s", "leaked");  // buf未释放
}

// M2.2 测例4：Offset Free
static PyObject* demo_offset_free(PyObject *self, PyObject *args) {
    char *buf = PyMem_Malloc(16);
    if (!buf) return PyErr_NoMemory(), NULL;
    PyMem_Free(buf + 4);  // 非起始地址释放
    Py_RETURN_NONE;
}

// M2.2 测例5：Partial Allocation Use
static PyObject* demo_partial_alloc_use(PyObject *self, PyObject *args) {
    char *buf = PyMem_Malloc(4);
    if (!buf) return PyErr_NoMemory(), NULL;
    buf[10] = 'A';  // 越界写入
    PyMem_Free(buf);
    Py_RETURN_NONE;
}

// M2.2 测例6：Double Free via Exception
static PyObject* demo_double_free_exception(PyObject *self, PyObject *args) {
    char *buf = PyMem_Malloc(32);
    if (!buf) return PyErr_NoMemory(), NULL;
    PyMem_Free(buf);
    if (1) return PyErr_Format(PyExc_RuntimeError, "error after free");
    PyMem_Free(buf);  // 实际不可达但存在二次释放
    Py_RETURN_NONE;
}



static PyMethodDef MemErrorsMethods[] = {
    {"double_free",             demo_double_free,             METH_NOARGS, "M2.2 测例1"},
    {"use_after_free",          demo_use_after_free,          METH_NOARGS, "M2.2 测例2"},
    {"memory_leak",             demo_memory_leak,             METH_NOARGS, "M2.2 测例3"},
    {"offset_free",             demo_offset_free,             METH_NOARGS, "M2.2 测例4"},
    {"partial_alloc_use",       demo_partial_alloc_use,       METH_NOARGS, "M2.2 测例5"},
    {"double_free_exception",   demo_double_free_exception,   METH_NOARGS, "M2.2 测例6"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef memerrorsmodule = {
    PyModuleDef_HEAD_INIT,
    "memerrors",
    NULL,
    -1,
    MemErrorsMethods
};

PyMODINIT_FUNC PyInit_memerrors(void) {
    return PyModule_Create(&memerrorsmodule);
}
