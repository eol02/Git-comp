#define _CRT_SECURE_NO_WARNINGS

#include "Storage.h"
#include "common.h"

// 데이터 확인용 함수
void printAllData() {
    printf("\n========== 멤버 목록 (%d명) ==========\n", member_count);
    for (int i = 0; i < member_count; i++) {
        printf("  [%d] %s\n", i + 1, members[i]);
    }

    printf("\n========== 이벤트 목록 (%d건) ==========\n", event_count);
    for (int i = 0; i < event_count; i++) {
        printf(" - %s (결제자: %s)\n", events[i].title, members[events[i].payer]);
        for (int j = 0; j < member_count; j++) {
            if (events[i].participants[j] == 1) {
                printf("   %s : %d원\n", members[j], events[i].costs[j]);
            }
        }
    }
    printf("=======================================\n");
}

// 테스트용 main
int main() {

    add_member("강한얼");
    add_member("김은혁");
    add_member("이경민");

    int idx1[] = {0, 1, 2};
    int cost1[] = {40000, 40000, 40000};
    create_event("여행", 0, idx1, 3, cost1);

    int idx2[] = {0, 2};
    int cost2[] = {15000, 25000};
    create_event("식비", 2, idx2, 2, cost2);

    saveData("fairly_data.txt");

    memset(members, 0, sizeof(members));
    memset(events, 0, sizeof(events));
    member_count = 0;
    event_count = 0;

    if (loadData("fairly_data.txt")) {
        printAllData();
    }

    return 0;
}
