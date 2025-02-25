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


Field* initialize_field() {
    Field * field = new Field(XGridSize,YGridSize);
    std::ifstream file(FileName);
    if (!file.is_open()) {
        delete field;
        return NULL; //throw std::runtime_error("Failed to open file: " + std::string(FileName));
    }
    for (int y = 0; y < YGridSize; y++) {
        for (int x = 0; x < XGridSize; x++) {
            char c = file.get();
            if (file.eof()) {
                break;
            }
            if (!file) {
                delete field;
                return NULL;
                //throw std::runtime_error("Failed to read file: " + std::string(FileName) + " or file is wrong");
            }
            switch (c) {
                case 's': field->set_cell(x, y, std::make_unique<StaticWallCell>(x, y)); break;
                case 'm': field->set_cell(x, y, std::make_unique<MovingWallCell>(x, y, 1, 0)); break;
                case 'w': field->set_cell(x, y, std::make_unique<WaterCell>(x, y, 0, 0, 0));  break;
                case '\n': x--; break;
                default: delete field; return NULL; //throw std::runtime_error("Invalid character in file: " + std::string(FileName));
            }
        }
    }
    return field;
}

}
