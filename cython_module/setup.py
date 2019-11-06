"""
package python module by running command: python3 setup.py build_ext --inplace
for difference application, such as for c or for python, you should write in difference way
reference:
[1] https://www.cnblogs.com/freeweb/p/6548208.html
[2] https://stackoverflow.com/questions/14657375/cython-fatal-error-numpy-arrayobject-h-no-such-file-or-directory
"""
from distutils.core import setup
from Cython.Build import cythonize


print("package python module to .so file")

setup(
    include_dirs=".",  # Path to your lib, such as numpy[2].
    ext_modules=cythonize("pymodule.pyx")
)
print("done")
