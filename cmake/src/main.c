/************************
* 1. compile by execute the following command:  "gcc $(python3-config --includes) main.c $(python3-config --libs) -o main.o [libXXX.so]"
* 2. export LD_LIBRARY_PATH=/PATH/TO/DIRECTORY/OF/YOUR/LIBXXX.so
* 3. run the command: ./cy_c.o
reference:
[1] https://medium.com/pyladies-taiwan/%E5%A6%82py%E4%BC%BCc-python-%E8%88%87-c-%E7%9A%84%E5%85%B1%E7%94%9F%E6%B3%95%E5%89%87-568add0ba5b8
[2] https://blog.csdn.net/zj360202/article/details/79214363
************************/

#include "Python.h"

/* PATH TO YOUR numpy/core/include/numpy*/
#include "numpy/arrayobject.h"

#include "pymodule.h"

int show_vector(PyArrayObject *vec);
int not_doublevector(PyArrayObject *vec);


int main() {
  // Init module & Python compiler
  PyImport_AppendInittab("pymodule", PyInit_pymodule);
  Py_Initialize();
  PyImport_ImportModule("pymodule");

  // call function
  printf("NPY_FLOAT64: %d\n", 1-not_doublevector(compute("../deer.jpg")));
  show_vector(compute("../deer.jpg"));

  // release resource used by Python
  Py_Finalize();
}


int show_vector(PyArrayObject *pyvec){

    double *cvec;
    int dim, n, m;
    const char *str;

    /* Check that objects are 'double' type and vectors
       Not needed if python wrapper function checks before call to this routine */
    if (NULL == pyvec)  return NULL;

    /* Get vector dimension. */
    n = PyArray_DIM(pyvec, 0);
    printf("dimension: %d\n", n);

    /* Change contiguous arrays into C * arrays   */
    cvec=(double *) PyArray_DATA(pyvec);

    /* show the vector */
    for(int i=0;i<n;i++){
        printf("%f ", cvec[i]);
    }
    printf("\n");

    return 1;
}

/* ==== Check that PyArrayObject is a double (Float) type and a vector ==============
    return 1 if input vector not belong to double type */
int not_doublevector(PyArrayObject *vec)  {
//	if (vec->descr->type_num != NPY_DOUBLE || vec->nd != 1)  {
	if (PyArray_TYPE(vec) != NPY_DOUBLE || PyArray_NDIM(vec) != 1)
		return 1;
	return 0;
}
