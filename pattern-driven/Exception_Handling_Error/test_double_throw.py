import errormisuse
def try_call(func):
    #print(f">>> {func}()")
    try:
        result = func()
        print("Result:", result)
    except Exception as e:
        print("Error:", type(e), e)
    print("-" * 50)

if __name__ == "__main__":
    try_call(errormisuse.overwrite_error)
    try_call(errormisuse.chain_overwrite_demo)


    try_call(errormisuse.error_then_use_list)
    try_call(errormisuse.unhandled_then_continue)
    try_call(errormisuse.error_then_get_attr)

    try_call(errormisuse.return_null_without_error)
    try_call(errormisuse.set_error_but_return_value)
    try_call(errormisuse.clear_error_then_return_null)


