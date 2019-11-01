import numpy as np
import cv2


def compute(array):
    print("origin: ", array)
    result = array + np.random.randint(100, 200)
    cv2.cvtColor(result, cv2.COLOR_BGR2RGB)
    result[result >= 255] = 255
    print("result: ", result)
    return result