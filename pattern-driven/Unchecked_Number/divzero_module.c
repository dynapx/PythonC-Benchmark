#define PY_SSIZE_T_CLEAN
#include <Python.h>

// N1.1 测例1：int 除以 int，未检查除数是否为 0
static PyObject* divide_int(PyObject *self, PyObject *args) {
    int a, b;
    if (!PyArg_ParseTuple(args, "ii", &a, &b)) return NULL;
    int result = a / b;  // 若 b == 0，未定义行为（SIGFPE）
    return PyLong_FromLong(result);
}

// N1.1 测例2：int 模运算，未检查除数是否为 0
static PyObject* mod_int(PyObject *self, PyObject *args) {
    int a, b;
    if (!PyArg_ParseTuple(args, "ii", &a, &b)) return NULL;
    int result = a % b;  // 若 b == 0，未定义行为
    return PyLong_FromLong(result);
}

// N1.1 测例3：double 除以 double，未检查除数是否为 0
static PyObject* divide_float(PyObject *self, PyObject *args) {
    double a, b;
    if (!PyArg_ParseTuple(args, "dd", &a, &b)) return NULL;
    double result = a / b;  // 若 b == 0.0，返回 inf 或 nan，但不抛异常
    return PyFloat_FromDouble(result);
}

// N1.1 测例4：PyLong_AsLong 取参数后执行除法，未检查除数是否为 0
static PyObject* divide_pyobject(PyObject *self, PyObject *args) {
    PyObject *a_obj, *b_obj;
    if (!PyArg_ParseTuple(args, "OO", &a_obj, &b_obj)) return NULL;
    long a = PyLong_AsLong(a_obj);
    long b = PyLong_AsLong(b_obj);
    long result = a / b;
    return PyLong_FromLong(result);
}

// N1.1 测例5：表达式结果为 0 的除法（例如 b = 3 - 3）
static PyObject* divide_by_expr_zero(PyObject *self, PyObject *args) {
    int a, b;
    if (!PyArg_ParseTuple(args, "ii", &a, &b)) return NULL;
    int denom = b - b;  // 结果为 0
    int result = a / denom;
    return PyLong_FromLong(result);
}

static PyMethodDef DivZeroMethods[] = {
    {"divide_int",           divide_int,           METH_VARARGS, "N1.1 测例1：整数除法无检查"},
    {"mod_int",              mod_int,              METH_VARARGS, "N1.1 测例2：模运算无检查"},
    {"divide_float",         divide_float,         METH_VARARGS, "N1.1 测例3：浮点除法无检查"},
    {"divide_pyobject",      divide_pyobject,      METH_VARARGS, "N1.1 测例4：对象除法无检查"},
    {"divide_by_expr_zero",  divide_by_expr_zero,  METH_VARARGS, "N1.1 测例5：表达式结果为零"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef divzeromodule = {
    PyModuleDef_HEAD_INIT,
    "divzero",
    "N1.1 除 0 错误示例",
    -1,
    DivZeroMethods
};

PyMODINIT_FUNC PyInit_divzero(void) {
    return PyModule_Create(&divzeromodule);
}
