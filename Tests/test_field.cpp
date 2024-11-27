#include "../Classes/field.h"
#include "../Classes/cell.h"
#include "test_field.h"

#include <cassert>

void test_Field() {
    Field field(2, 2);

    for (int x = 0; x < field.get_xSize(); x++) {
        for (int y = 0; y < field.get_ySize(); y++) {
            field.set_cell(x, y, new Cell(x, y));
        }
    }

    for (int x = 0; x < field.get_xSize(); x++) {
        for (int y = 0; y < field.get_ySize(); y++) {
            assert(field.get_cell(x, y).get_x() == x);
            assert(field.get_cell(x, y).get_y() == y);
        }
    }

    field.display();
}