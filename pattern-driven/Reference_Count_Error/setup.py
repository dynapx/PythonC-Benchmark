from setuptools import setup, Extension
import os

#os.environ["CC"] = "/path-to/gcc-with-cpychecker"


module = Extension(
    'refbug',
    sources=['refbug.c'],

)

setup(
    name='refbug',
    version='1.0',
    description='Python C扩展异常处理示例',
    ext_modules=[module],
)