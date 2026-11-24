#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>

#define MAX_MEMBERS 100
#define MAX_EVENTS 100

/* --------------- 이벤트 구조체 정의 ---------------- */
typedef struct Event {
    char title[MAX_MEMBERS]; // 결제 한 장소 혹은 사건의 이름
    int payer; // 결제한 멤버의 인덱스 번호
    int participants[MAX_MEMBERS]; // 소비에 참여한 멤버의 인덱스 번호
    int costs[MAX_MEMBERS]; // 멤버별 소비한 금액 (인덱스 동기화)
} Event;

/* --------------- manager.c --------------- */

extern char members[MAX_MEMBERS][20]; // 전체 멤버 배열
extern struct Event events[MAX_EVENTS]; // 이벤트 구조체 배열
extern int event_count; // 만든 이벤트 개수
extern int member_count; // 전체 인원 수

/* 이벤트 생성 함수
- payer: 메인 결제자 인덱스(ex.5)
- checks: ui에서 체크된 인원 수(ex.3)
- members_idx[]: ui에서 체크된 인원의 인덱스 번호들(ex.{1,2,4})
- costs[]: members_idx와 같은 순서로 배치된 각각의 금액(ex.{1000,2000,4000}, 즉 1:1000원, 2:2000원, 4:4000원)
*/
void create_event(char title[], int payer, int members_idx[], int checks, int costs[]);

/* 이벤트 수정 함수
- idx: 수정할 이벤트의 인덱스 값
- 나머지 create_event와 인자 동일
*/
void update_event(int idx, char title[], int payer, int members_idx[], int checks, int costs[]);

// 멤버 추가 함수
void add_member(char name[]);

#endif
