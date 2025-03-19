#include "cell.h"
#include "../Settings/params.h"

#include <stdexcept>
#include <memory>


Cell::Cell(int x, int y) {
    if (x < 0 || y < 0) {
        throw std::invalid_argument("Invalid coordinates");
    }
    this->x = x;
    this->y = y;
    this->type = "None";
}

Cell::~Cell() {}

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

std::string Cell::get_type() const {
    return type;
}

std::string Cell::get_description() const{
    return " ";
}

std::string Cell::get_description_test() const {
    return "Cell at (" + std::to_string(x) + ", " + std::to_string(y) + ") " + "with type: " + type;
}

void Cell::set_type(std::string type) {
    this->type = type;
}

std::unique_ptr<Cell> Cell::copy() const {
    return std::make_unique<Cell>(*this);
}
