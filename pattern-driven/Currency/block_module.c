#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <unistd.h>
#include <time.h>

// C1.1 测例1：阻塞 sleep，未释放 GIL
static PyObject* blocking_io(PyObject *self, PyObject *args) {
    long seconds;
    if (!PyArg_ParseTuple(args, "l", &seconds))
        return NULL;
    sleep(seconds);  // 会阻塞整个解释器
    Py_RETURN_NONE;
}

// C1.1 测例2：阻塞 sleep，释放 GIL
static PyObject* gil_safe_sleep(PyObject *self, PyObject *args) {
    long seconds;
    if (!PyArg_ParseTuple(args, "l", &seconds))
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    sleep(seconds);
    Py_END_ALLOW_THREADS

    Py_RETURN_NONE;
}

// C1.1 测例3：模拟慢速 I/O 读取，未释放 GIL
static PyObject* simulate_io(PyObject *self, PyObject *args) {
    int loops;
    if (!PyArg_ParseTuple(args, "i", &loops)) return NULL;

    for (int i = 0; i < loops; i++) {
        usleep(100000);  // 0.1秒，阻塞GIL
    }
    Py_RETURN_NONE;
}

// C1.1 测例4：高强度计算未释放 GIL，导致多线程性能下降
static PyObject* cpu_bound(PyObject *self, PyObject *args) {
    long count = 100000000;
    if (!PyArg_ParseTuple(args, "|l", &count)) return NULL;

    volatile long x = 0;
    for (long i = 0; i < count; i++) {
        x += i % 7;
    }
    return PyLong_FromLong(x);
}

static PyMethodDef BlockMethods[] = {
    {"blocking_io",     blocking_io,     METH_VARARGS, "C1.1 测例1：sleep 阻塞未释放 GIL"},
    {"gil_safe_sleep",  gil_safe_sleep,  METH_VARARGS, "C1.1 测例2：sleep 释放 GIL"},
    {"simulate_io",     simulate_io,     METH_VARARGS, "C1.1 测例3：模拟 I/O 未释放 GIL"},
    {"cpu_bound",       cpu_bound,       METH_VARARGS, "C1.1 测例4：计算密集任务无 GIL 管理"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef blockmodule = {
    PyModuleDef_HEAD_INIT,
    "blockio",
    "GIL 临界区阻塞示例",
    -1,
    BlockMethods
};

PyMODINIT_FUNC PyInit_blockio(void) {
    return PyModule_Create(&blockmodule);
}
