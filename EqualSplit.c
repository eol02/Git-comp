#include "common.h"

int equalSplit(int total, int checks, int costs[], int unit) {
    if (total <= 0 || checks <= 0 || unit != 1)
        return -1;

    int base = (total / checks / unit) * unit; // 분배 금액
    int rem = total - (base * checks); // 나머지 금액

    for (int i = 0; i < checks; i++)
        costs[i] += base;

    if (rem > 0) {
        int i = rand() % checks; // 나머지 금액을 랜덤하게 분배. unit이 1인 기준.
        for (int j = 0; j < rem; j++)
            costs[(i + j) % checks] += 1;
    }

    return 0;
}
