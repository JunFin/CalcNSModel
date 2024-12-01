#ifndef CALCNSMODEL_CELL_H_
#define CALCNSMODEL_CELL_H_

#include <string>
#include <memory>

class Cell {
    private:
        int x; // x coordinate in the grid
        int y; // y coordinate in the grid
        std::string type;
    public:
        Cell(int x, int y);  // constructor
        virtual ~Cell();  // destructor
        int get_x() const; // returns the x coordinate
        int get_y() const; // returns the y coordinate
        float operator[](char c) const;

        std::string get_type() const;  // returns the type of the cell

        virtual std::string get_description() const;  // returns the description of the cell
        std::string get_description_test() const;  // returns the description of the cell for test with full information
        virtual std::unique_ptr<Cell> copy() const;  // returns a copy of the cell
    
    protected:
        void set_type(std::string type);
};


#endif //CALCNSMODEL_CELL_H_
