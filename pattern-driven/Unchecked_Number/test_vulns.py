import divzero

def safe_call(func, *args):
    try:
        print(f"{func.__name__}")
        result = func(*args)
    except Exception as e:
        print(f"{func.__name__}{args} raised: {type(e).__name__} - {e}")

if __name__ == "__main__":
    print("=== N1.1 除以零测例 ===")

    # 测例 1：整数除法
    #safe_call(divzero.divide_int, 10, 0)

    # 测例 2：模运算
    # safe_call(divzero.mod_int, 10, 0)

    # 测例 3：浮点除法（不会抛异常但会返回 inf）
    safe_call(divzero.divide_float, 10.0, 0.0)

    # 测例 4：PyObject 转 long 后除 0
    # safe_call(divzero.divide_pyobject, 10, 0)

    # 测例 5：表达式为 0 的除法
    safe_call(divzero.divide_by_expr_zero, 123, 5)
