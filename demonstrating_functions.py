from initialized_functions import *
from field_analyse_functions import *
import pygame


# Define colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (0, 0, 255)
DARK_BLUE = (0, 0, 100)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
GRAY = (100, 100, 100)
YELLOW = (255, 255, 0)

def draw_text(text, font, color, surface, x, y):
    textobj = font.render(text, 1, color)
    textrect = textobj.get_rect()
    textrect.topleft = (x, y)
    surface.blit(textobj, textrect)

def display(screen, field, XGridSize, YGridSize, cell_size):
    screen.fill(BLACK)
    for y in range(YGridSize):
        for x in range(XGridSize):
            cell = CalcNSModel.get_cell(field, x, y)
            if CalcNSModel.get_type(cell) == b"Water":
                if CalcNSModel.get_u(cell) != 0 or CalcNSModel.get_v(cell) != 0:
                    color = DARK_BLUE
                else:
                    color = BLUE
            elif CalcNSModel.get_type(cell) == b"StaticWall":
                color = GREEN
            elif CalcNSModel.get_type(cell) == b"MovingWall":
                color = RED
            else:
                color = WHITE
            pygame.draw.rect(screen, color, (x * cell_size, y * cell_size, cell_size, cell_size))

def main_menu(screen, XGridSize, cell_size):
    screen.fill(BLACK)
    font = pygame.font.SysFont(None, 55)
    draw_text('Main Menu', font, WHITE, screen, 20, 20)
    start_button = pygame.Rect(20, 100, XGridSize * cell_size - 40, 50)
    quit_button = pygame.Rect(20, 180, XGridSize * cell_size - 40, 50)
    pygame.draw.rect(screen, GRAY, start_button)
    pygame.draw.rect(screen, GRAY, quit_button)
    draw_text('1. Start Simulation', font, WHITE, screen, 30, 105)
    draw_text('2. Quit', font, WHITE, screen, 30, 185)
    pygame.display.flip()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return False
            if event.type == pygame.MOUSEBUTTONDOWN:
                if start_button.collidepoint(event.pos):
                    return True
                if quit_button.collidepoint(event.pos):
                    pygame.quit()
                    return False


def simulation(screen, fld, XGridSize, YGridSize, cell_size, prolog_file_name):
    flag = True
    paused = False
    speed = 1  # Initial speed
    clock = pygame.time.Clock()

    font = pygame.font.SysFont(None, 55)
    small_font = pygame.font.SysFont(None, 35)

    # Create a surface for the simulation

    pause_button = pygame.Rect(0, YGridSize * cell_size, XGridSize * cell_size // 3, 70)
    speed_up_button = pygame.Rect(XGridSize * cell_size // 3, YGridSize * cell_size, XGridSize * cell_size // 3, 70)
    speed_down_button = pygame.Rect(2 * (XGridSize * cell_size // 3), YGridSize * cell_size, XGridSize * cell_size // 3, 70)
    speed_rect = pygame.Rect(2 * (XGridSize * cell_size // 3), YGridSize * cell_size + 70, XGridSize * cell_size // 3, 70)

    input_box = pygame.Rect(XGridSize * cell_size + 20, 50, 300, 50)
    find_button = pygame.Rect(XGridSize * cell_size + 20, 120, 300, 50)
    color_inactive = pygame.Color('lightskyblue3')
    color_active = pygame.Color('dodgerblue2')
    color = color_inactive
    active = False
    text = ''


    cords = []

    while flag:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                flag = False
                return 0
            if event.type == pygame.KEYDOWN:
                if active:
                    if event.key == pygame.K_RETURN:
                        if paused:
                            cords = find_cells_with_characteristics(screen, fld, XGridSize, YGridSize, cell_size, text, prolog_file_name)
                    elif event.key == pygame.K_BACKSPACE:
                        text = text[:-1]
                    else:
                        text += event.unicode
            if event.type == pygame.MOUSEBUTTONDOWN:
                if pause_button.collidepoint(event.pos):
                    paused = not paused
                if speed_up_button.collidepoint(event.pos):
                    speed = min(speed + 1, 10.0)  # Increase speed, max speed is 10x
                if speed_down_button.collidepoint(event.pos):
                    speed = max(speed - 1, 1)  # Decrease speed, min speed is 0.1x
                if find_button.collidepoint(event.pos) and paused:
                    cords = find_cells_with_characteristics(screen, fld, XGridSize, YGridSize, cell_size, text, prolog_file_name)
                if input_box.collidepoint(event.pos):
                    active = not active
                else:
                    active = False
                color = color_active if active else color_inactive

        display(screen, fld, XGridSize, YGridSize, cell_size)
        if not paused:
            cords = []
            for _ in range(int(speed)):
                CalcNSModel.update(fld)
        

        # Draw control layer below the simulation
        pygame.draw.rect(screen, GRAY, pause_button)
        draw_text('Pause', small_font, WHITE, screen, pause_button.x + 10, pause_button.y + 10)

        pygame.draw.rect(screen, GRAY, speed_up_button)
        draw_text('Speed Up', small_font, WHITE, screen, speed_up_button.x + 10, speed_up_button.y + 10)

        pygame.draw.rect(screen, GRAY, speed_down_button)
        draw_text('Speed Down', small_font, WHITE, screen, speed_down_button.x + 10, speed_down_button.y + 10)

        # Draw current speed
        pygame.draw.rect(screen, GRAY, speed_rect)
        draw_text(f'Speed: {speed:.2f}x', small_font, WHITE, screen, speed_rect.x + 10, speed_rect.y + 10)

        if paused:
            draw_text('Paused', font, RED, screen, 20, YGridSize * cell_size + 80)

            # Draw the "Find" button only when paused
            pygame.draw.rect(screen, GRAY, find_button)
            draw_text('Find', small_font, WHITE, screen, find_button.x + 10, find_button.y + 10)

            for coord in cords:
                pygame.draw.rect(screen, YELLOW, (coord[0] * cell_size, coord[1] * cell_size, cell_size, cell_size))

        # Draw the input box and text
        txt_surface = small_font.render(text, True, color)
        width = max(200, txt_surface.get_width() + 10)
        input_box.w = width
        screen.blit(txt_surface, (input_box.x + 5, input_box.y + 5))
        pygame.draw.rect(screen, color, input_box, 2)
        draw_text('Enter cell type', small_font, WHITE, screen, XGridSize * cell_size + 20, 10)

        pygame.display.flip()
        clock.tick(60)
