/************************
* 1. compile by execute the following command:  "gcc $(python3-config --includes) main.c $(python3-config --libs) -o main.o [libXXX.so]"
* 2. export LD_LIBRARY_PATH=/PATH/TO/DIRECTORY/OF/YOUR/LIBXXX.so
* 3. run the command: ./cy_c.o
reference: https://medium.com/pyladies-taiwan/%E5%A6%82py%E4%BC%BCc-python-%E8%88%87-c-%E7%9A%84%E5%85%B1%E7%94%9F%E6%B3%95%E5%89%87-568add0ba5b8
************************/

#include <Python.h>
#include "example_cy.h"
//#include "pymodule.h"

// example 1
/**/
int main() {
  // Init module & Python compiler
  PyImport_AppendInittab("example_cy", PyInit_example_cy);
  Py_Initialize();
  PyImport_ImportModule("example_cy");

  // call function
  printf("%d\n", test(3));

  // release resource used by Python
  Py_Finalize();
}
/**/

// example 2
/**
int main() {
  // Init module & Python compiler
  PyImport_AppendInittab("pymodule", PyInit_example_cy);
  Py_Initialize();
  PyImport_ImportModule("pymodule");

  // call function
  printf("%d\n", test(3));

  // release resource used by Python
  Py_Finalize();
}
/**/
