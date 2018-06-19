from ctypes import *

test = cdll.LoadLibrary("./libhello.so")
print test
testpy = test.HelloFunc
testpy()
