#ifndef CALCNSMODEL_WATERCELL_H_
#define CALCNSMODEL_WATERCELL_H_

#include "cell.h"
#include <string>

class WaterCell: public Cell {
    private:
        float u; // x velocity
        float v; // y velocity
        float p; // pressure
        std::string type;
    public:
        WaterCell(int x, int y, float u, float v, float p); // constructor
        
        float& operator[](char c); // sets the value of the velocity or pressure
        float operator[](char c) const; // sets the value of the velocity or pressure 

        float get_u(); // returns the x velocity
        float get_v(); // returns the y velocity
        float get_p(); // returns the pressure

        void set_u(float u); // sets the x velocity
        void set_v(float v); // sets the y velocity
        void set_p(float p); // sets the pressure

        std::string get_description() const override;
};

#endif //CALCNSMODEL_WATERCELL_H_
