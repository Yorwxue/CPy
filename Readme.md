Method of Extension Library Between C and Python
===

## Call a C Function From Python
### By ctypes
```python
from ctypes import cdll, c_int, c_float
clib = cdll.LoadLibrary("PATH/TO/YOUR/CLIB.so")
clib.func(c_int(5), c_float(0.3))
```

## Call a Python Function From C
### By Python/C API
```c
#include <stdio.h>
#include <python3.6/Python.h>

PyObject *pow_func;
Py_Initialize();
PySys_SetPath(Py_DecodeLocale(".", NULL));

/* Get reference to the python function */
PyObject *u_name, *module;
u_name = PyUnicode_FromString("/YOUR/PYTHON/MODULE");
module = PyImport_Import("YOUR_FUNCTION_NAME");
Py_DECREF(u_name);
pow_func = PyObject_GetAttrString(module, symbol);

/* Build arguments */
args = Py_BuildValue("(dd)", x, y);
kwargs = NULL;

/* Call the function */
result = PyObject_Call(pow_func, args, kwargs);
Py_DECREF(args);
Py_XDECREF(kwargs);

/* Create the return value */
retval = PyFloat_AsDouble(result);
Py_DECREF(result);

return retval;
```

## By Cython
+ Using cdef for c/c++, cpdef for c/c++ and ptrhon, such as:
```cython 
cdef public np.ndarray[double, ndim=1] compute(char* path):
    cdef public int attr 
    def __cinit__:
        self.attr = 0
        // your algorithm go here ..
```
+ It's necessary to declare types of return object amd initial attributes.
```cython
from libcpp.string cimport string
from libcpp cimport bool

# common types in Cython
# cdef  int 
# cdef  float 
# cdef  string 
# cdef  object 
# cdef  list 
# cdef  bool 
# cdef YOUR_CUSTOMER_OBJECT 
```
+ Note that if you using your own type, you're suppose to declare object with right type.

# cmake
+ Copy source files(.c) into ./cmake/src
+ Copy head files(.h) into ./cmake/include
+ Copy shared object files(.so) into ./cmake/ and rename to lib*.so
+ Create CMakeLists.txt. 
+ Note that although you execute the commands in ./cmake/build, but you should define related path based on ./cmake
+ Then, run the following command in ./cmake/:
```bash
$ mkdir build
$ cd build
$ cmake ../ > /dev/null; make
```
+ After cmake, you can found executable file with name defined in ./cmake/CMakeLists.txt


### reference: 
> [1] Extension between C and Python: https://medium.com/pyladies-taiwan/%E5%A6%82py%E4%BC%BCc-python-%E8%88%87-c-%E7%9A%84%E5%85%B1%E7%94%9F%E6%B3%95%E5%89%87-568add0ba5b8
> [2] Cython for Python: https://www.cnblogs.com/freeweb/p/6548208.html
> [3] Python-C API: https://learning-python.com/class/Workbook/unit16.htm
> [4] C Extension: http://shouce.jb51.net/Python_jj/c_extensions/python_c_api.html
> [5] C Extension: https://segmentfault.com/a/1190000000479951#articleHeader1
> [6] Numpy for C (Python side): https://stackoverflow.com/questions/28474931/return-numpy-array-in-cython-defined-c-function
> [7] Numpy for C (C side): https://stackoverflow.com/questions/28483819/how-can-i-use-the-numpy-c-api-in-both-c-header-and-source-file
> [8] C function with Numpy object: https://github.com/macklin/C_arraytest
> [9] Numpy type in C(C side): https://docs.scipy.org/doc/numpy/reference/c-api.dtype.html
> [10] Numpy type in C(Python side): https://numpy.org/devdocs/user/basics.types.html
> [11] PyArrayObject: https://blog.csdn.net/zj360202/article/details/79214363
> [12] PyClass for Cython: https://www.reddit.com/r/Cython/comments/8mqlca/convert_python_class_to_cython/
> [13] Using Python Object in C++: https://www.tutorialspoint.com/How-to-use-Python-object-in-Cplusplus