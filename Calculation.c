#include "common.h"

int totalCost[MAX_MEMBERS] = {0};  //각 멤버별 송금 관계 +-
int eventCost[MAX_EVENTS] = {0};
Transfer trans[MAX_MEMBERS];

int calculate(struct Event* event, int memberCount, int eventCount) {    //금액 합산
    int total = 0;

    for(int i = 0; i < memberCount; i++) totalCost[i] = 0;  //각 멤버별 송금 관계 초기화

    for (int i = 0; i < eventCount; i++) {
        total = 0;
        for (int j = 0; j < memberCount; j++) {
            if (event[i].participants[j] == 1) {
                total += event[i].costs[j]; //결제에 참여한 멤버만 금액 체크 및 합산
            }
        }
        eventCost[i] = total;  //이벤트별 금액 합산 배열에 추가
        totalCost[event[i].payer] += total;  //결제한 멤버 금액 +
        
        for (int j = 0; j < memberCount; j++) { //결제에 참여한 멤버 금액 -
            if (event[i].participants[j] == 1) {
                totalCost[j] -= event[i].costs[j];
            }
        }
    }

    return 0;
}

int optimizeTransfers(int memberCount){
    int count = 0;
    int balance[MAX_MEMBERS] = {0};

    for (int i = 0; i < memberCount; i++) balance[i] = totalCost[i];

    for (int i = 0; i< memberCount; i++) {
        if (balance[i] <= 0) continue;    //송금할 금액이 없는 멤버는 건너뜀
        for (int j = 0; j < memberCount; j++) {
            if (balance[j] == -balance[i]) {    //받을 돈 줄 돈이 1:1인 경우
                trans[count].from = j;
                trans[count].to = i;
                trans[count].amount = balance[i];
                count++;
                balance[i] = 0;
                balance[j] = 0;
                break;
            }
        }
    }

    while (1) {
        int t = -1, f = -1;  //t: 받아야하는 멤버, f: 보내야하는 멤버
        for (int i = 0; i < memberCount; i++) { //최대 금액을 보내야하는 멤버와 받아야하는 멤버 탐색
            if (balance[i] > 0 && (t == -1 || balance[i] > balance[t])) t = i;
            if (balance[i] < 0 && (f == -1 || balance[i] < balance[f])) f = i;
        }
        if (t == -1 || f == -1) break;  //더 이상 송금할 멤버가 없는 경우 종료

        int amt = (balance[t] < -balance[f]) ? balance[t] : -balance[f];  //송금 금액 결정
        trans[count].from = f;
        trans[count].to = t;
        trans[count].amount = amt;
        count++;
        balance[t] -= amt;  //송금 후 금액 업데이트
        balance[f] += amt;
    }

    return count;   //송금 횟수 반환
}