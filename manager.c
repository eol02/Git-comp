#include "common.h"

char members[MAX_MEMBERS][20]; // 전체 멤버
struct Event events[MAX_EVENTS]; // 이벤트 구조체 배열
int event_count = 0; // 만든 이벤트 개수
int member_count = 0; // 전체 인원 수

/* --------------- EVENT --------------- */

void create_event(char title[], int payer, int members_idx[], int checks, int costs[]) {
    int idx = event_count++;
    update_event(idx, title, payer, members_idx, checks, costs);
}

void update_event(int idx, char title[], int payer, int members_idx[], int checks, int costs[]) {
    // 기존 이벤트의 참여자 및 금액 배열 초기화
    memset(events[idx].participants, 0, sizeof(events[idx].participants));
    memset(events[idx].costs, 0, sizeof(events[idx].costs));

    strcpy(events[idx].title, title);
    events[idx].payer = payer;

    // 체크된 멤버의 참여 여부(1:참여)와 금액 갱신
    for (int i = 0; i < checks; i++) {
        int m_idx = members_idx[i];
        events[idx].participants[m_idx] = 1;
        events[idx].costs[m_idx] = costs[i];
    }
}

void delete_event(int idx) {
    // 삭제한 위치 뒤의 이벤트들을 한 칸씩 앞으로 이동
    for (int i = idx; i < event_count - 1; i++) {
        events[i] = events[i + 1];
    }
    event_count--;
}

/* --------------- MEMBER --------------- */

void add_member(char name[]) {
    int idx = member_count++;
    strcpy(members[idx], name);
}
