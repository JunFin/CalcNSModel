import ctypes
import os
import time

XGridSize = 99
YGridSize = 49

if os.name == "posix":  # Linux/macOS
    CalcNSModel = ctypes.CDLL("./library.so")
else:  # Windows
    CalcNSModel = ctypes.CDLL("./library.dll")


CalcNSModel.initialize_field.argtypes = []
CalcNSModel.initialize_field.restype = ctypes.c_void_p

CalcNSModel.display_without_walls.argtypes = [ctypes.c_void_p]
CalcNSModel.display_without_walls.restype = None

CalcNSModel.update.argtypes = [ctypes.c_void_p]
CalcNSModel.update.restype = None

fld = CalcNSModel.initialize_field()

CalcNSModel.display_without_walls(fld)

for i in range(1000):
    CalcNSModel.update(fld)
    CalcNSModel.display_without_walls(fld)
    time.sleep(0.1)
