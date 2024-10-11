#include "waterCell.h"
#include "params.h"

#include <stdexcept>


WaterCell::WaterCell(int x, int y, float u, float v, float p) {
    if (x < 0 || x >= GridSize || y < 0 || y >= GridSize) {
        throw std::invalid_argument("Invalid coordinates");
    }
    this->x = x;
    this->y = y;
    this->u = u;
    this->v = v;

    if (p < 0) {
        throw std::invalid_argument("Invalid pressure");
    }
    this->p = p;
}

float& WaterCell::operator[](char c) {
    switch (c) {
        case 'u': return u;
        case 'v': return v;
        case 'p': return p;
    } 

    throw std::invalid_argument("Invalid parameter");
}

int WaterCell::get_x() {
    return x;
}  

int WaterCell::get_y() {
    return y;
}

float WaterCell::get_u() {
    return u;
}

float WaterCell::get_v() {
    return v;
}

float WaterCell::get_p() {
    return p;
}