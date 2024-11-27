#ifndef CALCNSMODEL_STATICWALLCELL_H_
#define CALCNSMODEL_STATICWALLCELL_H_

#include "wallCell.h"

#include <string>

class StaticWallCell: public WallCell {
    private:
        std::string type;
    public:
        StaticWallCell(int x, int y); // constructor
};

#endif //CALCNSMODEL_STATICWALLCELL_H_
