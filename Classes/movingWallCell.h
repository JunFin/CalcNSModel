#ifndef CALCNSMODEL_MOVINGWALLCELL_H_
#define CALCNSMODEL_MOVINGWALLCELL_H_

#include "wallCell.h"

#include <string>
#include <memory>

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

        void set_u(float u); // sets the x velocity
        void set_v(float v); // sets the y velocity

        std::string get_description() const override;

        std::unique_ptr<Cell> copy() const override;


};

#endif //CALCNSMODEL_MOVINGWALLCELL_H_
