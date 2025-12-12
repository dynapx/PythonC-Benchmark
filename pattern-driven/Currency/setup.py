from setuptools import setup, Extension
import os

#os.environ["CC"] = "/path-to/gcc-with-cpychecker"
modules = [
    Extension('blockio', sources=['block_module.c']),
]

setup(
    name='vuln_demo',
    version='0.1',
    ext_modules=modules,
)