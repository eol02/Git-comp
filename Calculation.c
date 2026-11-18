#include "common.h"

static int totalCost[MAX_MEMBERS] = {0};  //각 멤버별 송금 관계 +-
int eventCost[MAX_EVENTS] = {0};

int calculate(struct Event* event, int memberCount, int eventCount) {    //금액 합산
    int total = 0;

    for(int i = 0; i < memberCount; i++) totalCost[i] = 0;  //각 멤버별 송금 관계 초기화

    for (int i = 0; i < eventCount; i++) {
        total = 0;
        for (int j = 0; j < memberCount; j++) {
            if (event[i].member[j] == 1) {
                total += event[i].cost[j]; //결제에 참여한 멤버만 금액 체크 및 합산
            }
        }
        eventCost[i] = total;  //이벤트별 금액 합산 배열에 추가
        totalCost[event[i].payer] += total;  //결제한 멤버 금액 +
        
        for (int j = 0; j < memberCount; j++) { //결제에 참여한 멤버 금액 -
            if (event[i].member[j] == 1) {
                totalCost[j] -= event[i].cost[j];
            }
        }
    }

    return 0;
}

// int optimizeTransfers(struct Event* event, int eventCount, int memberCount) {  //송금 관계 최적화
//     int expense[MAX_MEMBERS] = {0};  //각 멤버별 송금 관계 +-
//     int* totalCost;

//     for (int i = 0; i < eventCount; i++) {
//         totalCost = calculateTotalCost(&event[i], memberCount);

//         for (int j = 0; j < memberCount; j++) { //결제한 멤버들 금액 +
//             expense[j] += totalCost[j];
//         }
//     }
// }