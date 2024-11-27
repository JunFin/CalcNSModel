#include "staticWallCell.h"
#include "../Settings/params.h"

#include <stdexcept>


StaticWallCell::StaticWallCell(int x, int y):WallCell(x, y) {
    this->type = "StaticWall";
}

