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
#include <unistd.h>
#include <thread>
#include <chrono>
#include <memory>


extern "C" {


void initialize_field(Field* field) {
    std::ifstream file(FileName);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + std::string(FileName));
    }
    for (int y = 0; y < YGridSize; y++) {
        for (int x = 0; x < XGridSize; x++) {
            char c = file.get();
            if (file.eof()) {
                break;
            }
            if (!file) {
                throw std::runtime_error("Failed to read file: " + std::string(FileName) + " or file is wrong");
            }
            switch (c) {
                case 's': field->set_cell(x, y, std::make_unique<StaticWallCell>(x, y)); break;
                case 'm': field->set_cell(x, y, std::make_unique<MovingWallCell>(x, y, 1, 0)); break;
                case 'w': field->set_cell(x, y, std::make_unique<WaterCell>(x, y, 0, 0, 0));  break;
                case '\n': x--; break;
                default: throw std::runtime_error("Invalid character in file: " + std::string(FileName));
            }
        }
    }
}


int main() {
    try {
        std::cout << "Field creating" << std::endl;
        Field field(XGridSize, YGridSize);
        std::cout << "Field initializing" << std::endl;
        initialize_field(&field);
        std::cout << "Field displaying" << std::endl;
        field.display_without_walls();
        for (int t = 0; t < TimeOfSimulation; t++) {
            std::cout << "\033[2J\033[1;1H";
            field.update();
            field.display_without_walls();
            std::this_thread::sleep_for(std::chrono::milliseconds(TimeStep));
        }
        return 0;
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime error catched: " << e.what() << std::endl;
    }
    
}
}