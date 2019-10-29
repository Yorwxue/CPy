/************************
* 1. compile by execute the following command:  "gcc -g -Wall main.c -lpython3.6m -o py_c.out"
* 2. run py2c.out
reference: https://learning-python.com/class/Workbook/unit16.htm
************************/

#include <stdio.h>
#include <python3.6/Python.h>

/* Execute func(x,y) in the Python interpreter.  The
   arguments and return result of the function must
   be Python floats */

double call_func(PyObject *func, double x, double y) {
    PyObject *args;
    PyObject *kwargs;
    PyObject *result = 0;
    double retval;

    /* Make sure we own the GIL */
    PyGILState_STATE state = PyGILState_Ensure();

    /* Verify that func is a proper callable */
    if (!PyCallable_Check(func)) {
        fprintf(stderr,"call_func: expected a callable\n");
        goto fail;
    }
    /* Build arguments */
    args = Py_BuildValue("(dd)", x, y);
    kwargs = NULL;

    /* Call the function */
    result = PyObject_Call(func, args, kwargs);
    Py_DECREF(args);
    Py_XDECREF(kwargs);

    /* Check for Python exceptions (if any) */
    if (PyErr_Occurred()) {
        PyErr_Print();
        goto fail;
    }

    /* Verify the result is a float object */
    if (!PyFloat_Check(result)) {
        fprintf(stderr,"call_func: callable didn't return a float\n");
        goto fail;
    }

    /* Create the return value */
    retval = PyFloat_AsDouble(result);
    Py_DECREF(result);

    /* Restore previous GIL state and return */
    PyGILState_Release(state);
    return retval;

    fail:
    Py_XDECREF(result);
    PyGILState_Release(state);
    abort();   // Change to something more appropriate
}

/* Load a symbol from a module */
PyObject *import_name(const char *modname, const char *symbol) {
    PyObject *u_name, *module;
    u_name = PyUnicode_FromString(modname);
    module = PyImport_Import(u_name);
    Py_DECREF(u_name);
    return PyObject_GetAttrString(module, symbol);
}

/* Simple embedding example */
int main() {
    printf("import python module in c program.\n");
    double x = 0.2;
    double y = 0.3;

    Py_Initialize();

    PySys_SetPath(Py_DecodeLocale(".", NULL));

    /* import python library */
//    PyObject *sys_path = PySys_GetObject("path");
//    PyList_Append(sys_path, PyString_FromString("/home/clliao/CppProjects/py2c/venv/lib/python3.6/site-packages"));
//    PyObject* np = PyImport_ImportModule("numpy");

    /* Get the reference to the python function */
    PyObject *pclass = import_name("pymodule","pycompute");

    /* Declare python object*/
    PyObject *pargs  = Py_BuildValue("()");
    PyObject *py_obj = PyEval_CallObject(pclass, pargs);

    /* Call it using call_func() code */
    PyObject *py_func = PyObject_GetAttrString(py_obj, "compute");
    printf("ans: %0.2f\n", call_func(py_func, x, y));
    
    /* Done */
//    Py_DECREF(sys_path);
    Py_DECREF(pclass);
    Py_DECREF(pargs);
    Py_DECREF(py_obj);
    Py_DECREF(py_func);
    Py_Finalize();
    return 0;
}