from setuptools import setup, Extension
import os


os.environ["CC"]  = "clang -emit-llvm"
os.environ["CXX"] = "clang -emit-llvm"
os.environ["LDSHARED"] = "clang -flto -shared"

module = Extension(
    'overflow',
    sources=['overflow.c'],

)

setup(
    name='overflow',
    version='1.0',
    description='Python C扩展异常处理示例',
    ext_modules=[module],
)