#include <cassert>
#include <stdexcept>
#include <string>

#include "../Settings/params.h"
#include "../Classes/staticWallCell.h"
#include "test_staticWallCell.h"



void test_StaticWallCell() {
    StaticWallCell w1(1, 2);
    assert(w1.get_x() == 1);
    assert(w1.get_y() == 2);

    try {
        StaticWallCell w2(-1, 2);
        assert(false);
    } catch (std::invalid_argument& e) {
        assert(std::string(e.what()).find("Invalid coordinates") != std::string::npos);
    }

    try {
        StaticWallCell w3(1, -2);
        assert(false);
    } catch (std::invalid_argument& e) {
        assert(std::string(e.what()).find("Invalid coordinates") != std::string::npos);
    }

    try {
        StaticWallCell w4(-1, -2);
        assert(false);
    } catch (std::invalid_argument& e) {
        assert(std::string(e.what()).find("Invalid coordinates") != std::string::npos);
    }


    const StaticWallCell w5(6, 7);
    assert(w5['x'] == 6);
    assert(w5['y'] == 7);

    StaticWallCell w6(6, 7);
    try {
        assert(w6['x'] == 6);
    } catch (std::invalid_argument& e) {
        assert(std::string(e.what()).find("Invalid parameter") != std::string::npos);
    }
    try {
        assert(w6['y'] == 7);
    } catch (std::invalid_argument& e) {
        assert(std::string(e.what()).find("Invalid parameter") != std::string::npos);
    }
}
