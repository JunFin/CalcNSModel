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
        WaterCell(int x, int y, int u, int v, int p): x(x), y(y), u(u), v(v), p(p) {};

        float& operator[](char c); // sets the value of the velocity or pressure
        const int& operator[](char c) const; // returns the value of the coordinate
};

#endif //PROJECT_WATERCELL_H_