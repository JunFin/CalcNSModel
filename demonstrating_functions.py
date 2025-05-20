from initialized_functions import *
from field_analyse_functions import *
import pygame
import math  # for arrow calculations

# Define colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (0, 0, 255)       # вода — всегда голубая
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
            t = CalcNSModel.get_type(cell)

            # базовый цвет
            if t == b"Water":
                color = BLUE
            elif t == b"StaticWall":
                color = GREEN
            elif t == b"MovingWall":
                color = RED
            else:
                color = WHITE

            pygame.draw.rect(screen, color,
                             (x*cell_size, y*cell_size, cell_size, cell_size))


            # рисуем стрелку только если вода и скорость корректна
            if t == b"Water":
                u = CalcNSModel.get_u(cell)
                v = CalcNSModel.get_v(cell)

                # проверяем ненулевую и конечную скорость
                if (u != 0 or v != 0) and math.isfinite(u) and math.isfinite(v):
                    mag = math.hypot(u, v)
                    if mag > 1e-6:
                        ux, uy = u/mag, v/mag
                        cx = x*cell_size + cell_size/2
                        cy = y*cell_size + cell_size/2
                        main_len = 0.8 * cell_size
                        head_len = 0.2 * cell_size
                        half = main_len/2

                        start = (cx - ux*half, cy - uy*half)
                        end   = (cx + ux*half, cy + uy*half)

                        # безопасно приводим в int
                        sp = (int(round(start[0])), int(round(start[1])))
                        ep = (int(round(end[0])),   int(round(end[1])))

                        pygame.draw.line(screen, WHITE, sp, ep, 2)

                        # наконечник ±30°
                        ang = math.radians(30)
                        bx, by = -ux, -uy
                        lx = bx*math.cos(ang) - by*math.sin(ang)
                        ly = bx*math.sin(ang) + by*math.cos(ang)
                        left = (ep[0] + int(round(lx*head_len)),
                                ep[1] + int(round(ly*head_len)))
                        pygame.draw.line(screen, WHITE, ep, left, 2)

                        rx = bx*math.cos(-ang) - by*math.sin(-ang)
                        ry = bx*math.sin(-ang) + by*math.cos(-ang)
                        right = (ep[0] + int(round(rx*head_len)),
                                 ep[1] + int(round(ry*head_len)))
                        pygame.draw.line(screen, WHITE, ep, right, 2)


# Оставляем без изменений main_menu и simulation

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
    speed = 1
    clock = pygame.time.Clock()

    font = pygame.font.SysFont(None, 55)
    small_font = pygame.font.SysFont(None, 35)

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
                return 0
            if event.type == pygame.KEYDOWN and active:
                if event.key == pygame.K_RETURN and paused:
                    cords = find_cells_with_characteristics(screen, fld, XGridSize, YGridSize, cell_size, text, prolog_file_name)
                elif event.key == pygame.K_BACKSPACE:
                    text = text[:-1]
                else:
                    text += event.unicode
            if event.type == pygame.MOUSEBUTTONDOWN:
                if pause_button.collidepoint(event.pos): paused = not paused
                if speed_up_button.collidepoint(event.pos): speed = min(speed + 1, 10)
                if speed_down_button.collidepoint(event.pos): speed = max(speed - 1, 1)
                if find_button.collidepoint(event.pos) and paused:
                    cords = find_cells_with_characteristics(screen, fld, XGridSize, YGridSize, cell_size, text, prolog_file_name)
                if input_box.collidepoint(event.pos): active = not active
                else: active = False
                color = color_active if active else color_inactive
        display(screen, fld, XGridSize, YGridSize, cell_size)
        if not paused:
            cords = []
            for _ in range(int(speed)): CalcNSModel.update(fld)

        pygame.draw.rect(screen, GRAY, pause_button)
        draw_text('Pause', small_font, WHITE, screen, pause_button.x + 10, pause_button.y + 10)
        pygame.draw.rect(screen, GRAY, speed_up_button)
        draw_text('Speed Up', small_font, WHITE, screen, speed_up_button.x + 10, speed_up_button.y + 10)
        pygame.draw.rect(screen, GRAY, speed_down_button)
        draw_text('Speed Down', small_font, WHITE, screen, speed_down_button.x + 10, speed_down_button.y + 10)
        pygame.draw.rect(screen, GRAY, speed_rect)
        draw_text(f'Speed: {speed}x', small_font, WHITE, screen, speed_rect.x + 10, speed_rect.y + 10)

        if paused:
            draw_text('Paused', font, RED, screen, 20, YGridSize * cell_size + 80)
            pygame.draw.rect(screen, GRAY, find_button)
            draw_text('Find', small_font, WHITE, screen, find_button.x + 10, find_button.y + 10)
            for coord in cords:
                pygame.draw.rect(screen, YELLOW, (coord[0] * cell_size, coord[1] * cell_size, cell_size, cell_size))

        txt_surface = small_font.render(text, True, color)
        input_box.w = max(200, txt_surface.get_width() + 10)
        screen.blit(txt_surface, (input_box.x + 5, input_box.y + 5))
        pygame.draw.rect(screen, color, input_box, 2)
        draw_text('Enter cell type', small_font, WHITE, screen, XGridSize * cell_size + 20, 10)

        pygame.display.flip()
        clock.tick(60)
