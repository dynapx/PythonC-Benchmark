#define PY_SSIZE_T_CLEAN
#include <Python.h>

// T2.2 测例1：声明 METH_NOARGS，但试图解析参数（应为 NULL）
static PyObject* wrong_flag_noargs(PyObject *self, PyObject *args) {
    int x;
    if (!PyArg_ParseTuple(args, "i", &x)) return NULL;
    return PyLong_FromLong(x);
}

// T2.2 测例2：声明 METH_VARARGS，但定义中使用了 kwargs 参数
static PyObject* excess_param_function(PyObject *self, PyObject *args, PyObject *kwargs) {
    int a = 0;
    static char *kwlist[] = {"a", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|i", kwlist, &a)) return NULL;
    return PyLong_FromLong(a);
}

// T2.2 测例3：声明 METH_VARARGS，但使用了 PyArg_ParseTupleAndKeywords（错误用法）
static PyObject* parse_kw_without_flag(PyObject *self, PyObject *args, PyObject *kwargs) {
    const char *s = "default";
    static char *kwlist[] = {"s", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|s", kwlist, &s)) return NULL;
    return PyUnicode_FromFormat("Received: %s", s);
}

// T2.2 测例4：声明 METH_VARARGS | METH_KEYWORDS，但函数缺少 kwargs 参数
static PyObject* missing_kwarg_param(PyObject *self, PyObject *args) {
    int val;
    if (!PyArg_ParseTuple(args, "i", &val)) return NULL;
    return PyLong_FromLong(val + 100);
}

// T2.2 测例5：声明 METH_VARARGS，但完全未使用 args 参数
static PyObject* unused_args(PyObject *self, PyObject *args) {
    PyObject *lst = PyList_New(0);
    for (int i = 0; i < 5; i++) {
        PyObject *item = PyLong_FromLong(i);
        PyList_Append(lst, item);
        Py_DECREF(item);
    }
    return lst;
}

// T2.2 测例6：声明 METH_NOARGS，但调用了 PyArg_ParseTuple
static PyObject* parse_args_in_noargs(PyObject *self, PyObject *args) {
    const char *msg;
    if (!PyArg_ParseTuple(args, "s", &msg)) return NULL;
    return PyUnicode_FromFormat("Echo: %s", msg);
}

// T2.2 测例7：声明 VARARGS，但未调用 PyArg_ParseTuple，参数未使用
static PyObject* declared_but_unused_args(PyObject *self, PyObject *args) {
    PyObject *a = PyList_New(0);
    PyObject *b = PyDict_New();
    PyObject *c = PyLong_FromLong(123);
    Py_DECREF(a);
    Py_DECREF(b);
    Py_DECREF(c);
    Py_RETURN_NONE;
}

// T2.2 测例8：声明 METH_O，但未使用 arg 参数
static PyObject* declared_but_unused_o(PyObject *self, PyObject *arg) {
    Py_RETURN_NONE;
}

// T2.2 测例9：声明 VARARGS | KEYWORDS，但 args/kwargs 均未使用
static PyObject* declared_but_unused_kw(PyObject *self, PyObject *args, PyObject *kwargs) {
    Py_RETURN_NONE;
}

// 方法表
static PyMethodDef TypeMismatchMethods[] = {
    {"wrong_flag_noargs", wrong_flag_noargs, METH_NOARGS, "T2.2 测例1: METH_NOARGS 但尝试解析参数"},
    {"excess_param_function", (PyCFunction)(void(*)(void))excess_param_function, METH_VARARGS, "T2.2 测例2: VARARGS 函数却定义了 kwargs"},
    {"parse_kw_without_flag", (PyCFunction)parse_kw_without_flag, METH_VARARGS, "T2.2 测例3: VARARGS 但尝试解析关键字参数"},
    {"missing_kwarg_param", (PyCFunction)(void(*)(void))missing_kwarg_param, METH_VARARGS | METH_KEYWORDS, "T2.2 测例4: KEYWORDS 标志但函数签名缺失"},
    {"unused_args", unused_args, METH_VARARGS, "T2.2 测例5: 参数未使用"},
    {"parse_args_in_noargs", parse_args_in_noargs, METH_NOARGS, "T2.2 测例6: NOARGS 但使用 PyArg_ParseTuple"},
    {"declared_but_unused_args", declared_but_unused_args, METH_VARARGS, "T2.2 测例7: 未使用 args"},
    {"declared_but_unused_o", declared_but_unused_o, METH_O, "T2.2 测例8: METH_O 但未使用参数"},
    {"declared_but_unused_kw", (PyCFunction)(void(*)(void))declared_but_unused_kw, METH_VARARGS | METH_KEYWORDS, "T2.2 测例9: KEYWORDS 函数参数未使用"},
    {NULL, NULL, 0, NULL}
};

// 模块定义
static struct PyModuleDef t22module = {
    PyModuleDef_HEAD_INIT,
    "typemismatch_t22",
    "T2.2: 接口声明与实际调用不匹配",
    -1,
    TypeMismatchMethods
};

PyMODINIT_FUNC PyInit_typemismatch_t22(void) {
    return PyModule_Create(&t22module);
}