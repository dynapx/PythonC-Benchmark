from setuptools import setup, Extension
#os.environ["CC"] = "/path-to/gcc-with-cpychecker"
module = Extension(
    'overflow',
    sources=['overflow.c']
)

setup(
    name="overflow",
    version="1.0",
    description="Integer overflow test module",
    ext_modules=[module]
)