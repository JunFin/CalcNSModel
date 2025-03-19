import subprocess

def make_prolog_file(input_file, output_file):
    with open(input_file, 'r') as input_file:
        data = input_file.read()
        with open(output_file, 'w') as output_file:
            for y, line in enumerate(data.split('\n')):
                for x, cell in enumerate(line):
                    if cell == 'w':
                        output_file.write(f'cell(water, [{x}, {y}]).\n')
                    elif cell == 'm':
                        output_file.write(f'cell(moving_wall, [{x}, {y}]).\n')
                    elif cell == 's':
                        output_file.write(f'cell(static_wall, [{x}, {y}]).\n')
        
            output_file.close()
        input_file.close()
    
    return
    

def find_cells_with_characteristics(screen, field, XGridSize, YGridSize, cell_size, type, prolog_file_name):
    # Call the Prolog program to find cells with the given characteristics
    prolog_command = f"swipl -s {prolog_file_name} -g 'cell({type}, Coordinates), write(Coordinates), nl, fail; halt.'"
    result = subprocess.run(prolog_command, shell=True, capture_output=True, text=True)
    coordinates = [[int(coord) for coord in line.split('[')[1].split(']')[0].split(',')] for line in result.stdout.split('\n')[:-1]]
    # Highlight the cells with the returned coordinates
    return coordinates

