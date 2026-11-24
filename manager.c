#include "common.h"

char members[MAX_MEMBERS][20]; // 전체 멤버
struct Event events[MAX_EVENTS]; // 이벤트 구조체 배열
int event_count = 0; // 만든 이벤트 개수
int member_count = 0; // 전체 인원 수

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

/* 이벤트 수정 함수
- idx: 수정할 이벤트의 인덱스 값
- 나머지 create_event와 인자 동일
*/
void update_event(int idx, char title[], int payer, int members_idx[], int checks, int costs[]) {

    // 기존 참여자 및 금액 초기화
    memset(events[idx].participants, 0, sizeof(events[idx].participants));
    memset(events[idx].costs, 0, sizeof(events[idx].costs));

    strcpy(events[idx].title, title); // title 지정
    events[idx].payer = payer; // payer 지정

    // events.participants에 members의 인덱스 기준으로 참여여부(1:참여)와 각각의 금액 갱신
    for (int i = 0; i < checks; i++) {
        int m_idx = members_idx[i];
        events[idx].participants[m_idx] = 1;
        events[idx].costs[m_idx] = costs[i];
    }
}

// 전체 멤버 추가 함수
void add_member(char name[]) {
    int idx = member_count++;
    strcpy(members[idx], name);
}
