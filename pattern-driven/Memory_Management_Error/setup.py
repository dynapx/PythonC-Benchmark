from setuptools import setup, Extension
import os

#os.environ["CC"] = "/path-to/gcc-with-cpychecker"
modules = [
              Extension('memerrors', sources=['memerrors_module.c']),
              Extension('mismatch',  sources=['mismatch_module.c']),
]

setup(
    name='vuln_demo',
    version='0.1',
    ext_modules=modules,
)