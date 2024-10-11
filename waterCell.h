#ifndef PROJECT_WATERCELL_H_
#define PROJECT_WATERCELL_H_

class WaterCell{
    private:
        int x; // x coordinate in the grid
        int y; // y coordinate in the grid
        float u; // x velocity
        float v; // y velocity
        float p; // pressure
    public:
        WaterCell(int x, int y, float u, float v, float p); // constructor
        
        float& operator[](char c); // sets the value of the velocity or pressure 

        int get_x(); // returns the x coordinate
        int get_y(); // returns the y coordinate
        float get_u(); // returns the x velocity
        float get_v(); // returns the y velocity
        float get_p(); // returns the pressure
};

#endif //PROJECT_WATERCELL_H_