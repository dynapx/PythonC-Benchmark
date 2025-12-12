import memerrors

def run_test(name, func):
    print(f"[+] Running {name}")
    try:
        result = func()
        print(f"    Result: {result}")
    except Exception as e:
        print(f"    Exception: {e}")
    print("-" * 40)

if __name__ == "__main__":
    tests = [
        ("M2.2 测例1 - double_free", memerrors.double_free),
        ("M2.2 测例2 - use_after_free", memerrors.use_after_free),
        ("M2.2 测例3 - memory_leak", memerrors.memory_leak),
        ("M2.2 测例4 - offset_free", memerrors.offset_free),
        ("M2.2 测例5 - partial_alloc_use", memerrors.partial_alloc_use),
        ("M2.2 测例6 - double_free_exception", memerrors.double_free_exception),
    ]

    for name, func in tests:
        run_test(name, func)
