"""
package python module by running command: python3 setup.py build_ext
for difference application, such as for c or for python, you should write in difference way
reference: https://www.cnblogs.com/freeweb/p/6548208.html
"""
from distutils.core import setup
from Cython.Build import cythonize


print("package python module to .so file")

setup(
    ext_modules=cythonize("pymodule.py")
)
print("done")
