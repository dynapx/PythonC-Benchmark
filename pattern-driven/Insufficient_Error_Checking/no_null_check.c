#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string.h>
#ifdef MOPSA
#include "python_stubs.c"  // ✅ 添加 MOPSA 分析支持
#endif

// E2.1 测例1：未检查 PyArg_ParseTuple 返回值
static PyObject* unsafe_parse_args(PyObject *self, PyObject *args) {
    int value;
    PyArg_ParseTuple(args, "i", &value);  // 忽略返回值
    return PyLong_FromLong(value * 2);
}

// E2.1 测例2：未检查 PyMem_Malloc 返回值
static PyObject* unsafe_malloc(PyObject *self, PyObject *args) {
    int size;
    if (!PyArg_ParseTuple(args, "i", &size)) return NULL;
    char *buffer = (char*)PyMem_Malloc(size);
    strcpy(buffer, "Hello");  // 若 buffer == NULL 会崩溃
    PyObject *result = PyUnicode_FromString(buffer);
    PyMem_Free(buffer);
    return result;
}

// E2.1 测例3：未检查 PyUnicode_FromString 返回值
static PyObject* unsafe_unicode_create(PyObject *self, PyObject *args) {
    PyObject *s = PyUnicode_FromString("danger");
    // 不检查 s 是否为 NULL
    return PyObject_CallMethod(s, "upper", NULL);  // 若 s 为 NULL，崩溃
}

// E2.1 测例4：未检查 PyList_New 返回值
static PyObject* unsafe_list_access(PyObject *self, PyObject *args) {
    PyObject *lst = PyList_New(3);  // 可能为 NULL
    PyList_SetItem(lst, 0, PyLong_FromLong(1));  // 若 lst 为 NULL → 崩溃
    Py_INCREF(Py_None);
    return Py_None;
}

// E2.1 测例5：未检查 PyImport_ImportModule 返回值
static PyObject* unsafe_import(PyObject *self, PyObject *args) {
    PyObject *mod = PyImport_ImportModule("nonexistent");  // 失败返回 NULL
    PyObject *dict = PyModule_GetDict(mod);  // mod 为 NULL 时崩溃
    Py_INCREF(dict);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef CheckMethods[] = {
    {"unsafe_parse_args",     unsafe_parse_args,     METH_VARARGS, "E2.1 测例1：未检查参数解析"},
    {"unsafe_malloc",         unsafe_malloc,         METH_VARARGS, "E2.1 测例2：未检查内存分配"},
    {"unsafe_unicode_create", unsafe_unicode_create, METH_NOARGS,  "E2.1 测例3：未检查字符串创建"},
    {"unsafe_list_access",    unsafe_list_access,    METH_NOARGS,  "E2.1 测例4：未检查列表创建"},
    {"unsafe_import",         unsafe_import,         METH_NOARGS,  "E2.1 测例5：未检查模块导入"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef nonullcheckmodule = {
    PyModuleDef_HEAD_INIT,
    "no_null_check",
    "E2.1 缺乏接口检查演示",
    -1,
    CheckMethods
};

PyMODINIT_FUNC PyInit_no_null_check(void) {
    return PyModule_Create(&nonullcheckmodule);
}
