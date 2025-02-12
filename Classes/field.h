#ifndef CALCNSMODEL_FIELD_H_
#define CALCNSMODEL_FIELD_H_

#include "../Settings/params.h"
#include "cell.h"

#include <vector>
#include <memory>

class Field {
    private:
        int xSize;  // number of cells in the x direction
        int ySize;  // number of cells in the y direction
        std::vector<std::vector<std::unique_ptr<Cell> > > field;  // 2D array of cells
    public:
        Field(int xSize, int ySize);
        Field* create_field(int xSize, int ySize);  // constructor for python
        Field(Field&& other) noexcept;  // move constructor

        Field& operator=(Field&& other) noexcept;  // move assignment

        void set_xSize(int xSize);  // set the number of cells in the x direction
        void set_ySize(int ySize);  // set the number of cells in the y direction
        int get_xSize() const;  // get the number of cells in the x direction
        int get_ySize() const;  // get the number of cells in the y direction
        void set_cell(int x, int y, std::unique_ptr<Cell> cell);  // set the value of a cell at position (x, y)
        Cell* get_cell(int x, int y);  // get the value of a cell at position (x, y)

        void display(Field*);  // display the field
        void display_without_walls(Field*);  // display the field
        void display_test(Field*);  // display the field for test with full description of cells
        void update(Field*);  // update the field
};



#endif //CALCNSMODEL_FIELD_H_