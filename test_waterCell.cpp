#include <cassert>

#include "waterCell.h"

void test_WaterCell() {
    WaterCell w1(3, 4, 5, 6, 7);
    assert(w1.getX() == 3);
    assert(w1.getY() == 4);
    assert(w1.getU() == 5);
    assert(w1.getV() == 6);
    assert(w1.getP() == 7);
    w1.setX(8);
    w1.setY(9);
    w1.setU(10);
    w1.setV(11);
    w1.setP(12);
    assert(w1.getX() == 8);
    assert(w1.getY() == 9);
    assert(w1.getU() == 10);
    assert(w1.getV() == 11);
    assert(w1.getP() == 12);
}

int main() {
    test_WaterCell();
    return 0;
}
