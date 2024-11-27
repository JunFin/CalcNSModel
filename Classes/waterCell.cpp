#include "waterCell.h"
#include "../Settings/params.h"

#include <stdexcept>
#include <string>


WaterCell::WaterCell(int x, int y, float u, float v, float p):Cell(x, y) {
    this->u = u;
    this->v = v;
    if (p < 0) {
        throw std::invalid_argument("Invalid pressure");
    }
    this->p = p;
    this->type = "Water";
}

float& WaterCell::operator[](char c) {
    switch (c) {
        case 'u': return u;
        case 'v': return v;
        case 'p': return p;
    } 
    throw std::invalid_argument("Invalid parameter");
}

float WaterCell::operator[](char c) const {
    switch (c) {
        case 'u': return u;
        case 'v': return v;
        case 'p': return p;
        case 'x': return get_x();
        case 'y': return get_y();
    } 

    throw std::invalid_argument("Invalid parameter");
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
