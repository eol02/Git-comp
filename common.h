#ifndef COMMON_H
#define COMMON_H

#define MAX_MEMBERS 100
#define MAX_EVENTS 100

/*---------------이벤트 구조체 정의----------------*/
typedef struct Event {
    char title[MAX_MEMBERS];    //결제 한 장소 혹은 사건의 이름
    int payer;                  //결제한 멤버의 인덱스 번호
    int member[MAX_MEMBERS];    //소비에 참여한 멤버의 인덱스 번호
    int cost[MAX_MEMBERS];      //멤버별 소비한 금액 (인덱스 동기화)
} Event;

extern char members[MAX_MEMBERS][20];   //전체 멤버 배열
extern int eventCost[MAX_EVENTS];  //이벤트별 금액 합산 배열

//Calculation.c
int calculate(struct Event* event, int memberCount, int eventCount);

#endif