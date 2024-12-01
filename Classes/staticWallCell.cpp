#include "staticWallCell.h"
#include "../Settings/params.h"

#include <stdexcept>
#include <memory>


StaticWallCell::StaticWallCell(int x, int y):WallCell(x, y) {
    this->set_type("StaticWall");
}

std::unique_ptr<Cell> StaticWallCell::copy() const {
    return std::make_unique<StaticWallCell>(*this);
}
