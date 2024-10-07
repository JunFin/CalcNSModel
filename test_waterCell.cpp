#include <cassert>

#include "params.h"
#include "waterCell.h"

void test_WaterCell() {
    WaterCell w1(1, 2, 3, 4, 5);

    assert(w1['u'] == 3);
    assert(w1['v'] == 4);
    assert(w1['p'] == 5);

    w1['u'] = 6.f;
    w1['v'] = 7.f;
    w1['p'] = 8.f;

    assert(w1['u'] == 6);
    assert(w1['v'] == 7);
    assert(w1['p'] == 8);


}

int main() {
    test_WaterCell();
    return 0;
}
