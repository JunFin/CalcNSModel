from initialized_functions import *
from demonstrating_functions import *
from field_analyse_functions import *
import pygame

XGridSize = 99
YGridSize = 99

cell_size = 7

fld = CalcNSModel.initialize_field()

pygame.init()
screen = pygame.display.set_mode((XGridSize * cell_size + 400, YGridSize * cell_size + 140))
pygame.display.set_caption("Simulation")


print("Creating Prolog file...")
prolog_file_name = 'field.pl'
make_prolog_file('field.txt', prolog_file_name)
print("Prolog file created successfully.")


if __name__ == "__main__":
    if main_menu(screen, XGridSize, cell_size):
        simulation(screen, fld, XGridSize, YGridSize, cell_size, prolog_file_name)
