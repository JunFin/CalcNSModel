#ifndef PROJECT_WALLCELL_H_
#define PROJECT_WALLCELL_H_

#include "cell.h"

class WallCell: public Cell {
    public:
        WallCell(int x, int y); // constructor
        
        float operator[](char c) const; // sets the value of the velocity or pressure 
};

#endif //PROJECT_WALLCELL_H_