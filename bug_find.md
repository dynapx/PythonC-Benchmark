# 漏洞索引文档



## 漏洞 1: cffi仓库 1.17.1版本 调用约定不匹配
- **仓库**: [cffi](https://github.com/python-cffi/cffi)
- **版本**: 1.17.1
- **代码链接**: [cffi/src/c
/_cffi_backend.c#L3418](https://github.com/python-cffi/cffi/blob/main/src/c/_cffi_backend.c#L3418)
- **位置**: cffi/src/c/_cffi_backend.c, line 3418
- **说明**: 函数声明时为[METH_VARARGS](https://github.com/python-cffi/cffi/blob/main/src/c/_cffi_backend.c#L3510)但实际上函数参数没有使用过
- **修复 diff**:
 ```diff
 static PyMethodDef cdata_methods[] = {
    {"__dir__",     cdata_dir,      METH_NOARGS},
    {"__complex__", cdata_complex,  METH_NOARGS},
    {"__enter__",   cdata_enter,    METH_NOARGS},
-   {"__exit__",    cdata_exit,     METH_VARARGS},
+   {"__exit__",    cdata_exit,     METH_NOARGS},
    {NULL,          NULL}           /* sentinel */
    {NULL,          NULL}           /* sentinel */
};
```



## 漏洞 2: coverage仓库 7.8.0版本 调用约定不匹配
- **仓库**: [coverage](https://github.com/nedbat/coveragepy)
- **版本**: 7.8.0
- **代码链接**: [coverage/ctracer/tracer.c#L982](https://github.com/nedbat/coveragepy/releases/tag/7.8.0)
- **说明**:函数CTracer_start声明时为METH_VARARGS但实际上函数参数没有使用过
- **修复 diff**:
```diff
static PyObject *
CTracer_start(CTracer *self, PyObject *args_unused)
{
    PyEval_SetTrace((Py_tracefunc)CTracer_trace, (PyObject*)self);
    self->started = TRUE;
    self->tracing_arcs = self->trace_arcs && PyObject_IsTrue(self->trace_arcs);

    /* start() returns a trace function usable with sys.settrace() */
    Py_INCREF(self);
    return (PyObject *)self;
}
...
static PyMethodDef
CTracer_methods[] = {
-    { "start",      (PyCFunction) CTracer_start,        METH_VARARGS,
-            PyDoc_STR("Start the tracer") },
+    { "start",      (PyCFunction) CTracer_start,        METH_NOARGS,
+            PyDoc_STR("Start the tracer") },
    { "stop",       (PyCFunction) CTracer_stop,         METH_VARARGS,
            PyDoc_STR("Stop the tracer") },

    { "get_stats",  (PyCFunction) CTracer_get_stats,    METH_VARARGS,
            PyDoc_STR("Get statistics about the tracing") },

    { "activity",   (PyCFunction) CTracer_activity,     METH_VARARGS,
            PyDoc_STR("Has there been any activity?") },

    { "reset_activity", (PyCFunction) CTracer_reset_activity, METH_VARARGS,
            PyDoc_STR("Reset the activity flag") },

    { NULL }
};
```



## 漏洞 3: coverage仓库 7.8.0版本 调用约定不匹配
- **仓库**: [coverage](https://github.com/nedbat/coveragepy)
- **版本**: 7.8.0
- **代码链接**: [coverage/ctracer/tracer.c#L993](https://github.com/nedbat/coveragepy/releases/tag/7.8.0)
- **说明**:函数CTracer_stop声明时为METH_VARARGS但实际上函数参数没有使用过
- **修复 diff**:
```diff
static PyObject *
CTracer_stop(CTracer *self, PyObject *args_unused)
{
    if (self->started) {
        /* Set the started flag only. The actual call to
           PyEval_SetTrace(NULL, NULL) is delegated to the callback
           itself to ensure that it called from the right thread.
           */
        self->started = FALSE;
    }

    Py_RETURN_NONE;
}
...
static PyMethodDef
CTracer_methods[] = {
    { "start",      (PyCFunction) CTracer_start,        METH_VARARGS,
            PyDoc_STR("Start the tracer") },

-    { "stop",       (PyCFunction) CTracer_stop,         METH_VARARGS,
-            PyDoc_STR("Stop the tracer") },
+    { "stop",       (PyCFunction) CTracer_stop,         METH_NOARGS,
+            PyDoc_STR("Stop the tracer") },

    { "get_stats",  (PyCFunction) CTracer_get_stats,    METH_VARARGS,
            PyDoc_STR("Get statistics about the tracing") },

    { "activity",   (PyCFunction) CTracer_activity,     METH_VARARGS,
            PyDoc_STR("Has there been any activity?") },

    { "reset_activity", (PyCFunction) CTracer_reset_activity, METH_VARARGS,
            PyDoc_STR("Reset the activity flag") },

    { NULL }
};
```

## 漏洞 4: coverage仓库 7.8.0版本 调用约定不匹配
- **仓库**: [coverage](https://github.com/nedbat/coveragepy)
- **版本**: 7.8.0
- **代码链接**: [coverage/ctracer/tracer.c#L1026](https://github.com/nedbat/coveragepy/releases/tag/7.8.0)
- **说明**:函数CTracer_get_stats声明时为METH_VARARGS但实际上函数参数没有使用过
- **修复 diff**:
```diff
static PyObject *
CTracer_get_stats(CTracer *self, PyObject *args_unused)
{
#if COLLECT_STATS
    return Py_BuildValue(
        "{sI,sI,sI,sI,sI,sI,si,sI,sI,sI}",
        "calls", self->stats.calls,
        "lines", self->stats.lines,
        "returns", self->stats.returns,
        "others", self->stats.others,
        "files", self->stats.files,
        "stack_reallocs", self->stats.stack_reallocs,
        "stack_alloc", self->pdata_stack->alloc,
        "errors", self->stats.errors,
        "pycalls", self->stats.pycalls,
        "start_context_calls", self->stats.start_context_calls
        );
#else
    Py_RETURN_NONE;
#endif /* COLLECT_STATS */
}
...
static PyMethodDef
CTracer_methods[] = {
    { "start",      (PyCFunction) CTracer_start,        METH_VARARGS,
            PyDoc_STR("Start the tracer") },

    { "stop",       (PyCFunction) CTracer_stop,         METH_VARARGS,
            PyDoc_STR("Stop the tracer") },

-    { "get_stats",  (PyCFunction) CTracer_get_stats,    METH_VARARGS,
-            PyDoc_STR("Get statistics about the tracing") },
+    { "get_stats",  (PyCFunction) CTracer_get_stats,    METH_NOARGS,
+            PyDoc_STR("Get statistics about the tracing") },


    { "activity",   (PyCFunction) CTracer_activity,     METH_VARARGS,
            PyDoc_STR("Has there been any activity?") },

    { "reset_activity", (PyCFunction) CTracer_reset_activity, METH_VARARGS,
            PyDoc_STR("Reset the activity flag") },

    { NULL }
};
```

## 漏洞 5: coverage仓库 7.8.0版本 调用约定不匹配
- **仓库**: [coverage](https://github.com/nedbat/coveragepy)
- **版本**: 7.8.0
- **代码链接**: [coverage/ctracer/tracer.c#L1008](https://github.com/nedbat/coveragepy/releases/tag/7.8.0)
- **说明**:函数CTracer_activity声明时为METH_VARARGS但实际上函数参数没有使用过
- **修复 diff**:
```diff
static PyObject *
CTracer_activity(CTracer *self, PyObject *args_unused)
{
    if (self->activity) {
        Py_RETURN_TRUE;
    }
    else {
        Py_RETURN_FALSE;
    }
}
...
static PyMethodDef
CTracer_methods[] = {
    { "start",      (PyCFunction) CTracer_start,        METH_VARARGS,
            PyDoc_STR("Start the tracer") },

    { "stop",       (PyCFunction) CTracer_stop,         METH_VARARGS,
            PyDoc_STR("Stop the tracer") },


    { "get_stats",  (PyCFunction) CTracer_get_stats,    METH_NOARGS,
            PyDoc_STR("Get statistics about the tracing") },


-    { "activity",   (PyCFunction) CTracer_activity,     METH_VARARGS,
-           PyDoc_STR("Has there been any activity?") },

+    { "activity",   (PyCFunction) CTracer_activity,     METH_NOARGS,
+           PyDoc_STR("Has there been any activity?") },

    { "reset_activity", (PyCFunction) CTracer_reset_activity, METH_VARARGS,
            PyDoc_STR("Reset the activity flag") },

    { NULL }
};
```

## 漏洞 6: coverage仓库 7.8.0版本 调用约定不匹配
- **仓库**: [coverage](https://github.com/nedbat/coveragepy)
- **版本**: 7.8.0
- **代码链接**: [coverage/ctracer/tracer.c#L1019](https://github.com/nedbat/coveragepy/releases/tag/7.8.0)
- **说明**:函数CTracer_reset_activity声明时为METH_VARARGS但实际上函数参数没有使用过
- **修复 diff**:
```diff
static PyObject *
CTracer_reset_activity(CTracer *self, PyObject *args_unused)
{
    self->activity = FALSE;
    Py_RETURN_NONE;
}
...
static PyMethodDef
CTracer_methods[] = {
    { "start",      (PyCFunction) CTracer_start,        METH_VARARGS,
            PyDoc_STR("Start the tracer") },

    { "stop",       (PyCFunction) CTracer_stop,         METH_VARARGS,
            PyDoc_STR("Stop the tracer") },


    { "get_stats",  (PyCFunction) CTracer_get_stats,    METH_NOARGS,
            PyDoc_STR("Get statistics about the tracing") },




    { "activity",   (PyCFunction) CTracer_activity,     METH_NOARGS,
           PyDoc_STR("Has there been any activity?") },

-    { "reset_activity", (PyCFunction) CTracer_reset_activity, METH_VARARGS,
-            PyDoc_STR("Reset the activity flag") },

+    { "reset_activity", (PyCFunction) CTracer_reset_activity, METH_NOARGS,
+            PyDoc_STR("Reset the activity flag") },

    { NULL }
};
```

## 漏洞 7: regex仓库 2024.11.6版本 调用约定不匹配
- **仓库**: [regex](https://github.com/mrabarnett/mrab-regex)
- **版本**: 2024.11.6
- **代码链接**: [regex_3/_regex.c#L21009](https://github.com/mrabarnett/mrab-regex/releases/tag/2024.11.6)
- **说明**:函数splitter_deepcopy声明时为METH_O但实际上函数参数没有使用过
- **修复 diff**:
```diff
static PyObject* splitter_deepcopy(SplitterObject* self, PyObject* memo) {
    return make_splitter_copy(self);
}
...
static PyMethodDef splitter_methods[] = {
    {"split", (PyCFunction)splitter_split, METH_NOARGS, splitter_split_doc},
    {"__copy__", (PyCFunction)splitter_copy, METH_NOARGS},
-    {"__deepcopy__", (PyCFunction)splitter_deepcopy, METH_O},
+    {"__deepcopy__", (PyCFunction)splitter_deepcopy, METH_NOARGS},

    {NULL, NULL}
};
```

## 漏洞 8: regex仓库 2024.11.6版本 调用约定不匹配
- **仓库**: [regex](https://github.com/mrabarnett/mrab-regex)
- **版本**: 2024.11.6
- **代码链接**: [regex_3/_regex.c#L19870](https://github.com/mrabarnett/mrab-regex/releases/tag/2024.11.6)
- **说明**:函数match_deepcopy声明时为METH_O但实际上函数参数没有使用过
- **修复 diff**:
```diff
static PyObject* match_deepcopy(MatchObject* self, PyObject* memo) {
    return make_match_copy(self);
}
...
static PyMethodDef match_methods[] = {
    {"group", (PyCFunction)match_group, METH_VARARGS, match_group_doc},
    {"start", (PyCFunction)match_start, METH_VARARGS, match_start_doc},
    {"end", (PyCFunction)match_end, METH_VARARGS, match_end_doc},
    {"span", (PyCFunction)match_span, METH_VARARGS, match_span_doc},
    {"groups", (PyCFunction)match_groups, METH_VARARGS|METH_KEYWORDS,
      match_groups_doc},
    {"groupdict", (PyCFunction)match_groupdict, METH_VARARGS|METH_KEYWORDS,
      match_groupdict_doc},
    {"capturesdict", (PyCFunction)match_capturesdict, METH_NOARGS,
      match_capturesdict_doc},
    {"expand", (PyCFunction)match_expand, METH_O, match_expand_doc},
    {"expandf", (PyCFunction)match_expandf, METH_O, match_expandf_doc},
    {"captures", (PyCFunction)match_captures, METH_VARARGS,
      match_captures_doc},
    {"allcaptures", (PyCFunction)match_allcaptures, METH_NOARGS,
      match_allcaptures_doc},
    {"starts", (PyCFunction)match_starts, METH_VARARGS, match_starts_doc},
    {"ends", (PyCFunction)match_ends, METH_VARARGS, match_ends_doc},
    {"spans", (PyCFunction)match_spans, METH_VARARGS, match_spans_doc},
    {"allspans", (PyCFunction)match_allspans, METH_NOARGS, match_allspans_doc},
    {"detach_string", (PyCFunction)match_detach_string, METH_NOARGS,
      match_detach_string_doc},
    {"__copy__", (PyCFunction)match_copy, METH_NOARGS},
-    {"__deepcopy__", (PyCFunction)match_deepcopy, METH_O},
+    {"__deepcopy__", (PyCFunction)match_deepcopy, METH_NOARGS},
    {"__getitem__", (PyCFunction)match_getitem, METH_O|METH_COEXIST},
#if PY_VERSION_HEX >= 0x03090000
    {"__class_getitem__", (PyCFunction)Py_GenericAlias, METH_O|METH_CLASS,
      PyDoc_STR("See PEP 585")},
#endif
    {NULL, NULL}
};
```

## 漏洞 9: regex仓库 2024.11.6版本 调用约定不匹配
- **仓库**: [regex](https://github.com/mrabarnett/mrab-regex)
- **版本**: 2024.11.6
- **代码链接**: [regex_3/_regex.c#L22221](https://github.com/mrabarnett/mrab-regex/releases/tag/2024.11.6)
- **说明**:函数pattern_deepcopy声明时为METH_O但实际上函数参数没有使用过
- **修复 diff**:
```diff
static PyObject* pattern_deepcopy(PatternObject* self, PyObject* memo) {
    return make_pattern_copy(self);
}
...
static PyMethodDef pattern_methods[] = {
    {"match", (PyCFunction)pattern_match, METH_VARARGS|METH_KEYWORDS,
      pattern_match_doc},
    {"fullmatch", (PyCFunction)pattern_fullmatch, METH_VARARGS|METH_KEYWORDS,
      pattern_fullmatch_doc},
    {"search", (PyCFunction)pattern_search, METH_VARARGS|METH_KEYWORDS,
      pattern_search_doc},
    {"sub", (PyCFunction)pattern_sub, METH_VARARGS|METH_KEYWORDS,
      pattern_sub_doc},
    {"subf", (PyCFunction)pattern_subf, METH_VARARGS|METH_KEYWORDS,
      pattern_subf_doc},
    {"subn", (PyCFunction)pattern_subn, METH_VARARGS|METH_KEYWORDS,
      pattern_subn_doc},
    {"subfn", (PyCFunction)pattern_subfn, METH_VARARGS|METH_KEYWORDS,
      pattern_subfn_doc},
    {"split", (PyCFunction)pattern_split, METH_VARARGS|METH_KEYWORDS,
      pattern_split_doc},
    {"splititer", (PyCFunction)pattern_splititer, METH_VARARGS|METH_KEYWORDS,
      pattern_splititer_doc},
    {"findall", (PyCFunction)pattern_findall, METH_VARARGS|METH_KEYWORDS,
      pattern_findall_doc},
    {"finditer", (PyCFunction)pattern_finditer, METH_VARARGS|METH_KEYWORDS,
      pattern_finditer_doc},
    {"scanner", (PyCFunction)pattern_scanner, METH_VARARGS|METH_KEYWORDS,
      pattern_scanner_doc},
    {"__copy__", (PyCFunction)pattern_copy, METH_NOARGS},
-    {"__deepcopy__", (PyCFunction)pattern_deepcopy, METH_O},
+    {"__deepcopy__", (PyCFunction)pattern_deepcopy, METH_NOARGS},
    {"__sizeof__", (PyCFunction)pattern_sizeof, METH_NOARGS|METH_COEXIST},
#if PY_VERSION_HEX >= 0x03090000
    {"__class_getitem__", (PyCFunction)Py_GenericAlias, METH_O|METH_CLASS,
      PyDoc_STR("See PEP 585")},
#endif
    {NULL, NULL}
};
```

## 漏洞 10: regex仓库 2024.11.6版本 调用约定不匹配
- **仓库**: [regex](https://github.com/mrabarnett/mrab-regex)
- **版本**: 2024.11.6
- **代码链接**: [regex_3/_regex.c#L20706](https://github.com/mrabarnett/mrab-regex/releases/tag/2024.11.6)
- **说明**:函数scanner_deepcopy声明时为METH_O但实际上函数参数没有使用过
- **修复 diff**:
```diff
static PyObject* scanner_deepcopy(ScannerObject* self, PyObject* memo) {
    return make_scanner_copy(self);
}
...
static PyMethodDef scanner_methods[] = {
    {"match", (PyCFunction)scanner_match, METH_NOARGS, scanner_match_doc},
    {"search", (PyCFunction)scanner_search, METH_NOARGS, scanner_search_doc},
    {"__copy__", (PyCFunction)scanner_copy, METH_NOARGS},
-    {"__deepcopy__", (PyCFunction)scanner_deepcopy, METH_O},
+    {"__deepcopy__", (PyCFunction)scanner_deepcopy, METH_NOARGS},
    {NULL, NULL}
};
```

## 漏洞 11: regex仓库 2024.11.6版本 调用约定不匹配
- **仓库**: [regex](https://github.com/mrabarnett/mrab-regex)
- **版本**: 2024.11.6
- **代码链接**: [regex_3/_regex.c#L25816](https://github.com/mrabarnett/mrab-regex/releases/tag/2024.11.6)
- **说明**:函数get_properties声明时为METH_VARARGS但实际上函数参数没有使用过
- **修复 diff**:
```diff
static PyObject* get_properties(PyObject* self_, PyObject* args) {
    Py_INCREF(property_dict);

    return property_dict;
}
...
static PyMethodDef _functions[] = {
    {"compile", (PyCFunction)re_compile, METH_VARARGS},
    {"get_code_size", (PyCFunction)get_code_size, METH_NOARGS},
-    {"get_properties", (PyCFunction)get_properties, METH_VARARGS},
+    {"get_properties", (PyCFunction)get_properties, METH_NOARGS},
    {"fold_case", (PyCFunction)fold_case, METH_VARARGS},
    {"get_expand_on_folding", (PyCFunction)get_expand_on_folding, METH_NOARGS},
    {"has_property_value", (PyCFunction)has_property_value, METH_VARARGS},
    {"get_all_cases", (PyCFunction)get_all_cases, METH_VARARGS},
    {NULL, NULL}
};
```

## 漏洞 12: numpy仓库 2.2.5版本 调用约定不匹配
- **仓库**: [numpy](https://github.com/numpy/numpy)
- **版本**: 2.2.5
- **代码链接**: [numpy/linalg/lapack_litemodule.c#L351](https://github.com/numpy/numpy/releases/tag/v2.2.5)
- **说明**:函数lapack_lite_xerbla声明时为METH_VARARGS但实际上函数参数没有使用过
- **修复 diff**:
```diff
static PyObject *
lapack_lite_xerbla(PyObject *NPY_UNUSED(self), PyObject *args)
{
    fortran_int info = -1;

    NPY_BEGIN_THREADS_DEF;
    NPY_BEGIN_THREADS;
    FNAME(xerbla)("test", &info);
    NPY_END_THREADS;

    if (PyErr_Occurred()) {
        return NULL;
    }
    Py_RETURN_NONE;
}
...
#define STR(x) #x
#define lameth(name) {STR(name), lapack_lite_##name, METH_VARARGS, NULL}
static struct PyMethodDef lapack_lite_module_methods[] = {
    lameth(dgelsd),
    lameth(dgeqrf),
    lameth(dorgqr),
    lameth(zgelsd),
    lameth(zgeqrf),
    lameth(zungqr),
-   lameth(xerbla),
+   {xerbla,lapack_lite_xerbla, METH_NOARGS, NULL}
    { NULL,NULL,0, NULL}
};
```

## 漏洞 13: numpy仓库 2.2.5版本 调用约定不匹配
- **仓库**: [numpy](https://github.com/numpy/numpy)
- **版本**: 2.2.5
- **代码链接**: [numpy/_core/src/multiarray/nditer_pywrap.c#L2350](https://github.com/numpy/numpy/releases/tag/v2.2.5)
- **说明**:函数npyiter_exit声明时为METH_VARARGS但实际上函数参数没有使用过
- **修复 diff**:
```diff
static PyObject *
npyiter_exit(NewNpyArrayIterObject *self, PyObject *NPY_UNUSED(args))
{
    /* even if called via exception handling, writeback any data */
    return npyiter_close(self, NULL);
}
...
static PyMethodDef npyiter_methods[] = {
    {"reset",
        (PyCFunction)npyiter_reset,
        METH_NOARGS, NULL},
    {"copy",
        (PyCFunction)npyiter_copy,
        METH_NOARGS, NULL},
    {"__copy__",
        (PyCFunction)npyiter_copy,
        METH_NOARGS, NULL},
    {"iternext",
        (PyCFunction)npyiter_iternext,
        METH_NOARGS, NULL},
    {"remove_axis",
        (PyCFunction)npyiter_remove_axis,
        METH_VARARGS, NULL},
    {"remove_multi_index",
        (PyCFunction)npyiter_remove_multi_index,
        METH_NOARGS, NULL},
    {"enable_external_loop",
        (PyCFunction)npyiter_enable_external_loop,
        METH_NOARGS, NULL},
    {"debug_print",
        (PyCFunction)npyiter_debug_print,
        METH_NOARGS, NULL},
    {"__enter__", (PyCFunction)npyiter_enter,
         METH_NOARGS,  NULL},
-   {"__exit__",  (PyCFunction)npyiter_exit,
-        METH_VARARGS, NULL},
+   {"__exit__",  (PyCFunction)npyiter_exit,
+        METH_NOARGS, NULL},
    {"close",  (PyCFunction)npyiter_close,
         METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL},
};
```

## 漏洞 14: pillow仓库 11.2.1版本 调用约定不匹配
- **仓库**: [pillow](https://github.com/python-pillow/Pillow/releases/tag/11.2.1)
- **版本**: 11.2.1
- **代码链接**: [pillow/src/_imaging.c#L1102](https://github.com/python-pillow/Pillow/releases/tag/11.2.1)
- **说明**:函数_copy声明时为METH_VARARGS但实际上函数参数没有使用过
- **修复 diff**:
```diff
static PyObject *
_copy(ImagingObject *self, PyObject *args) {
    return PyImagingNew(ImagingCopy(self->image));
}
...
static struct PyMethodDef methods[] = {

    /* Put commonly used methods first */
    {"getpixel", (PyCFunction)_getpixel, METH_VARARGS},
    {"putpixel", (PyCFunction)_putpixel, METH_VARARGS},

    {"pixel_access", (PyCFunction)pixel_access_new, METH_VARARGS},

    /* Standard processing methods (Image) */
    {"color_lut_3d", (PyCFunction)_color_lut_3d, METH_VARARGS},
    {"convert", (PyCFunction)_convert, METH_VARARGS},
    {"convert2", (PyCFunction)_convert2, METH_VARARGS},
    {"convert_matrix", (PyCFunction)_convert_matrix, METH_VARARGS},
    {"convert_transparent", (PyCFunction)_convert_transparent, METH_VARARGS},
-    {"copy", (PyCFunction)_copy, METH_VARARGS},
+    {"copy", (PyCFunction)_copy, METH_NOARGS},
    {"crop", (PyCFunction)_crop, METH_VARARGS},
    {"expand", (PyCFunction)_expand_image, METH_VARARGS},
    {"filter", (PyCFunction)_filter, METH_VARARGS},
    {"histogram", (PyCFunction)_histogram, METH_VARARGS},
    ...

    {NULL, NULL} /* sentinel */
};
```

## 漏洞 15: pillow仓库 11.2.1版本 调用约定不匹配
- **仓库**: [pillow](https://github.com/python-pillow/Pillow/releases/tag/11.2.1)
- **版本**: 11.2.1
- **代码链接**: [pillow/src/_imaging.c#L264](https://github.com/python-pillow/Pillow/releases/tag/11.2.1)
- **说明**:函数ExportArrowSchemaPyCapsule声明时为METH_VARARGS但实际上函数参数表没有这个参数
- **修复 diff**:
```diff
PyObject *
ExportArrowSchemaPyCapsule(ImagingObject *self) {
    struct ArrowSchema *schema =
        (struct ArrowSchema *)calloc(1, sizeof(struct ArrowSchema));
    int err = export_imaging_schema(self->image, schema);
    if (err == 0) {
        return PyCapsule_New(schema, "arrow_schema", ReleaseArrowSchemaPyCapsule);
    }
    free(schema);
    return ArrowError(err);
}
...
static struct PyMethodDef methods[] = {

    /* Put commonly used methods first */
    {"getpixel", (PyCFunction)_getpixel, METH_VARARGS},
    {"putpixel", (PyCFunction)_putpixel, METH_VARARGS},

    {"pixel_access", (PyCFunction)pixel_access_new, METH_VARARGS},

    /* Standard processing methods (Image) */
    {"color_lut_3d", (PyCFunction)_color_lut_3d, METH_VARARGS},
    {"convert", (PyCFunction)_convert, METH_VARARGS},
    {"convert2", (PyCFunction)_convert2, METH_VARARGS},
    {"convert_matrix", (PyCFunction)_convert_matrix, METH_VARARGS},
    {"convert_transparent", (PyCFunction)_convert_transparent, METH_VARARGS},
    {"copy", (PyCFunction)_copy, METH_VARARGS},
    {"crop", (PyCFunction)_crop, METH_VARARGS},
...

    /* Misc. */
    {"save_ppm", (PyCFunction)_save_ppm, METH_VARARGS},

    /* arrow */
-   {"__arrow_c_schema__", (PyCFunction)ExportArrowSchemaPyCapsule, METH_VARARGS},
+   {"__arrow_c_schema__", (PyCFunction)ExportArrowSchemaPyCapsule, METH_NOARGS},
    {"__arrow_c_array__", (PyCFunction)ExportArrowArrayPyCapsule, METH_VARARGS},

    {NULL, NULL} /* sentinel */
};
```

## 漏洞 16: pillow仓库 11.2.1版本 调用约定不匹配
- **仓库**: [pillow](https://github.com/python-pillow/Pillow/releases/tag/11.2.1)
- **版本**: 11.2.1
- **代码链接**: [pillow/src/_imaging.c#L4094](https://github.com/python-pillow/Pillow/releases/tag/11.2.1)
- **说明**:函数_get_use_block_allocator声明时为METH_VARARGS但实际上函数参数没有使用过
- **修复 diff**:
```diff
static PyObject *
_get_use_block_allocator(PyObject *self, PyObject *args) {
    return PyLong_FromLong(ImagingDefaultArena.use_block_allocator);
}
...
static PyMethodDef functions[] = {

    /* Object factories */
    {"alpha_composite", (PyCFunction)_alpha_composite, METH_VARARGS},
    {"blend", (PyCFunction)_blend, METH_VARARGS},
    {"fill", (PyCFunction)_fill, METH_VARARGS},
    {"new", (PyCFunction)_new, METH_VARARGS},
    {"new_block", (PyCFunction)_new_block, METH_VARARGS},
    {"new_arrow", (PyCFunction)_new_arrow, METH_VARARGS},
    {"merge", (PyCFunction)_merge, METH_VARARGS},

    ...
    /* Resource management */
    {"get_stats", (PyCFunction)_get_stats, METH_VARARGS},
    {"reset_stats", (PyCFunction)_reset_stats, METH_VARARGS},
    {"get_alignment", (PyCFunction)_get_alignment, METH_VARARGS},
    {"get_block_size", (PyCFunction)_get_block_size, METH_VARARGS},
    {"get_blocks_max", (PyCFunction)_get_blocks_max, METH_VARARGS},
-   {"get_use_block_allocator", (PyCFunction)_get_use_block_allocator, METH_VARARGS},
+   {"get_use_block_allocator", (PyCFunction)_get_use_block_allocator, METH_NOARGS},
    {"set_alignment", (PyCFunction)_set_alignment, METH_VARARGS},
    {"set_block_size", (PyCFunction)_set_block_size, METH_VARARGS},
    {"set_blocks_max", (PyCFunction)_set_blocks_max, METH_VARARGS},
    {"set_use_block_allocator", (PyCFunction)_set_use_block_allocator, METH_VARARGS},
    {"clear_cache", (PyCFunction)_clear_cache, METH_VARARGS},

    {NULL, NULL} /* sentinel */
};
```

## 漏洞 17: pillow仓库 11.2.1版本 调用约定不匹配
- **仓库**: [pillow](https://github.com/python-pillow/Pillow/releases/tag/11.2.1)
- **版本**: 11.2.1
- **代码链接**: [pillow/src/_imaging.c#L286](https://github.com/python-pillow/Pillow/releases/tag/11.2.1)
- **说明**:函数ExportArrowArrayPyCapsule声明时为METH_VARARGS但实际上函数参数表没有这个参数
- **修复 diff**:
```diff
PyObject *
ExportArrowArrayPyCapsule(ImagingObject *self) {
    struct ArrowArray *array =
        (struct ArrowArray *)calloc(1, sizeof(struct ArrowArray));
    int err = export_imaging_array(self->image, array);
    if (err == 0) {
        return PyCapsule_New(array, "arrow_array", ReleaseArrowArrayPyCapsule);
    }
    free(array);
    return ArrowError(err);
}
...
static struct PyMethodDef methods[] = {

    /* Put commonly used methods first */
    {"getpixel", (PyCFunction)_getpixel, METH_VARARGS},
    {"putpixel", (PyCFunction)_putpixel, METH_VARARGS},

    {"pixel_access", (PyCFunction)pixel_access_new, METH_VARARGS},
    ...
    /* arrow */
    {"__arrow_c_schema__", (PyCFunction)ExportArrowSchemaPyCapsule, METH_VARARGS},
-   {"__arrow_c_array__", (PyCFunction)ExportArrowArrayPyCapsule, METH_VARARGS},
+   {"__arrow_c_array__", (PyCFunction)ExportArrowArrayPyCapsule, METH_NOARGS},
    {NULL, NULL} /* sentinel */
};
```

## 漏洞 18: pillow仓库 11.2.1版本 调用约定不匹配
- **仓库**: [pillow](https://github.com/python-pillow/Pillow/releases/tag/11.2.1)
- **版本**: 11.2.1
- **代码链接**: [pillow/src/decode.c#L143](https://github.com/python-pillow/Pillow/releases/tag/11.2.1)
- **说明**:函数_decode_cleanup声明时为METH_VARARGS但实际上但实际上函数参数没有使用过
- **修复 diff**:
```diff
static PyObject *
_decode_cleanup(ImagingDecoderObject *decoder, PyObject *args) {
    int status = 0;

    if (decoder->cleanup) {
        status = decoder->cleanup(&decoder->state);
    }

    return Py_BuildValue("i", status);
}
...
static struct PyMethodDef methods[] = {
    {"decode", (PyCFunction)_decode, METH_VARARGS},
-   {"cleanup", (PyCFunction)_decode_cleanup, METH_VARARGS},
+   {"cleanup", (PyCFunction)_decode_cleanup, METH_NOARGS},
    {"setimage", (PyCFunction)_setimage, METH_VARARGS},
    {"setfd", (PyCFunction)_setfd, METH_VARARGS},
    {NULL, NULL} /* sentinel */
};
```

## 漏洞 19: coverage仓库 7.8.0版本 格式化字符串不匹配
- **仓库**: [coverage](https://github.com/nedbat/coveragepy)
- **版本**: 7.8.0
- **代码链接**: [coverage/ctracer/tracer.c#L922](https://github.com/nedbat/coveragepy/releases/tag/7.8.0)
- **说明**:函数CTracer_call在解析参数时应该有六个参数，但实际只有五个参数
- **修复 diff**:
```diff
static PyObject *
CTracer_call(CTracer *self, PyObject *args, PyObject *kwds)
{
    PyFrameObject *frame;
    PyObject *what_str;
    PyObject *arg;
    int what;
    PyObject *ret = NULL;
    PyObject * ascii = NULL;
+   int arg_value;
    #if DO_NOTHING
    CRASH
    #endif

    static char *what_names[] = {
        "call", "exception", "line", "return",
        "c_call", "c_exception", "c_return",
        NULL
        };

    static char *kwlist[] = {"frame", "event", "arg", NULL};

-    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!O!O|i:Tracer_call", kwlist,
-            &PyFrame_Type, &frame, &PyUnicode_Type, &what_str, &arg)) {
-       goto done;
-    }

+    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!O!O|i:Tracer_call", kwlist,
+            &PyFrame_Type, &frame, &PyUnicode_Type, &what_str, &arg，&arg_value)) {
+       goto done;
+    }

    /* In Python, the what argument is a string, we need to find an int
       for the C function. */
    for (what = 0; what_names[what]; what++) {
        int should_break;
        ascii = PyUnicode_AsASCIIString(what_str);
        should_break = !strcmp(PyBytes_AS_STRING(ascii), what_names[what]);
        Py_DECREF(ascii);
        if (should_break) {
            break;
        }
    }

    #if WHAT_LOG
    ascii = PyUnicode_AsASCIIString(MyFrame_BorrowCode(frame)->co_filename);
    printf("pytrace: %s @ %s %d\n", what_sym[what], PyBytes_AS_STRING(ascii), PyFrame_GetLineNumber(frame));
    Py_DECREF(ascii);
    #endif

    /* Invoke the C function, and return ourselves. */
    if (CTracer_trace(self, frame, what, arg) == RET_OK) {
        Py_INCREF(self);
        ret = (PyObject *)self;
    }

    /* For better speed, install ourselves the C way so that future calls go
       directly to CTracer_trace, without this intermediate function.

       Only do this if this is a CALL event, since new trace functions only
       take effect then.  If we don't condition it on CALL, then we'll clobber
       the new trace function before it has a chance to get called.  To
       understand why, there are three internal values to track: frame.f_trace,
       c_tracefunc, and c_traceobj.  They are explained here:
       https://nedbatchelder.com/text/trace-function.html

       Without the conditional on PyTrace_CALL, this is what happens:

            def func():                 #   f_trace         c_tracefunc     c_traceobj
                                        #   --------------  --------------  --------------
                                        #   CTracer         CTracer.trace   CTracer
                sys.settrace(my_func)
                                        #   CTracer         trampoline      my_func
                        # Now Python calls trampoline(CTracer), which calls this function
                        # which calls PyEval_SetTrace below, setting us as the tracer again:
                                        #   CTracer         CTracer.trace   CTracer
                        # and it's as if the settrace never happened.
        */
    if (what == PyTrace_CALL) {
        PyEval_SetTrace((Py_tracefunc)CTracer_trace, (PyObject*)self);
    }

done:
    return ret;
}
```


## 漏洞 20: msgpack仓库 1.1.0版本 对象过早释放
- **仓库**: [msgpack](https://github.com/msgpack/msgpack-python/)
- **版本**: 1.1.0
- **代码链接**: [msgpack/_cmsgpack.c#L12104](https://github.com/msgpack/msgpack-python/releases/tag/v1.1.0)
- **说明**:函数__pyx_f_7msgpack_9_cmsgpack_get_data_from_buffer中的变量pyx_v_contiguous引用计数在任意分支在__Pyx_XDECREF()前均为0，无需再次释放
- **修复 diff**:
```diff
static CYTHON_INLINE int __pyx_f_7msgpack_9_cmsgpack_get_data_from_buffer(PyObject *__pyx_v_obj, Py_buffer *__pyx_v_view, char **__pyx_v_buf, Py_ssize_t *__pyx_v_buffer_len) {
  PyObject *__pyx_v_contiguous = 0;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  Py_ssize_t __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("get_data_from_buffer", 1);

  __pyx_t_1 = PyObject_GetBuffer(__pyx_v_obj, __pyx_v_view, PyBUF_FULL_RO); if (unlikely(__pyx_t_1 == ((int)-1))) __PYX_ERR(1, 125, __pyx_L1_error)
  __pyx_t_2 = (__pyx_t_1 == -1L);
  if (unlikely(__pyx_t_2)) {

    __Pyx_ReraiseException(); __PYX_ERR(1, 126, __pyx_L1_error)

  }

  __pyx_t_2 = (__pyx_v_view->itemsize != 1);
  if (unlikely(__pyx_t_2)) {
    PyBuffer_Release(__pyx_v_view);
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_BufferError, __pyx_tuple__25, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 129, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_Raise(__pyx_t_3, 0, 0, 0);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __PYX_ERR(1, 129, __pyx_L1_error)
  __pyx_t_2 = (PyBuffer_IsContiguous(__pyx_v_view, 'A') == 0);
  if (__pyx_t_2) {
    PyBuffer_Release(__pyx_v_view);
    __pyx_t_3 = PyMemoryView_GetContiguous(__pyx_v_obj, PyBUF_READ, 'C'); if (unlikely(!__pyx_t_3)) __PYX_ERR(1, 133, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_v_contiguous = __pyx_t_3;
    __pyx_t_3 = 0;

    __pyx_t_1 = PyObject_GetBuffer(__pyx_v_contiguous, __pyx_v_view, PyBUF_SIMPLE); if (unlikely(__pyx_t_1 == ((int)-1))) __PYX_ERR(1, 134, __pyx_L1_error)
    Py_DECREF(__pyx_v_contiguous);
  }

  __pyx_t_4 = __pyx_v_view->len;
  (__pyx_v_buffer_len[0]) = __pyx_t_4;

  (__pyx_v_buf[0]) = ((char *)__pyx_v_view->buf);

  __pyx_r = 1;
  goto __pyx_L0;
  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("msgpack._cmsgpack.get_data_from_buffer", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
- __Pyx_XDECREF(__pyx_v_contiguous);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
```

## 漏洞 21: lxml仓库 5.4.0版本 对象过早释放
- **仓库**: [lxml](https://github.com/lxml/lxml)
- **版本**: 5.4.0
- **代码链接**: [lxml//src/lxml/etree.c#L206313,L48435](https://github.com/lxml/lxml/releases/tag/lxml-5.4.0)
- **说明**:函数__pyx_f_4lxml_5etree__forwardXPathError中的__pyx_t_3被释放后__pyx_v_error.message变悬空指针,在__pyx_f_4lxml_5etree_9_LogEntry__setError Line 48435中访问该指针就会出现释放后使用的情况
- **修复 diff**:
```diff
// 在 __pyx_f_4lxml_5etree__forwardXPathError 函数中：
      __pyx_t_3 = __Pyx_GetItemInt_Tuple(__pyx_v_4lxml_5etree_LIBXML2_XPATH_ERROR_MESSAGES, __pyx_v_xpath_code, int, 1, __Pyx_PyInt_From_int, 0, 1, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(11, 405, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_v_error.message = PyBytes_AS_STRING(__pyx_t_3);
-     __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0
+     __pyx_t_3 = 0

// 在 __pyx_f_4lxml_5etree_9_LogEntry__setError 函数中
 __pyx_t_3 = ((__pyx_v_error->message[0]) == '\x00');
  if (!__pyx_t_3) {
  } else {
    __pyx_t_2 = __pyx_t_3;
    goto __pyx_L4_bool_binop_done;
  }

```
