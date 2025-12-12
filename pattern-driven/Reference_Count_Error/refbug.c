#include <Python.h>

/* M1.1 测例1：创建新对象未释放，造成内存泄漏 */
static PyObject* leaky_creation(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, ""))
        return NULL;
    PyObject *num1 = PyLong_FromLong(42);
    Py_INCREF(num1);
    PyObject *num = PyLong_FromLong(420);

    Py_RETURN_NONE;

}

/* M1.1 测例2：多个对象创建后均未释放，造成复合泄漏 */
static PyObject* multi_leak(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, ""))
        return NULL;
    PyObject *a = PyList_New(0);
    PyObject *b = PyDict_New();
     Py_INCREF(a);
    PyObject *c = PyLong_FromLong(123);
    Py_RETURN_NONE;
}

/* M1.1 测例3：循环中创建对象未释放，造成批量泄漏 */
static PyObject* loop_leak(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, ""))
        return NULL;
    for (int i = 0; i < 1000; i++) {
        PyObject *num = PyLong_FromLong(i);
    }
    Py_RETURN_NONE;
}

/* M1.1 测例4：创建列表元素未释放，造成间接泄漏 */
static PyObject* container_leak(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, ""))
        return NULL;
    PyObject *lst = PyList_New(0);
    for (int i = 0; i < 10; i++) {
        PyObject *item = PyUnicode_FromFormat("str%d", i);
        PyList_Append(lst, item);
    }
    Py_RETURN_NONE;
}

/* M1.2 测例1：返回借用引用未增加引用计数，造成悬空引用 */
static PyObject* bad_return_ref(PyObject *self, PyObject *args) {
    PyObject *list;
    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &list))
        return NULL;
    PyObject *item = PyList_GetItem(list, 0);
    return item;
}

/* M1.2 测例2：重复释放引用导致悬空引用或崩溃 */
static PyObject* double_free(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, ""))
        return NULL;
    PyObject *dict = PyDict_New();
    PyObject *key = PyUnicode_FromString("answer");
    PyDict_SetItem(dict, key, PyLong_FromLong(42));
    Py_DECREF(key);
    Py_DECREF(key);  // 第二次释放相同对象
    Py_DECREF(dict);
    Py_RETURN_NONE;
}

/* M1.2 测例3：对象释放后继续使用，造成悬空访问 */
static PyObject* use_after_decref(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, ""))
        return NULL;
    PyObject *s = PyUnicode_FromString("hello");
    Py_DECREF(s);
    Py_ssize_t len = PyUnicode_GetLength(s);  // 使用已释放对象
    return PyLong_FromSsize_t(len);
}

/* M1.2 测例4：引用释放后传入其他 API 使用，触发未定义行为 */
static PyObject* call_after_decref(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, ""))
        return NULL;
    PyObject *s = PyUnicode_FromString("data");
    Py_DECREF(s);
    PyObject *repr = PyObject_Repr(s);  // 在已释放对象上操作
    return repr;
}

/* M1.2 测例5：释放本地对象后赋值给模块全局变量 */
static PyObject* global_assign_after_free(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, ""))
        return NULL;
    static PyObject *global = NULL;
    PyObject *obj = PyUnicode_FromString("oops");
    Py_DECREF(obj);
    global = obj;  // 保存悬空指针
    Py_RETURN_NONE;
}

/* 修复参考：增加引用计数，安全返回对象 */
static PyObject* safe_return_ref(PyObject *self, PyObject *args) {
    PyObject *list;
    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &list))
        return NULL;
    PyObject *item = PyList_GetItem(list, 0);
    Py_INCREF(item);
    return item;
}

static PyMethodDef AdvancedMethods[] = {
    {"leaky_creation", leaky_creation, METH_VARARGS, "M1.1 case 1"},
    {"multi_leak", multi_leak, METH_VARARGS, "M1.1 case 2"},
    {"loop_leak", loop_leak, METH_VARARGS, "M1.1 case 3"},
    {"container_leak", container_leak, METH_VARARGS, "M1.1 case 4"},
    {"bad_return_ref", bad_return_ref, METH_VARARGS, "M1.2 case 1"},
    {"double_free", double_free, METH_VARARGS, "M1.2 case 2"},
    {"use_after_decref", use_after_decref, METH_VARARGS, "M1.2 case 3"},
    {"call_after_decref", call_after_decref, METH_VARARGS, "M1.2 case 4"},
    {"global_assign_after_free", global_assign_after_free, METH_VARARGS, "M1.2 case 5"},
    {"safe_return_ref", safe_return_ref, METH_VARARGS, "Safe reference return"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef advancedmodule = {
    PyModuleDef_HEAD_INIT,
    "refbug",
    NULL,
    -1,
    AdvancedMethods
};

PyMODINIT_FUNC PyInit_refbug(void) {
    return PyModule_Create(&advancedmodule);
}