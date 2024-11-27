#include "test_waterCell.h"
#include "test_staticWallCell.h"
#include "test_movingWallCell.h"
#include "test_field.h"

#include <iostream>

int main() {
    test_WaterCell();
    test_StaticWallCell();
    test_MovingWallCell();
    test_Field();
    std::cout << "All tests passed" << std::endl;
    return 0;
}