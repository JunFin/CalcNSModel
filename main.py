import ctypes
import os
import time

import pygame

XGridSize = 99
YGridSize = 99

if os.name == "posix":  # Linux/macOS
    CalcNSModel = ctypes.CDLL("./library.so")
else:  # Windows
    CalcNSModel = ctypes.CDLL("./library.dll")


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

fld = CalcNSModel.initialize_field()


cell_size = 5


pygame.init()
screen = pygame.display.set_mode((XGridSize * cell_size, YGridSize * cell_size))



def display(field):    
    screen.fill((0, 0, 0))
    for y in range(YGridSize):
        for x in range(XGridSize):
            cell = CalcNSModel.get_cell(field, x, y)
            if CalcNSModel.get_type(cell) == b"Water":
                if CalcNSModel.get_u(cell) != 0 or CalcNSModel.get_v(cell) != 0:
                    color = (0, 0, 100)
                else:
                    color = (0, 0, 255)
            elif CalcNSModel.get_type(cell) == b"StaticWall":
                color = (0, 255, 0)
            elif CalcNSModel.get_type(cell) == b"MovingWall":
                color = (255, 0, 0)
            else:
                color = (255, 255, 255)
            pygame.draw.rect(screen, color, (x * cell_size, y * cell_size, cell_size, cell_size))
    pygame.display.flip()


flag = True
clock = pygame.time.Clock() 
while flag:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            flag = False
            break
    display(fld)
    CalcNSModel.update(fld)
    clock.tick(60)
