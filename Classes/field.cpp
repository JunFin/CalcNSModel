#include "field.h"
#include "cell.h"
#include "waterCell.h"
#include "movingWallCell.h"
#include "staticWallCell.h"

#include <vector>
#include <stdexcept>
#include <iostream>
#include <memory>




Field::Field(int xSize, int ySize) {
    if (xSize <= 0 || ySize <= 0) {
        throw std::invalid_argument("Field dimensions must be positive integers");
    }
    this->xSize = xSize;
    this->ySize = ySize;
    this->field = std::vector<std::vector<std::unique_ptr<Cell>>>(xSize);
    for (int x = 0; x < xSize; x++) {
        this->field[x] = std::vector<std::unique_ptr<Cell>>(ySize);
        for (int y = 0; y < ySize; y++) {
            set_cell(x, y, std::make_unique<Cell>(x, y));
        }
    }
}

Field::Field(Field&& other) noexcept  // move constructor
    : xSize(other.xSize), ySize(other.ySize), field(std::move(other.field)) {
    other.xSize = 0;
    other.ySize = 0;
}

Field& Field::operator=(Field&& other) noexcept {  // move assignment
    if (this != &other) {
        xSize = other.xSize;
        ySize = other.ySize;
        field = std::move(other.field);

        other.xSize = 0;
        other.ySize = 0;
    }
    return *this;
}


void Field::set_xSize(int xSize) {
    if (xSize <= 0) {
        throw std::invalid_argument("Field dimensions must be positive integers");
    }
    this->xSize = xSize;
}

void Field::set_ySize(int ySize) {
    if (ySize <= 0) {
        throw std::invalid_argument("Field dimensions must be positive integers");
    }
    this->ySize = ySize;
}


int Field::get_xSize() const {
    return xSize;
}

int Field::get_ySize() const {
    return ySize;
}

void Field::set_cell(int x, int y, std::unique_ptr<Cell> cell) {
    if (x < 0 || y < 0 || x >= xSize || y >= ySize) {
        throw std::invalid_argument("Invalid coordinates");
    }
    field[x][y] = std::move(cell);
}


Cell* Field::get_cell(int x, int y) {
    if (x < 0 || x >= xSize || y < 0 || y >= ySize) {
        throw std::invalid_argument("Invalid coordinates");
    }
    return field[x][y].get();
}




extern "C" {

    Field* create_field(int xSize, int ySize) {
            
        if (xSize <= 0 || ySize <= 0) {
            throw std::invalid_argument("Field dimensions must be positive integers");
        }

        Field* field = new Field(xSize, ySize);

        field->set_xSize(xSize);
        field->set_ySize(ySize);
        for (int x = 0; x < xSize; x++) {
            for (int y = 0; y < ySize; y++) {
                field->set_cell(x, y, std::make_unique<Cell>(x, y));
            }
        }

        return field;
    }





    void display(Field* field) {
        for (int i = 0; i < 4 * field->get_xSize() + 1; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;

        for (int y = 0; y < field->get_ySize(); y++) {
            std::cout << "|";
            for (int x = 0; x < field->get_xSize(); x++) {
                std::cout << " " << field->get_cell(x, y)->get_description() << " |";
            }
            std::cout << std::endl;

            for (int i = 0; i < 4 * field->get_xSize() + 1; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;
        }
    }

    void display_without_walls(Field* field) {
        for (int y = 0; y < field->get_ySize(); y++) {
            for (int x = 0; x < field->get_xSize(); x++) {
                std::cout << field->get_cell(x, y)->get_description();
            }
            std::cout << std::endl;
        }
    }


    void display_test(Field* field) {
        for (int y = 0; y < field->get_ySize(); y++) {
            for (int x = 0; x < field->get_xSize(); x++) {
                std::cout << "| " << field->get_cell(x, y)->get_description_test() << " ";
            }
            std::cout << "|" << std::endl;
        }
    }

    void update(Field* field) {
        std::vector<std::vector<std::vector<int> > > changes = std::vector<std::vector<std::vector<int> > >(field->get_xSize(), std::vector<std::vector<int> >(field->get_ySize(), std::vector<int>(2, 0)));
        for (int x = 0; x < field->get_xSize(); x++) {
            for (int y = 0; y < field->get_ySize(); y++) {
                std::string type = field->get_cell(x, y)->get_type();
                if (type == "Water") {
                    WaterCell* cell = dynamic_cast<WaterCell*>(field->get_cell(x, y));
                    float u = cell->get_u();
                    float v = cell->get_v();
                    if (u > 0 && v == 0) {
                        if (x < field->get_xSize() - 1) {
                            if (field->get_cell(x + 1, y)->get_type() == "StaticWall" || field->get_cell(x + 1, y)->get_type() == "MovingWall") {
                                changes[x][y][0] += -u;
                            }
                            if (field->get_cell(x + 1, y)->get_type() == "Water") {
                                changes[x + 1][y][0] += u;
                            }
                        }
                    }
                    if (u < 0 && v == 0) {
                        if (x > 0) {
                            if (field->get_cell(x - 1, y)->get_type() == "StaticWall" || field->get_cell(x - 1, y)->get_type() == "MovingWall") {
                                changes[x][y][0] += -u;
                            }
                            if (field->get_cell(x - 1, y)->get_type() == "Water") {
                                changes[x - 1][y][0] += u;
                            }
                        }
                    }
                    if (u == 0 && v > 0) {
                        if (y < field->get_ySize() - 1) {
                            if (field->get_cell(x, y + 1)->get_type() == "StaticWall" || field->get_cell(x, y + 1)->get_type() == "MovingWall") {
                                changes[x][y][1] += -v;
                            }
                            if (field->get_cell(x, y + 1)->get_type() == "Water") {
                                changes[x][y + 1][1] += v;
                            }
                        }
                    }
                    if (u == 0 && v < 0) {
                        if (y > 0) {
                            if (field->get_cell(x, y - 1)->get_type() == "StaticWall" || field->get_cell(x, y - 1)->get_type() == "MovingWall") {
                                changes[x][y][1] += -v;
                            }
                            if (field->get_cell(x, y - 1)->get_type() == "Water") {
                                changes[x][y - 1][1] += v;
                            }
                        }
                    }
                    if (u > 0 && v > 0) {
                        if (x < field->get_xSize() - 1 && y < field->get_ySize() - 1) {
                            if (field->get_cell(x + 1, y + 1)->get_type() == "StaticWall" || field->get_cell(x + 1, y + 1)->get_type() == "MovingWall") {
                                changes[x][y][0] += -u;
                                changes[x][y][1] += -v;
                            }
                            if (field->get_cell(x + 1, y + 1)->get_type() == "Water") {
                                changes[x + 1][y + 1][0] += u;
                                changes[x + 1][y + 1][1] += v;
                            }
                        }
                    }
                    if (u < 0 && v < 0) {
                        if (x > 0 && y > 0) {
                            if (field->get_cell(x - 1, y - 1)->get_type() == "StaticWall" || field->get_cell(x - 1, y - 1)->get_type() == "MovingWall") {
                                changes[x][y][0] += -u;
                                changes[x][y][1] += -v;
                            }
                            if (field->get_cell(x - 1, y - 1)->get_type() == "Water") {
                                changes[x - 1][y - 1][0] += u;
                                changes[x - 1][y - 1][1] += v;
                            }
                        }
                    }
                    if (u > 0 && v < 0) {
                        if (x < field->get_xSize() - 1 && y > 0) {
                            if (field->get_cell(x + 1, y - 1)->get_type() == "StaticWall" || field->get_cell(x + 1, y - 1)->get_type() == "MovingWall") {
                                changes[x][y][0] += -u;
                                changes[x][y][1] += -v;
                            }
                            if (field->get_cell(x + 1, y - 1)->get_type() == "Water") {
                                changes[x + 1][y - 1][0] += u;
                                changes[x + 1][y - 1][1] += v;
                            }
                        }
                    }
                    if (u < 0 && v > 0) {
                        if (x > 0 && y < field->get_ySize() - 1) {
                            if (field->get_cell(x - 1, y + 1)->get_type() == "StaticWall" || field->get_cell(x - 1, y + 1)->get_type() == "MovingWall") {
                                changes[x][y][0] += -u;
                                changes[x][y][1] += -v;
                            }
                            if (field->get_cell(x - 1, y + 1)->get_type() == "Water") {
                                changes[x - 1][y + 1][0] += u;
                                changes[x - 1][y + 1][1] += v;
                            }
                        }
                    }

                }

                if (type == "MovingWall") {
                    MovingWallCell* cell = dynamic_cast<MovingWallCell*>(field->get_cell(x, y));
                    float u = cell->get_u();
                    float v = cell->get_v();
                    if (u > 0 && v == 0) {
                        if (x < field->get_xSize() - 1) {
                            if (field->get_cell(x + 1, y)->get_type() == "Water") {
                                changes[x + 1][y][0] += u;
                            }
                        }
                    }
                    if (u < 0 && v == 0) {
                        if (x > 0) {
                            if (field->get_cell(x - 1, y)->get_type() == "Water") {
                                changes[x - 1][y][0] += u;
                            }
                        }
                    }
                    if (u == 0 && v > 0) {
                        if (y < field->get_ySize() - 1) {
                            if (field->get_cell(x, y + 1)->get_type() == "Water") {
                                changes[x][y + 1][1] += v;
                            }
                        }
                    }
                    if (u == 0 && v < 0) {
                        if (y > 0) {
                            if (field->get_cell(x, y - 1)->get_type() == "Water") {
                                changes[x][y - 1][1] += v;
                            }
                        }
                    }
                    if (u > 0 && v > 0) {
                        if (x < field->get_xSize() - 1 && y < field->get_ySize() - 1) {
                            if (field->get_cell(x + 1, y + 1)->get_type() == "Water") {
                                changes[x + 1][y + 1][0] += u;
                                changes[x + 1][y + 1][1] += v;
                            }
                        }
                    }
                    if (u < 0 && v < 0) {
                        if (x > 0 && y > 0) {
                            if (field->get_cell(x - 1, y - 1)->get_type() == "Water") {
                                changes[x - 1][y - 1][0] += u;
                                changes[x - 1][y - 1][1] += v;
                            }
                        }
                    }
                    if (u > 0 && v < 0) {
                        if (x < field->get_xSize() - 1 && y > 0) {
                            if (field->get_cell(x + 1, y - 1)->get_type() == "Water") {
                                changes[x + 1][y - 1][0] += u;
                                changes[x + 1][y - 1][1] += v;
                            }
                        }
                    }
                    if (u < 0 && v > 0) {
                        if (x > 0 && y < field->get_ySize() - 1) {
                            if (field->get_cell(x - 1, y + 1)->get_type() == "Water") {
                                changes[x - 1][y + 1][0] += u;
                                changes[x - 1][y + 1][1] += v;
                            }
                        }
                    }
                    cell->set_u(0);
                    cell->set_v(0);
                }
            }
        }

        for (int x = 0; x < field->get_xSize(); x++) {
            for (int y = 0; y < field->get_ySize(); y++) {
                if (field->get_cell(x, y)->get_type() == "Water") {
                    WaterCell* cell = dynamic_cast<WaterCell*>(field->get_cell(x, y));
                    cell->set_u(changes[x][y][0]);
                    cell->set_v(changes[x][y][1]);
                }
            }
        }


    }


}