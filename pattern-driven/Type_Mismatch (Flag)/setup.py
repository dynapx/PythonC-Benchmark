from setuptools import setup, Extension
import os

#os.environ["CC"] = "/path-to/gcc-with-cpychecker"

module = Extension(
    'typemismatch',
    sources=['typemismatch.c'],

)

setup(
    name='TypeMismatch',
    version='1.0',
    description='Python C扩展异常处理示例',
    ext_modules=[module],
)