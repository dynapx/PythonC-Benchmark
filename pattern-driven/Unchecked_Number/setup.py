from setuptools import setup, Extension
import os
#os.environ["CC"] = "/path-to/gcc-with-cpychecker"
setup(
    name="divzero",
    ext_modules=[
        Extension("divzero", ["divzero_module.c"])
    ]
)
