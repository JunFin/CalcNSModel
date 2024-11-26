#include "movingWallCell.h"
#include "../Settings/params.h"

#include <stdexcept>


MovingWallCell::MovingWallCell(int x, int y, float u, float v):WallCell(x, y) {
    this->u = u;
    this->v = v;
}


float& MovingWallCell::operator[](char c) {
    switch (c) {
        case 'u': return u;
        case 'v': return v;
    } 
    throw std::invalid_argument("Invalid parameter");
}


float MovingWallCell::operator[](char c) const {
    switch (c) {
        case 'u': return u;
        case 'v': return v;
        case 'x': return get_x();
        case 'y': return get_y();
    } 

    throw std::invalid_argument("Invalid parameter");
}

float MovingWallCell::get_u() {
    return u;
}

float MovingWallCell::get_v() {
    return v;
}
