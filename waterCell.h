#ifndef PROJECT_WATERCELL_H_
#define PROJECT_WATERCELL_H_

class WaterCell{
    private:
        int x; // x coordinate
        int y; // y coordinate
        int u; // x velocity
        int v; // y velocity
        int p; // pressure
    public:
        WaterCell(int x, int y, int u, int v, int p): x(x), y(y), u(u), v(v), p(p) {};
        inline int getX() const {return x;}; // returns x coordinate
        inline int getY() const {return y;}; // returns y coordinate
        inline int getU() const {return u;}; // returns x velocity
        inline int getV() const {return v;}; // returns y velocity
        inline int getP() const {return p;}; // returns pressure

        void setX(int x); // sets x coordinate
        void setY(int y); // sets y coordinate
        void setU(int u); // sets x velocity
        void setV(int v); // sets y velocity
        void setP(int p); // sets pressure
};

#endif //PROJECT_WATERCELL_H_