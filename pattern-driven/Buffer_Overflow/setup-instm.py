from setuptools import setup, Extension
import os

os.environ["CC"]  = "clang -emit-llvm -Xclang -load -Xclang llvmSDIpass.so"
os.environ["CXX"] = "clang -emit-llvm -Xclang -load -Xclang llvmSDIpass.so"
os.environ["LDSHARED"] = "clang -flto -pthread -shared -lDynAnalyze"

module = Extension(
    'buffer_overflow',
    sources=['buffer_overflow.c'],
)

setup(
    name='buffer_overflow',
    version='1.0',
    description='Python C扩展异常处理示例',
    ext_modules=[module],
)