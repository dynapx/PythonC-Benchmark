import argparse_mismatch as am

def try_call(func, arg):
    try:
        print(f">>> {func}({arg!r})")
        result = func(arg)
        print("Result:", result)
    except Exception as e:
        print("Error:", type(e), e)
    print("-" * 50)

# T2.1 测例1：传字符串，但期待 int
try_call(am.wrong_format_int, "abc")

# T2.1 测例2：传参不足
try_call(am.wrong_arg_count, 42)

# T2.1 测例3：传 int，但期待字符串
try_call(am.wrong_string_type, 123)

# T2.1 测例4：O! 使用不当
try_call(am.wrong_object_type_check, 123)

# T2.1 测例5：非字符串传入 s#
try_call(am.wrong_s_size, 999)

# T2.1 测例6：传入字符串给 double
try_call(am.wrong_float_type, "abc")

# T2.1 测例7：C 端 long 接收 "i"
try_call(am.wrong_c_decl_int, 123)

# T2.1 测例8：C 端 float 接收 "d"
try_call(am.wrong_c_decl_float, 3.14)

# T2.1 测例9：C 端 PyObject* 接收 "s"
#try_call(am.wrong_c_decl_string, "hello")

# T2.1 测例10：int 接收 Py_ssize_t
# 确保这一行没有特殊字符
#try_call(am.wrong_c_decl_s_size, "abcdefg")  # 第 41 行

# T2.1 测例11：将字符串传入 "s"，但目标变量是 int
#try_call(am.format_double_misuse, "3.14")
# T2.1 测例12：将字符串传入 "s"，但目标变量是 double
#try_call(am.format_double_misuse, "3.14")