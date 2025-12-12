import typemismatch

def run(name, *args, **kwargs):
    print(f"== {name}({args}, {kwargs}) ==")
    try:
        result = getattr(typemismatch, name)(*args, **kwargs)
        print(f"✔ Result: {result}\n")
    except Exception as e:
        print(f"✘ Exception: {type(e).__name__}: {e}\n")

print("===== 测试 T2.2 测例（共 9 个） =====")

run("wrong_flag_noargs", 10)
run("excess_param_function", 5)
run("parse_kw_without_flag", s="world")
run("missing_kwarg_param", val=1)
run("unused_args", 42)
run("parse_args_in_noargs", "echo-me")
run("declared_but_unused_args", 123)
run("declared_but_unused_o", "oops")
run("declared_but_unused_kw", a=1, b=2)