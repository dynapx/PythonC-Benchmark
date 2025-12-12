import no_null_check
def try_call(func, *args):
    print(f">>> {func.__name__}({', '.join(map(str, args))})")
    try:
        result = func(*args)
        print("Result:", result)
    except Exception as e:
        print("Error:", type(e).__name__, e)
    print("-" * 60)

if __name__ == "__main__":
    try_call(no_null_check.unsafe_parse_args, "not-an-int")          # E2.1-1
    try_call(no_null_check.unsafe_malloc, 0)                          # E2.1-2
    try_call(no_null_check.unsafe_unicode_create)                     # E2.1-3
    try_call(no_null_check.unsafe_list_access)                        # E2.1-4
    try_call(no_null_check.unsafe_import)                             # E2.1-5