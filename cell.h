#ifndef CALCNSMODEL_CELL_H_
#define CALCNSMODEL_CELL_H_


class Cell {
    private:
        int x; // x coordinate in the grid
        int y; // y coordinate in the grid
    public:
        Cell(int x, int y);
        
        const int operator[](char c) const;
};


#endif //CALCNSMODEL_CELL_H_