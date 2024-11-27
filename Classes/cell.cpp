#include "cell.h"
#include "../Settings/params.h"

#include <stdexcept>


Cell::Cell(int x, int y) {
    if (x < 0 || x >= GridSize || y < 0 || y >= GridSize) {
        throw std::invalid_argument("Invalid coordinates");
    }
    this->x = x;
    this->y = y;
    this->type = "None";
}

float Cell::operator[](char c) const {
    switch (c) {
        case 'x': return x;
        case 'y': return y;
    }
    throw std::invalid_argument("Invalid parameter");
}

int Cell::get_x() const {
    return x;
}  

int Cell::get_y() const {
    return y;
}

std::string Cell::get_description() const {
    return "Cell at (" + std::to_string(x) + ", " + std::to_string(y) + ") " + "with type: " + type;
}
