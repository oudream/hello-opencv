from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

ext_modules = [
    Extension("hello_pyx1",
              sources=["hello1.pyx"],
              libraries=["m"]  # Unix-like specific
              )
]

setup(name="hello_pyx1",
      ext_modules=cythonize(ext_modules))