from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

ext_modules = [
    Extension("hello_pyx2",
              sources=["hello2.pyx"],
              libraries=["m"]  # Unix-like specific
              )
]

setup(name="hello_pyx2",
      ext_modules=cythonize(ext_modules))