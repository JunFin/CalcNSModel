#ifndef CALCNSMODEL_STATICWALLCELL_H_
#define CALCNSMODEL_STATICWALLCELL_H_

#include "wallCell.h"

#include <string>
#include <memory>

class StaticWallCell: public WallCell {
    private:
        std::string type;
    public:
        StaticWallCell(int x, int y); // constructor
        std::unique_ptr<Cell> copy() const override;

};

#endif //CALCNSMODEL_STATICWALLCELL_H_
