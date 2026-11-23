#define _CRT_SECURE_NO_WARNINGS

#include "Storage.h"
#include "common.h"

// manager.c 없이 Storage.c만 테스트하려고 여기서 임시로 정의
char members[MAX_MEMBERS][20];
struct Event events[MAX_EVENTS];
int member_count = 0;
int event_count = 0;

// 데이터 확인용 함수
void printAllData() {
    printf("\n========== 멤버 목록 (%d명) ==========\n", member_count);
    for (int i = 0; i < member_count; i++) {
        printf("  [%d] %s\n", i + 1, members[i]);
    }

    printf("\n========== 이벤트 목록 (%d건) ==========\n", event_count);
    for (int i = 0; i < event_count; i++) {
        printf(" - %s (결제자: %s)\n", events[i].title, members[events[i].payer]);
        for (int j = 0; j < events[i].count; j++) {
            int idx = events[i].participants[j];
            printf("   %s : %d원\n", members[idx], events[i].costs[j]);
        }
    }
    printf("=======================================\n");
}

// 테스트용 main
int main() {

    strcpy(members[0], "강한얼");
    strcpy(members[1], "김은혁");
    strcpy(members[2], "이경민");
    member_count = 3;

    strcpy(events[0].title, "여행");
    events[0].payer = 0;
    events[0].count = 3;
    events[0].participants[0] = 0;
    events[0].participants[1] = 1;
    events[0].participants[2] = 2;
    events[0].costs[0] = 40000;
    events[0].costs[1] = 40000;
    events[0].costs[2] = 40000;
    event_count = 1;

    saveData("fairly_data.txt");

    member_count = 0;
    event_count = 0;

    if (loadData("fairly_data.txt")) {
        printAllData();
    }

    return 0;
}
