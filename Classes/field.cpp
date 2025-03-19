#include "field.h"
#include "cell.h"
#include "waterCell.h"
#include "movingWallCell.h"
#include "staticWallCell.h"

#include <vector>
#include <stdexcept>
#include <iostream>
#include <memory>




Field::Field(int xSize, int ySize) {
    if (xSize <= 0 || ySize <= 0) {
        throw std::invalid_argument("Field dimensions must be positive integers");
    }
    this->xSize = xSize;
    this->ySize = ySize;
    this->field = std::vector<std::vector<std::unique_ptr<Cell>>>(xSize);
    for (int x = 0; x < xSize; x++) {
        this->field[x] = std::vector<std::unique_ptr<Cell>>(ySize);
        for (int y = 0; y < ySize; y++) {
            set_cell(x, y, std::make_unique<Cell>(x, y));
        }
    }
}

Field::Field(Field&& other) noexcept  // move constructor
    : xSize(other.xSize), ySize(other.ySize), field(std::move(other.field)) {
    other.xSize = 0;
    other.ySize = 0;
}

Field& Field::operator=(Field&& other) noexcept {  // move assignment
    if (this != &other) {
        xSize = other.xSize;
        ySize = other.ySize;
        field = std::move(other.field);

        other.xSize = 0;
        other.ySize = 0;
    }
    return *this;
}


void Field::set_xSize(int xSize) {
    if (xSize <= 0) {
        throw std::invalid_argument("Field dimensions must be positive integers");
    }
    this->xSize = xSize;
}

void Field::set_ySize(int ySize) {
    if (ySize <= 0) {
        throw std::invalid_argument("Field dimensions must be positive integers");
    }
    this->ySize = ySize;
}


int Field::get_xSize() const {
    return xSize;
}

int Field::get_ySize() const {
    return ySize;
}

void Field::set_cell(int x, int y, std::unique_ptr<Cell> cell) {
    if (x < 0 || y < 0 || x >= xSize || y >= ySize) {
        throw std::invalid_argument("Invalid coordinates");
    }
    field[x][y] = std::move(cell);
}


Cell* Field::get_cell(int x, int y) {
    if (x < 0 || x >= xSize || y < 0 || y >= ySize) {
        throw std::invalid_argument("Invalid coordinates");
    }
    return field[x][y].get();
}
