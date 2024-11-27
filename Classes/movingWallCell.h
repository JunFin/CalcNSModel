#ifndef CALCNSMODEL_MOVINGWALLCELL_H_
#define CALCNSMODEL_MOVINGWALLCELL_H_

#include "wallCell.h"

#include <string>

class MovingWallCell: public WallCell {
    private:
        float u; // x velocity
        float v; // y velocity
        std::string type;
    public:
        MovingWallCell(int x, int y, float u, float v); // constructor
        
        float& operator[](char c); // sets the value of the velocity or pressure 
        float operator[](char c) const; // sets the value of the velocity or pressure 

        float get_u(); // returns the x velocity
        float get_v(); // returns the y velocity
};

#endif //CALCNSMODEL_MOVINGWALLCELL_H_
