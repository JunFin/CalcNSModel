#ifndef CALCNSMODEL_WALLCELL_H_
#define CALCNSMODEL_WALLCELL_H_

#include "cell.h"

#include <string>

class WallCell: public Cell {
    private:
        std::string type;
    public:
        WallCell(int x, int y); // constructor
        
        float operator[](char c) const; // sets the value of the velocity or pressure 
};

#endif //CALCNSMODEL_WALLCELL_H_