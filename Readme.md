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


### reference: 
> [1] Extension between C and Python: https://medium.com/pyladies-taiwan/%E5%A6%82py%E4%BC%BCc-python-%E8%88%87-c-%E7%9A%84%E5%85%B1%E7%94%9F%E6%B3%95%E5%89%87-568add0ba5b8
> [2] Cython: https://www.cnblogs.com/freeweb/p/6548208.html
> [3] Python-C API: https://learning-python.com/class/Workbook/unit16.htm
> [4] C Extension: http://shouce.jb51.net/Python_jj/c_extensions/python_c_api.html
> [5] C Extension: https://segmentfault.com/a/1190000000479951#articleHeader1