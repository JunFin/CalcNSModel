import ctypes
import os

XGridSize = 99
YGridSize = 49
print(0)

if os.name == "posix":  # Linux/macOS
    CalcNSModel = ctypes.CDLL("./library.so")
else:  # Windows
    CalcNSModel = ctypes.CDLL("./library.dll")

print(1)

CalcNSModel.create_field.argtypes = [ctypes.c_int, ctypes.c_int]
CalcNSModel.create_field.restype = ctypes.c_void_p

CalcNSModel.initialize_field.argtypes = [ctypes.c_void_p]
CalcNSModel.initialize_field.restype = None

CalcNSModel.update_field.argtypes = [ctypes.c_void_p]
CalcNSModel.update_field.restype = None

CalcNSModel.display_field.argtypes = [ctypes.c_void_p]
CalcNSModel.display_field.restype = None

CalcNSModel.display_field_without_walls.argtypes = [ctypes.c_void_p]
CalcNSModel.display_field_without_walls.restype = None


field = CalcNSModel.create_field(XGridSize, YGridSize)
CalcNSModel.initialize_field(field)

for i in range(100):
    CalcNSModel.update_field(field)
    CalcNSModel.display_field(field)
    CalcNSModel.display_field_without_walls(field)