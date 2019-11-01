"""
Cython for Python
reference: https://pythonprogramming.net/introduction-and-basics-cython-tutorial/
"""

# example 1
"""
from example_cy import test
print(test(5))
# """

# example 2
# """
from pymodule import compute
import cv2

image = cv2.imread("../deer.jpg")

print("result: ", compute(image))
# """
