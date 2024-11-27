#include "Classes/field.h"
#include "Classes/cell.h"
#include "Classes/waterCell.h"
#include "Classes/movingWallCell.h"
#include "Classes/staticWallCell.h"
#include "Settings/params.h"

#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>

void initialize_field(Field* field);

void initialize_field(Field* field) {
    std::ifstream file(FileName);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + std::string(FileName));
    }
    for (int x = 0; x < GridSize; x++) {
        for (int y = 0; y < GridSize; y++) {
            char c = file.get();
            if (!file) {
                throw std::runtime_error("Failed to read file: " + std::string(FileName));
            }
            std::cout << c;
            switch (c) {
                case 's': field->set_cell(x, y, new StaticWallCell(x, y)); break;
                case 'm': field->set_cell(x, y, new MovingWallCell(x, y, 0, 0)); break;
                case 'w': field->set_cell(x, y, new WaterCell(x, y, 0, 0, 0));  break;
                default: throw std::runtime_error("Unknown cell type: " + std::string(1, c));   
            }
        }
    }
}


int main() {
    std::cout << "Field creating" << std::endl;
    Field field(GridSize, GridSize);
    std::cout << "Field initializing" << std::endl;
    initialize_field(&field);
    field.display();
}