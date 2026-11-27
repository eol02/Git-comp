#include "common.h"

int itemDiscount(int price, int type, int value) {
    if (price <= 0 || (type != 1 && type != 2) || value < 0)
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

int totalDiscount(int costs[], int checks, int type, int value) {
    if (costs == NULL || checks <= 0 || checks > MAX_MEMBERS || (type != 1 && type != 2) || value < 0)
        return -1;

    int total_cost = 0, total_discount = 0;
    for (int i = 0; i < checks; i++) {
        if (costs[i] < 0)
            return -1;
        total_cost += costs[i];
    }

    if (total_cost <= 0)
        return -1;

    if (type == 1) { // 전체 멤버에게 분할 되어야하는 할인 액으로 통일
        if (value > total_cost)
            return -1;
        total_discount = value;
    } else {
        if (value > 100)
            return -1;
        total_discount = (int)(((long long)total_cost * value) / 100);
    }

    // 소비 금액별 비율 분배
    int applied = 0;
    for (int i = 0; i < checks; i++) {
        int share = (int)(((long long)total_discount * costs[i]) / total_cost);
        costs[i] -= share;
        applied += share;
    }

    // 비율 분배 후 남는 금액 처리 (무작위 배분)
    int rem = total_discount - applied;
    if (rem > 0) {
        int start = rand() % checks;
        int step = 0;
        while (rem > 0) {
            int idx = (start + step) % checks;
            if (costs[idx] >= 1) {
                costs[idx] -= 1;
                rem--;
            }
            step++;
        }
    }

    return 0;
}
