import refbug
import sys
import gc


def test(func, *args):
    try:
        print(f"\n[+] Running: {func.__name__}")
        result = func(*args)
        print("    Result:", repr(result))
    except Exception as e:
        print("    Exception:", e)


if __name__ == "__main__":
    # 构造测试参数
    test_list = [1, 2, 3]
    test_dict = {"a": 1}

    # M1.1 内存泄漏相关
    test(refbug.leaky_creation)
    test(refbug.multi_leak)
    test(refbug.loop_leak)
    test(refbug.container_leak)

    # M1.2 悬空引用/过早释放相关
    test(refbug.bad_return_ref, test_list)  # 可能返回悬空对象
    test(refbug.double_free)
    test(refbug.use_after_decref)  # 可能触发崩溃或异常
    test(refbug.call_after_decref)  # 传递悬空对象给API
    test(refbug.global_assign_after_free)  # 模拟全局污染

    # 正确示例（参考）
    test(refbug.safe_return_ref, test_list)

    print("\n[*] 强制垃圾回收")
    gc.collect()
