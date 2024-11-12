#include <cassert>
#include <stdexcept>
#include <string>

#include "params.h"
#include "waterCell.h"



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


}

int main() {
    test_WaterCell();
    return 0;
}
