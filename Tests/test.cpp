#include "test_waterCell.h"
#include "test_staticWallCell.h"
#include "test_movingWallCell.h"
#include "test_field.h"

#include <iostream>

int main() {
    test_WaterCell();
    std::cout << "Water cell tests passed" << std::endl;
    test_StaticWallCell();
    std::cout << "Static wall cell tests passed" << std::endl;
    test_MovingWallCell();
    std::cout << "Moving wall cell tests passed" << std::endl;
    test_Field();
    std::cout << "Field tests passed" << std::endl;

    std::cout << "All tests passed" << std::endl;
    return 0;
}