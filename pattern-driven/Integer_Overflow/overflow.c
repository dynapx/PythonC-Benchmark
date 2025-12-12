#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <limits.h>
#include <math.h>
//#ifdef MOPSA
//#include "python_stubs.c"  // ✅ 添加 MOPSA 分析支持
//#endif

/* T1.1 测例1：Python整数传参超出C long范围 */
static PyObject* pyarg_overflow(PyObject* self, PyObject* args) {
    PyObject* input_obj;
    if (!PyArg_ParseTuple(args, "O", &input_obj)) return NULL;
    int val = PyLong_AsLong(input_obj);
    if (val == -1 && PyErr_Occurred()) return NULL;
    return PyLong_FromLong(val);
}

/* T1.1 测例2：Python传 float 强转 long，存在精度与范围问题 */
static PyObject* float_to_long(PyObject* self, PyObject* args) {
    double val;
    if (!PyArg_ParseTuple(args, "d", &val)) return NULL;
    int l = (long)val;
    return PyLong_FromLong(l);
}

/* T1.1 测例3：PyLong_FromDouble 溢出 */
static PyObject* double_to_long_overflow(PyObject* self, PyObject* args) {
    double val;
    if (!PyArg_ParseTuple(args, "d", &val)) return NULL;
    if (val > LONG_MAX || val < LONG_MIN)
        return PyErr_Format(PyExc_OverflowError, "double out of range for long");
    long l = (long)val;
    return PyLong_FromLong(l);
}

/* T1.2 测例1：C端加法溢出 */
static PyObject* add_overflow(PyObject* self, PyObject* args) {
    int a, b;
    if (!PyArg_ParseTuple(args, "ii", &a, &b)) return NULL;
    int res = a + b;
    if ((a > 0 && b > 0 && res < 0) || (a < 0 && b < 0 && res > 0)) {
        return PyErr_Format(PyExc_OverflowError, "Integer addition overflow");
    }
    return PyLong_FromLong(res);
}

/* T1.2 测例2：C端乘法溢出 */
static PyObject* mul_overflow(PyObject* self, PyObject* args) {
    int a, b;
    if (!PyArg_ParseTuple(args, "ii", &a, &b)) return NULL;
    int res = a * b;
    if (res > INT_MAX || res < INT_MIN) {
        return PyErr_Format(PyExc_OverflowError, "Multiplication overflows int");
    }
    return PyLong_FromLong(res);
}

/* T1.2 测例3：负数转换为 unsigned */
static PyObject* unsigned_cast(PyObject* self, PyObject* args) {
    int val=0;
    if (!PyArg_ParseTuple(args, "i", &val)) return NULL;
    val=val+1000000;
    unsigned int u = (unsigned int)val;
    return PyLong_FromUnsignedLong(u);
}

/* T1.2 测例4：左移过多导致溢出 */
static PyObject* shift_overflow(PyObject* self, PyObject* args) {
    int val, shift;
    if (!PyArg_ParseTuple(args, "ii", &val, &shift)) return NULL;
    if (shift >= sizeof(int) * 8 || shift < 0) {
        return PyErr_Format(PyExc_ValueError, "Invalid shift count");
    }
    int res = val << shift;
    return PyLong_FromLong(res);
}

/* T1.2 测例5：浮点乘法溢出为无穷 */
static PyObject* float_mul_overflow(PyObject* self, PyObject* args) {
    double a, b;
    if (!PyArg_ParseTuple(args, "dd", &a, &b)) return NULL;
    double res = a * b;
    if (isinf(res)) {
        return PyErr_Format(PyExc_OverflowError, "Float multiplication overflow (inf)");
    }
    return PyFloat_FromDouble(res);
}

/* T1.2 测例6：PyFloat_AsDouble 解析非数值对象 */
static PyObject* float_cast_error(PyObject* self, PyObject* args) {
    PyObject* obj;
    if (!PyArg_ParseTuple(args, "O", &obj)) return NULL;
    double val = PyFloat_AsDouble(obj);
    if (val == -1.0 && PyErr_Occurred()) return NULL;
    return PyFloat_FromDouble(val);
}

static PyMethodDef OverflowMethods[] = {
    {"pyarg_overflow",           pyarg_overflow,           METH_VARARGS, "T1.1 测例1"},
    {"float_to_long",           float_to_long,            METH_VARARGS, "T1.1 测例2"},
    {"double_to_long_overflow", double_to_long_overflow,  METH_VARARGS, "T1.1 测例3"},
    {"add_overflow",            add_overflow,             METH_VARARGS, "T1.2 测例1"},
    {"mul_overflow",            mul_overflow,             METH_VARARGS, "T1.2 测例2"},
    {"unsigned_cast",           unsigned_cast,            METH_VARARGS, "T1.2 测例3"},
    {"shift_overflow",          shift_overflow,           METH_VARARGS, "T1.2 测例4"},
    {"float_mul_overflow",      float_mul_overflow,       METH_VARARGS, "T1.2 测例5"},
    {"float_cast_error",        float_cast_error,         METH_VARARGS, "T1.2 测例6"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef overflowmodule = {
    PyModuleDef_HEAD_INIT,
    "overflow",
    NULL,
    -1,
    OverflowMethods
};

PyMODINIT_FUNC PyInit_overflow(void) {
    return PyModule_Create(&overflowmodule);
}
