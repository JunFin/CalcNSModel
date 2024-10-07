#include "waterCell.h"
#include "params.h"

#include <stdexcept>


float& WaterCell::operator[](char c) {
    switch (c) {
        case 'u': return u;
        case 'v': return v;
        case 'p': return p;
    }

    throw std::invalid_argument("Invalid parameter");

}

const int& WaterCell::operator[](char c) const {
    switch (c) {
        case 'x': return x;
        case 'y': return y;
    }

    throw std::invalid_argument("Invalid parameter");
}

