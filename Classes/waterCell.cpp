#include "waterCell.h"
#include "../Settings/params.h"

#include <stdexcept>
#include <string>
#include <memory>


WaterCell::WaterCell(int x, int y, float u, float v, float p):Cell(x, y) {
    this->u = u;
    this->v = v;
    if (p < 0) {
        throw std::invalid_argument("Invalid pressure");
    }
    this->p = p;
    this->set_type("Water");
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

void WaterCell::set_u(float u) {
    this->u = u;
}

void WaterCell::set_v(float v) {
    this->v = v;
}

void WaterCell::set_p(float p) {
    if (p < 0) {
        throw std::invalid_argument("Invalid pressure");
    }
    this->p = p;
}

std::unique_ptr<Cell> WaterCell::copy() const {
    return std::make_unique<WaterCell>(*this);
}

std::string WaterCell::get_description() const {
    if (u == 0 && v == 0) {
        return ".";
    }
    if (v == 0) {
        return "-";
    }
    if (u == 0) {
        return "|";
    }
    if ((u > 0 && v > 0) || (u < 0 && v < 0)) {
        return "\\";
    }
    if ((u < 0 && v > 0) || (u > 0 && v < 0)) {
        return "/";
    }
    return "?";
}


extern "C" {
    
    float get_u(WaterCell* cell) {
        return cell->get_u();
    }

    float get_v(WaterCell* cell) {
        return cell->get_v();
    }

    float get_p(WaterCell* cell) {
        return cell->get_p();
    }
}