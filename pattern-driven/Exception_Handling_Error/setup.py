from setuptools import setup, Extension
import os

# os.environ["CC"] = "/path-to/gcc-with-cpychecker"
module = Extension(
    'errormisuse',
    sources=['errormisuse.c'],
)

setup(
    name='errormisuse',
    version='1.0',
    description='Python C扩展异常处理示例',
    ext_modules=[module],
)