#include <cassert>
#include <stdexcept>
#include <string>

#include "../Settings/params.h"
#include "../Classes/movingWallCell.h"
#include "test_movingWallCell.h"



void test_MovingWallCell() {
    MovingWallCell w1(1, 2, 3, 4);

    assert(w1['u'] == 3);
    assert(w1['v'] == 4);

    w1['u'] = 6.f;
    w1['v'] = 7.f;

    assert(w1['u'] == 6);
    assert(w1['v'] == 7);

    assert(w1.get_x() == 1);
    assert(w1.get_y() == 2);
    assert(w1.get_u() == 6);
    assert(w1.get_v() == 7);

    try {
        MovingWallCell w2(-1, 2, 3, 4);
        assert(false);
    } catch (std::invalid_argument& e) {
        assert(std::string(e.what()).find("Invalid coordinates") != std::string::npos);
    }

    try {
        MovingWallCell w3(1, -2, 3, 4);
        assert(false);
    } catch (std::invalid_argument& e) {
        assert(std::string(e.what()).find("Invalid coordinates") != std::string::npos);
    }

    try {
        MovingWallCell w4(-1, -2, 3, 4);
        assert(false);
    } catch (std::invalid_argument& e) {
        assert(std::string(e.what()).find("Invalid coordinates") != std::string::npos);
    }

    const MovingWallCell w5(6, 7, 8, 9);
    assert(w5['x'] == 6);
    assert(w5['y'] == 7);
    assert(w5['u'] == 8);
    assert(w5['v'] == 9);

    MovingWallCell w6(6, 7, 8, 9);
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
    assert(w6['u'] == 8);
    assert(w6['v'] == 9); 
    
}
