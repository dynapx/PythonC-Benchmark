import mismatch

def test(func):
    try:
        print(f"[+] Running {func.__name__}")
        func()
    except Exception as e:
        print(f"    Exception: {e}")
    except BaseException as be:
        print(f"    Error: {be}")

if __name__ == "__main__":
    test(mismatch.malloc_pymemfree)
    test(mismatch.pymem_malloc_free)
    test(mismatch.rawmalloc_pymemfree)
    test(mismatch.objmalloc_rawfree)
    test(mismatch.objnew_objdel)      # 正确释放
    test(mismatch.objnew_pymemfree)
    test(mismatch.rawcalloc_free)
    test(mismatch.malloc_objfree)
    test(mismatch.objmalloc_free)
