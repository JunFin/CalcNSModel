#include "field.h"
#include "cell.h"

#include <vector>
#include <stdexcept>
#include <iostream>


Field::Field(int xSize, int ySize) {
    if (xSize <= 0 || ySize <= 0) {
        throw std::invalid_argument("Field dimensions must be positive integers");
    }

    this->xSize = xSize;
    this->ySize = ySize;
    this->field = std::vector<std::vector<Cell*> >(xSize, std::vector<Cell*>(ySize, new Cell(0, 0)));
}

Field::~Field() {
    for (int x = 0; x < xSize; x++) {
        for (int y = 0; y < ySize; y++) {
            delete field[x][y];
        }
    }
}

int Field::get_xSize() const {
    return xSize;
}

int Field::get_ySize() const {
    return ySize;
}

void Field::set_cell(int x, int y, Cell* cell) {
    if (x < 0 || x >= xSize || y < 0 || y >= ySize) {
        throw std::invalid_argument("Invalid coordinates");
    }
    field[x][y] = cell;
}

Cell* Field::get_cell(int x, int y) {
    if (x < 0 || x >= xSize || y < 0 || y >= ySize) {
        throw std::invalid_argument("Invalid coordinates");
    }
    return field[x][y];
}

void Field::display() {
    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            std::cout << "| " << field[i][j]->get_description() << " ";
        }
        std::cout << "|" << std::endl;
    }
}


