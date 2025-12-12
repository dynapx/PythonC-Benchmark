from setuptools import setup, Extension
import os

#os.environ["CC"] = "/path-to/gcc-with-cpychecker"

module = Extension(
    'argparse_mismatch',
    sources=['argparse_mismatch.c'],

)

setup(
    name='argparse_mismatch',
    version='1.0',
    description='Python C扩展异常处理示例',
    ext_modules=[module],
)