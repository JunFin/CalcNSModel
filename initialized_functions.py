import ctypes
import os

if os.name == "posix":  # Linux/macOS
    CalcNSModel = ctypes.CDLL("./CalcNSModel.so")
else:  # Windows
    CalcNSModel = ctypes.CDLL("./CalcNSModel.dll")


CalcNSModel.initialize_field.argtypes = []
CalcNSModel.initialize_field.restype = ctypes.c_void_p

CalcNSModel.create_field.restype = ctypes.c_void_p

CalcNSModel.display_without_walls.argtypes = [ctypes.c_void_p]
CalcNSModel.display_without_walls.restype = None

CalcNSModel.update.argtypes = [ctypes.c_void_p]
CalcNSModel.update.restype = None

CalcNSModel.get_cell.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
CalcNSModel.get_cell.restype = ctypes.c_void_p

CalcNSModel.get_x.argtypes = [ctypes.c_void_p]
CalcNSModel.get_x.restype = ctypes.c_int

CalcNSModel.get_y.argtypes = [ctypes.c_void_p]
CalcNSModel.get_y.restype = ctypes.c_int

CalcNSModel.get_type.argtypes = [ctypes.c_void_p]
CalcNSModel.get_type.restype = ctypes.c_char_p

CalcNSModel.get_u.argtypes = [ctypes.c_void_p]
CalcNSModel.get_u.restype = ctypes.c_float

CalcNSModel.get_v.argtypes = [ctypes.c_void_p]
CalcNSModel.get_v.restype = ctypes.c_float

CalcNSModel.get_p.argtypes = [ctypes.c_void_p]
CalcNSModel.get_p.restype = ctypes.c_float
