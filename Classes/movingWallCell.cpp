#include "movingWallCell.h"
#include "../Settings/params.h"

#include <stdexcept>
#include <iostream>
#include <memory>


MovingWallCell::MovingWallCell(int x, int y, float u, float v):WallCell(x, y) {
    this->u = u;
    this->v = v;
    set_type("MovingWall");
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

void MovingWallCell::set_u(float u) {
    this->u = u;
}

void MovingWallCell::set_v(float v) {
    this->v = v;
}

std::string MovingWallCell::get_description() const {
    return "M";
}

std::unique_ptr<Cell> MovingWallCell::copy() const {
    return std::make_unique<MovingWallCell>(*this);
}

