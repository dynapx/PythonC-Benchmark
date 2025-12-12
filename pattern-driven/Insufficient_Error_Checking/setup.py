from setuptools import setup, Extension
import os

#os.environ["CC"] = "/path-to/gcc-with-cpychecker"
module = Extension(
    'no_null_check',
    sources=['no_null_check.c'],

)

setup(
    name='no_null_check',
    version='1.0',
    description='Python C扩展异常处理示例',
    ext_modules=[module],
)