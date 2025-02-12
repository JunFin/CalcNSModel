#include "wallCell.h"
#include "../Settings/params.h"

#include <stdexcept>




WallCell::WallCell(int x, int y):Cell(x, y) {
    this->type = "NoneWall";
}

float WallCell::operator[](char c) const {
    switch (c) {
        case 'x': return get_x();
        case 'y': return get_y();
    } 

    throw std::invalid_argument("Invalid parameter");
}


