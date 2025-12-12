
import buffer_overflow

def get_payload():
    return "A" * 64  # 模拟“外部输入”，如文件、网络、用户交互等

def test(func, payload):
    try:
        print(f"[+] Running {func.__name__} with input length = {len(payload)}")
        result = func(payload)
        print(f"    Result: {result}")
    except Exception as e:
        print(f"    Exception: {e}")


def run_test(name, func):
    print(f"[+] Running {name}")
    try:
        result = func()
        print(f"    Result: {result}")
    except Exception as e:
        print(f"    Exception: {e}")
    print("-" * 40)



if __name__ == "__main__":
    input_data = get_payload()

    #test(buffer_overflow.unsafe_copy, input_data)       # M3.1 测例1
    #test(buffer_overflow.unsafe_memcpy, input_data)     # M3.1 测例2
    #test(buffer_overflow.unsafe_snprintf, input_data)   # M3.1 测例3
    test(buffer_overflow.unsafe_strncat, "A" * 64)    # M3.1 测例4

    tests = [
        ("M3.1 测例5 - free_null", buffer_overflow.free_null),
        ("M3.1 测例6 - out_of_bounds_read", buffer_overflow.out_of_bounds_read),
    ]

    for name, func in tests:
        run_test(name, func)
