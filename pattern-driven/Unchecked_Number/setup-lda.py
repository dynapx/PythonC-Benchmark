from setuptools import setup, Extension

import os
os.environ["CC"]  = "clang -emit-llvm"
os.environ["CXX"] = "clang -emit-llvm"
os.environ["LDSHARED"] = "clang -flto -shared"
modules = [
    # Extension('vlasize', sources=['vlasize_module.c']),  # VLASize 漏洞模块
    #  Extension('bitshift', sources=['bitshift_module.c']),# BitwiseShift 漏洞模块
    Extension('divzero', sources=['divzero_module.c']),  # DivideZero 漏洞模块
]

setup(
    name='vuln_demo',
    version='0.1',
    ext_modules=modules,
)