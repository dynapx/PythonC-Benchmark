# import overflow
# import sys
#
# def get_nun():
#     return -123
# print("=== T1.1 测例 ===")
# try:
#     print("T1.1 测例1:", overflow.pyarg_overflow(2 ** 100))
# except Exception as e:
#     print("T1.1 测例1 failed:", e)
#
# try:
#     print("T1.1 测例2:", overflow.float_to_long(1e100))
# except Exception as e:
#     print("T1.1 测例2 failed:", e)
#
# try:
#     print("T1.1 测例3:", overflow.double_to_long_overflow(1e308))
# except Exception as e:
#     print("T1.1 测例3 failed:", e)
#
# print("\n=== T1.2 测例 ===")
# try:
#     print("T1.2 测例1:", overflow.add_overflow(922337203685477005807, 922337203685477005807))
# except Exception as e:
#     print("T1.2 测例1 failed:", e)
#
# try:
#     print("T1.2 测例2小:", overflow.mul_overflow(10000, 1000000))
#     print("T1.2 测例2大:", overflow.mul_overflow(100000000, 100000000))
# except Exception as e:
#     print("T1.2 测例2 failed:", e)
#
# try:
#     num=get_nun()
#     print("T1.2 测例3:", overflow.unsigned_cast(num))
# except Exception as e:
#     print("T1.2 测例3 failed:", e)
#
# try:
#     print("T1.2 测例4:", overflow.shift_overflow(1, 4000))
# except Exception as e:
#     print("T1.2 测例4 failed:", e)
#
# try:
#     print("T1.2 测例5:", overflow.float_mul_overflow(1e308, 1e10))
# except Exception as e:
#     print("T1.2 测例5 failed:", e)
#
# try:
#     print("T1.2 测例6:", overflow.float_cast_error("not-a-float"))
# except Exception as e:
#     print("T1.2 测例6 failed:", e)


print("hello")
