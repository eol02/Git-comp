#include <stdio.h>
#include <string.h>
#define MAX 100

struct Event {
    char title[MAX]; // 결제 한 장소 혹은 사건의 이름
    int payer; // 결제한 멤버의 인덱스 번호
    int participants[MAX]; // 소비에 참여한 멤버 여부 (0: 미참여, 1: 참여)
    int costs[MAX]; // 멤버별 소비한 금액 (인덱스 동기화)
};

char members[MAX][20]; // 전체 멤버
struct Event events[MAX]; // 이벤트 구조체 배열
int event_count = 0; // 만든 이벤트 개수

void create_event(char title[], int payer, int members_idx[], int checks, int costs[]);

int main() {
    return 0;
}

/* 이벤트 생성 함수
- checks: ui에서 체크된 인원 수(ex.3)
- members_idx[]: ui에서 체크된 인원의 인덱스 번호들(ex.{1,2,4})
- costs[]: members_idx와 같은 순서로 배치된 각각의 금액(ex.{1000,2000,4000}, 즉 1:1000원, 2:2000원, 4:4000원)
*/
void create_event(char title[], int payer, int members_idx[], int checks, int costs[]) {
    int idx = event_count++; // 새로운 이벤트 인덱스 할당 및 개수 증가

    strcpy(events[idx].title, title); // title 지정
    events[idx].payer = payer; // payer 지정

    // events.member에 members의 인덱스 기준으로 참여여부(1:참여)와 각각의 금액 추가
    for (int i = 0; i < checks; i++) {
        int m_idx = members_idx[i];
        events[idx].participants[m_idx] = 1;
        events[idx].costs[m_idx] = costs[i];
    }
}
