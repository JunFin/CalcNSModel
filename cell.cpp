#include "cell.h"
#include "params.h"
#include <stdexcept>


Cell::Cell(int x, int y) {
    if (x < 0 || x >= GridSize || y < 0 || y >= GridSize) {
        throw std::invalid_argument("Invalid coordinates");
    }
    this->x = x;
    this->y = y;
}

const int Cell::operator[](char c) const {
    switch (c) {
        case 'x': return x;
        case 'y': return y;
    }
    throw std::invalid_argument("Invalid parameter");
}