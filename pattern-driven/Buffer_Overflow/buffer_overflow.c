#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string.h>
#include <stdlib.h>
#ifdef MOPSA
#include "python_stubs.c"  // ✅ 添加 MOPSA 分析支持
#endif

// M3.1 测例1：strcpy 复制未检查输入长度，导致溢出
static PyObject* unsafe_copy(PyObject* self, PyObject* args) {
    char buffer[16];
    const char* input;
    if (!PyArg_ParseTuple(args, "s", &input)) return NULL;
    strcpy(buffer, input);  // 溢出风险
    return PyUnicode_FromString(buffer);
}

// M3.1 测例2：memcpy 溢出（目标小于输入长度）
static PyObject* unsafe_memcpy(PyObject* self, PyObject* args) {
    char buffer[8];
    const char* input;
    if (!PyArg_ParseTuple(args, "s", &input)) return NULL;
    memcpy(buffer, input, strlen(input));  // 溢出风险
    return PyUnicode_FromString(buffer);
}

// M3.1 测例3：snprintf 长度错误，错误估计
static PyObject* unsafe_snprintf(PyObject* self, PyObject* args) {
    char buffer[10];
    const char* input;
    if (!PyArg_ParseTuple(args, "s", &input)) return NULL;
    snprintf(buffer, strlen(input), "%s", input);  // 格式长度错误
    return PyUnicode_FromString(buffer);
}

// M3.1 测例4：strncat 拼接导致目标缓冲区越界
static PyObject* unsafe_strncat(PyObject* self, PyObject* args) {
    char buffer[12] = "prefix:";
    const char* input;
    if (!PyArg_ParseTuple(args, "s", &input)) return NULL;
    strncat(buffer, input, strlen(input));  // buffer 可能溢出
    return PyUnicode_FromString(buffer);
}

// M3.1 测例5：Free NULL Pointer (合法但测试用途)
static PyObject* demo_free_null(PyObject *self, PyObject *args) {
    char *buf = NULL;
    PyMem_Free(buf);  // 测试NULL释放路径
    Py_RETURN_NONE;
}

// M3.1 测例6：Out-of-bounds Read
static PyObject* demo_out_of_bounds_read(PyObject *self, PyObject *args) {
    char *buf = PyMem_Malloc(8);
    if (!buf) return PyErr_NoMemory(), NULL;
    volatile char val = buf[20];  // 越界读取
    PyMem_Free(buf);
    return PyLong_FromLong(val);
}
static PyMethodDef OverflowMethods[] = {
    {"unsafe_copy",    unsafe_copy,    METH_VARARGS, "M3.1 测例1"},
    {"unsafe_memcpy",  unsafe_memcpy,  METH_VARARGS, "M3.1 测例2"},
    {"unsafe_snprintf",unsafe_snprintf,METH_VARARGS, "M3.1 测例3"},
    {"unsafe_strncat", unsafe_strncat, METH_VARARGS, "M3.1 测例4"},
    {"free_null",               demo_free_null,               METH_NOARGS, "M3.1 测例5"},
    {"out_of_bounds_read",      demo_out_of_bounds_read,      METH_NOARGS, "M3.1 测例6"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef overflowmodule = {
    PyModuleDef_HEAD_INIT,
    "buffer_overflow",
    NULL,
    -1,
    OverflowMethods
};

PyMODINIT_FUNC PyInit_buffer_overflow(void) {
    return PyModule_Create(&overflowmodule);
}
