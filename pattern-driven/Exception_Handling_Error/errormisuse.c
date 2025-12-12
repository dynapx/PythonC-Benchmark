#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>

#ifdef MOPSA
#include "python_stubs.c"
#endif

// E1.2 测例1：异常未立即返回 → 被覆盖
static PyObject* overwrite_error(PyObject *self, PyObject *args) {
    PyErr_SetString(PyExc_IOError, "First error set");
    PyErr_SetString(PyExc_ValueError, "Second error overwrites the first");
    return NULL;
}

//E1.2 测例2：异常链覆盖
static PyObject* chain_overwrite_demo(PyObject *self, PyObject *args) {
    PyErr_SetString(PyExc_RuntimeError, "Initial error: something went wrong");
    PyErr_SetString(PyExc_TypeError, "Overwritten error: invalid type encountered");
    return NULL;
}


// E1.1 测例1：异常后继续调用 PyList_Append
static PyObject* error_then_use_list(PyObject *self, PyObject *args) {
    PyErr_SetString(PyExc_ValueError, "Input is invalid");
    // 错误：异常已设置，但继续使用 Python API
    PyObject *list = PyList_New(0);
    if (list) {
        PyList_Append(list, PyUnicode_FromString("should not happen"));
        Py_DECREF(list);
    }
    return NULL;
}


// E1.1 测例2：异常未返回即调用其他 API
static PyObject* unhandled_then_continue(PyObject *self, PyObject *args) {
    PyErr_SetString(PyExc_ZeroDivisionError, "First error");
    PyObject *dummy = PyLong_FromLong(42);  // 不应执行
    Py_XDECREF(dummy);
    return NULL;
}

// E1.1 测例3：异常后仍调用 PyObject_GetAttrString
static PyObject* error_then_get_attr(PyObject *self, PyObject *args) {
    PyErr_SetString(PyExc_KeyError, "Key not found");
    PyObject *mod = PyImport_ImportModule("sys");
    if (mod) {
        PyObject *attr = PyObject_GetAttrString(mod, "version");
        Py_XDECREF(attr);
        Py_DECREF(mod);
    }
    return NULL;
}


// E1.3 测例1：返回 NULL 但未设置异常
static PyObject* return_null_without_error(PyObject *self, PyObject *args) {
    PyErr_Clear();
    return NULL;
}

// E1.3 测例2：设置异常后仍返回对象
static PyObject* set_error_but_return_value(PyObject *self, PyObject *args) {
    PyErr_Clear();
    PyErr_SetString(PyExc_RuntimeError, "Error occurred");
    return Py_BuildValue("s", "should not return");
}

// E1.3 测例3：错误地清除了异常后返回 NULL（返回值与状态不一致）
static PyObject* clear_error_then_return_null(PyObject *self, PyObject *args) {
    PyErr_SetString(PyExc_ValueError, "initial error");
    PyErr_Clear();  // 清除异常
    return NULL;    // 返回 NULL 但无异常 → 错误
}

// 正确示例
static PyObject* correct_usage(PyObject *self, PyObject *args) {
    FILE *f = fopen("nonexist.txt", "r");
    if (!f) {
        PyErr_SetString(PyExc_FileNotFoundError, "file not found");
        return NULL;
    }
    fclose(f);
    Py_RETURN_NONE;
}

// 方法表
static PyMethodDef ErrorMisuseMethods[] = {
    {"overwrite_error", overwrite_error, METH_NOARGS, "E1.2 测例1：异常覆盖"},
    {"chain_overwrite_demo", chain_overwrite_demo, METH_NOARGS, "E1.2 测例2：异常覆盖"},

    {"error_then_use_list", error_then_use_list, METH_NOARGS, "E1.1 测例1：异常后继续调用 PyList_Append"},
    {"unhandled_then_continue", unhandled_then_continue, METH_NOARGS, "E1.1 测例2：未立即返回"},
    {"error_then_get_attr", error_then_get_attr, METH_NOARGS, "E1.1 测例3：异常后仍调用 PyObject_GetAttrString"},


    {"return_null_without_error", return_null_without_error, METH_NOARGS, "E1.3 测例1：返回NULL但无异常"},
    {"set_error_but_return_value", set_error_but_return_value, METH_NOARGS, "E1.3 测例2：设置异常但返回对象"},
    {"clear_error_then_return_null", clear_error_then_return_null, METH_NOARGS, "E1.3 测例3：清除异常后仍返回NULL"},
    {"correct_usage", correct_usage, METH_NOARGS, "对照：正确用法"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef errormisusemodule = {
    PyModuleDef_HEAD_INIT,
    "errormisuse",
    "E1.1/E1.2/E1.3 异常处理错误演示模块",
    -1,
    ErrorMisuseMethods
};

PyMODINIT_FUNC PyInit_errormisuse(void) {
    return PyModule_Create(&errormisusemodule);
}
