import numpy as np

cdef public int test(int x):
    print("x: %d" % x)
    y = np.random.randint(x, x**2)
    print("y: %d (random from %d ~ %d)" % (y, x, x**2))
    return y