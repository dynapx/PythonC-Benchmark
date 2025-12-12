#define PY_SSIZE_T_CLEAN
#include <Python.h>
#ifdef MOPSA
#include "python_stubs.c"  // ✅ 添加 MOPSA 分析支持
#endif

/* T2.1 测例1：格式 "i"，但 Python 传入字符串 */
static PyObject* wrong_format_int(PyObject *self, PyObject *args) {
    int value;
    if (!PyArg_ParseTuple(args, "i", &value)) return NULL;
    return PyLong_FromLong(value * 2);
}

/* T2.1 测例2：格式 "ii"，但只传入一个参数 */
static PyObject* wrong_arg_count(PyObject *self, PyObject *args) {
    int a, b;
    if (!PyArg_ParseTuple(args, "ii", &a, &b)) return NULL;
    return PyLong_FromLong(a + b);
}

/* T2.1 测例3：格式 "s"，但传入整数 */
static PyObject* wrong_string_type(PyObject *self, PyObject *args) {
    const char* s;
    if (!PyArg_ParseTuple(args, "s", &s)) return NULL;
    return PyUnicode_FromFormat("Got: %s", s);
}

/* T2.1 测例4：格式 "O!"，但未提供类型对象 */
static PyObject* wrong_object_type_check(PyObject *self, PyObject *args) {
    PyObject* obj;
    if (!PyArg_ParseTuple(args, "O!", &PyUnicode_Type, &obj)) return NULL;
    return PyObject_Repr(obj);
}

/* T2.1 测例5：格式 "s#", 但 Python 传入非字符串类型 */
static PyObject* wrong_s_size(PyObject *self, PyObject *args) {
    const char *buf;
    Py_ssize_t len;
    if (!PyArg_ParseTuple(args, "s#", &buf, &len)) return NULL;
    return PyLong_FromSsize_t(len);
}

/* T2.1 测例6：格式 "d"，但 Python 传入字符串 */
static PyObject* wrong_float_type(PyObject *self, PyObject *args) {
    double val;
    if (!PyArg_ParseTuple(args, "d", &val)) return NULL;
    return PyFloat_FromDouble(val);
}

/* T2.1 测例7：格式 "i"，但 C 端用 long 接收 */
static PyObject* wrong_c_decl_int(PyObject* self, PyObject* args) {
    long x;  // 应该是 int
    if (!PyArg_ParseTuple(args, "i", &x)) return NULL;
    return PyLong_FromLong(x);
}

/* T2.1 测例8：格式 "d"，但 C 端用 float 接收 */
static PyObject* wrong_c_decl_float(PyObject* self, PyObject* args) {
    float f;  // 应该是 double
    if (!PyArg_ParseTuple(args, "d", &f)) return NULL;
    return PyFloat_FromDouble(f);
}

/* T2.1 测例9：格式 "s"，但用 PyObject* 接收 */
static PyObject* wrong_c_decl_string(PyObject* self, PyObject* args) {
    PyObject* s;  // 应该是 const char*
    if (!PyArg_ParseTuple(args, "s", &s)) return NULL;
    return PyUnicode_FromFormat("Got: %R", s);
}

/* T2.1 测例10：格式 "s#"，但用 char* 和 int 接收 */
static PyObject* wrong_c_decl_s_size(PyObject* self, PyObject* args) {
   // char* buf;
    int len;  // 应该是 Py_ssize_t
    if (!PyArg_ParseTuple(args, "#",&len)) return NULL;
    return PyLong_FromLong(len);
}
/* T2.1 测例11：格式 "s"，但用 int 接收 */
static PyObject* format_type_confusion(PyObject* self, PyObject* args) {
    int x;
    if (!PyArg_ParseTuple(args, "s", &x)) return NULL;  // ❌ char* 写入 int（类型不匹配）
    return PyLong_FromLong(x);  // 🔥 Mopsa 检测未定义行为：int 未合法初始化
}

/* T2.1 测例12：格式 "s"，但用 double 接收 */
static PyObject* format_double_misuse(PyObject* self, PyObject* args) {
    double d;
    if (!PyArg_ParseTuple(args, "s", &d)) return NULL;  // ❌ char* 写入 double（类型不匹配）
    return PyFloat_FromDouble(d * 2.0);  // 🔥 Mopsa 检测：非法使用未定义 double
}
static PyMethodDef Methods[] = {
    {"wrong_format_int", wrong_format_int, METH_VARARGS, "T2.1 测例1"},
    {"wrong_arg_count", wrong_arg_count, METH_VARARGS, "T2.1 测例2"},
    {"wrong_string_type", wrong_string_type, METH_VARARGS, "T2.1 测例3"},
    {"wrong_object_type_check", wrong_object_type_check, METH_VARARGS, "T2.1 测例4"},
    {"wrong_s_size", wrong_s_size, METH_VARARGS, "T2.1 测例5"},
    {"wrong_float_type", wrong_float_type, METH_VARARGS, "T2.1 测例6"},
    {"wrong_c_decl_int", wrong_c_decl_int, METH_VARARGS, "T2.1 测例7"},
    {"wrong_c_decl_float", wrong_c_decl_float, METH_VARARGS, "T2.1 测例8"},
    {"wrong_c_decl_string", wrong_c_decl_string, METH_VARARGS, "T2.1 测例9"},
    {"wrong_c_decl_s_size", wrong_c_decl_s_size, METH_VARARGS, "T2.1 测例10"},
    {"format_type_confusion", format_type_confusion, METH_VARARGS, "T2.1 测例11：int ← s"},
    {"format_double_misuse", format_double_misuse, METH_VARARGS, "T2.1 测例12：double ← s"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "argparse_mismatch",
    NULL,
    -1,
    Methods
};

PyMODINIT_FUNC PyInit_argparse_mismatch(void) {
    return PyModule_Create(&moduledef);
}
