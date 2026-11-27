#include "common.h"

int itemDiscount(int price, int type, int value) {
    if (price < 0 || (type != 1 && type != 2) || value < 0)
        return -1;

    int discount = 0;

    if (type == 1) {
        if (price < value)
            return -1;
        discount = value;
    } else {
        if (value > 100)
            return -1;
        discount = (int)(((long long)price * value) / 100);
    }

    return price - discount;
}
