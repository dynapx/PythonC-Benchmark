from setuptools import setup, Extension
import os

#os.environ["CC"] = "/path-to/gcc-with-cpychecker"
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