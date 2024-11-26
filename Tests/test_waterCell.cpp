#include <cassert>
#include <stdexcept>
#include <string>

#include "../Settings/params.h"
#include "../Classes/waterCell.h"
#include "test_waterCell.h"



void test_WaterCell() {
    WaterCell w1(1, 2, 3, 4, 5);

    assert(w1['u'] == 3);
    assert(w1['v'] == 4);
    assert(w1['p'] == 5);

    
    w1['u'] = 6.f;
    w1['v'] = 7.f;
    w1['p'] = 8.f;

    assert(w1['u'] == 6);
    assert(w1['v'] == 7);
    assert(w1['p'] == 8);

    assert(w1.get_x() == 1);
    assert(w1.get_y() == 2);
    assert(w1.get_u() == 6);
    assert(w1.get_v() == 7);
    assert(w1.get_p() == 8);

    try {
        WaterCell w2(-1, 2, 3, 4, 5);
        assert(false);
    } catch (std::invalid_argument& e) {
        assert(std::string(e.what()).find("Invalid coordinates") != std::string::npos);
    }

    try {
        WaterCell w3(1, -2, 3, 4, 5);
        assert(false);
    } catch (std::invalid_argument& e) {
        assert(std::string(e.what()).find("Invalid coordinates") != std::string::npos);
    }

    try {
        WaterCell w4(-1, -2, 3, 4, 5);
        assert(false);
    } catch (std::invalid_argument& e) {
        assert(std::string(e.what()).find("Invalid coordinates") != std::string::npos);
    }

    try {
        WaterCell w5(1, 2, 3, 4, -5);
        assert(false);
    } catch (std::invalid_argument& e) {
        assert(std::string(e.what()).find("Invalid pressure") != std::string::npos);
    }

    const WaterCell w6(6, 7, 8, 9, 10);
    assert(w6['x'] == 6);
    assert(w6['y'] == 7);
    assert(w6['u'] == 8);
    assert(w6['v'] == 9);
    assert(w6['p'] == 10);

    WaterCell w7(6, 7, 8, 9, 10);
    try {
        assert(w7['x'] == 6);
    } catch (std::invalid_argument& e) {
        assert(std::string(e.what()).find("Invalid parameter") != std::string::npos);
    }
    try {
        assert(w7['y'] == 7);
    } catch (std::invalid_argument& e) {
        assert(std::string(e.what()).find("Invalid parameter") != std::string::npos);
    }
    assert(w7['u'] == 8);
    assert(w7['v'] == 9);
    assert(w7['p'] == 10);
    
    
}
