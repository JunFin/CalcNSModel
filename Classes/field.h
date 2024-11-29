#ifndef CALCNSMODEL_FIELD_H_
#define CALCNSMODEL_FIELD_H_

#include "../Settings/params.h"
#include "cell.h"

#include <vector>

class Field {
    private:
        int xSize;  // number of cells in the x direction
        int ySize;  // number of cells in the y direction
        std::vector<std::vector<Cell*> > field;  // 2D array of cells
    public:
        Field(int xSize, int ySize);  // constructor
        ~Field();  // destructor

        int get_xSize() const;  // get the number of cells in the x direction
        int get_ySize() const;  // get the number of cells in the y direction
        void set_cell(int x, int y, Cell* cell);  // set the value of a cell at position (x, y)
        Cell* get_cell(int x, int y);  // get the value of a cell at position (x, y)

        void display();  // display the field
        void display_test();  // display the field for test with full description of cells
        void update();  // update the field
};



#endif //CALCNSMODEL_FIELD_H_