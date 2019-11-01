import time


def timer(func, *args):
    func_name = str(func).split(" ")[1]
    START = time.time()
    result = func(*args)
    print("Function %s spent %f seconds" % (func_name, (time.time() - START)))
    return result
