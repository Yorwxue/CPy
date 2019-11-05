import os
import sys
import numpy as np
import cv2

cimport numpy as np
cimport cython


cdef public np.ndarray[double, ndim=1] compute(char* path):
    print("python version: ", sys.version)
    abspath = os.path.abspath(path.decode("utf-8"))
    print("path: %s" % abspath)
    img = cv2.imread(abspath)
    x_max, y_max, z_max = img.shape
    print("image shape: (%d, %d, %d)" % (x_max, y_max, z_max))

    mask = np.ones_like(img).astype(np.float)
    mask[:, :, 0] = mask[:, :, 0] * 1.1
    img_masked = img * mask
    img_masked = img_masked.astype(np.uint8)
    img_masked[img_masked>255] = 255

    print("mse: %f" % np.mean(np.power((img_masked-img), 2)))
    cv2.imwrite("test.jpg", img_masked)

    ret = np.random.randn(3)
    print("return: ", ret)
    return ret
