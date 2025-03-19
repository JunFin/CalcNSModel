#include "Classes/field.h"
#include "Classes/cell.h"
#include "Classes/waterCell.h"
#include "Classes/movingWallCell.h"
#include "Classes/staticWallCell.h"
#include "Settings/params.h"

#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <memory>


extern "C" {


Field* initialize_field() {
    Field * field = new Field(XGridSize,YGridSize);
    std::ifstream file(FileName);
    if (!file.is_open()) {
        delete field;
        return NULL; //throw std::runtime_error("Failed to open file: " + std::string(FileName));
    }
    for (int y = 0; y < YGridSize; y++) {
        for (int x = 0; x < XGridSize; x++) {
            char c = file.get();
            if (file.eof()) {
                break;
            }
            if (!file) {
                delete field;
                return NULL;
                //throw std::runtime_error("Failed to read file: " + std::string(FileName) + " or file is wrong");
            }
            switch (c) {
                case 's': field->set_cell(x, y, std::make_unique<StaticWallCell>(x, y)); break;
                case 'm': field->set_cell(x, y, std::make_unique<MovingWallCell>(x, y, 1, 0)); break;
                case 'w': field->set_cell(x, y, std::make_unique<WaterCell>(x, y, 0, 0, 0));  break;
                case '\n': x--; break;
                default: delete field; return NULL; //throw std::runtime_error("Invalid character in file: " + std::string(FileName));
            }
        }
    }
    return field;
    }


    
    int get_x(Cell* cell) {
        return cell->get_x();
    }

    int get_y(Cell* cell) {
        return cell->get_y();
    }

    const char* get_type(Cell* cell) {
        return cell->get_type().c_str();
    }
    


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

    Cell* get_cell(Field* field, int x, int y) {
        return field->get_cell(x, y);
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


    float get_u(WaterCell* cell) {
        return cell->get_u();
    }

    float get_v(WaterCell* cell) {
        return cell->get_v();
    }

    float get_p(WaterCell* cell) {
        return cell->get_p();
    }


}