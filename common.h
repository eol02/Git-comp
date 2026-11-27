#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEMBERS 100
#define MAX_EVENTS 100
#define TITLE_LEN 100
#define NAME_LEN 20

/* --------------- 이벤트 구조체 정의 ---------------- */
typedef struct Event {
    char title[TITLE_LEN]; // 결제 한 장소 혹은 사건의 이름
    int payer; // 결제한 멤버의 인덱스 번호
    int participants[MAX_MEMBERS]; // 멤버별 소비에 참여 여부 (1: 참여, 0: 미참여)
    int costs[MAX_MEMBERS]; // 멤버별 소비한 금액 (인덱스 동기화)
} Event;

/* --------------- 송금 내역 구조체 정의 ---------------- */
typedef struct Transfer {
    int from; // 보내는 멤버 인덱스
    int to; // 받는 멤버 인덱스
    int amount; // 송금 금액
} Transfer;

/* --------------- manager.c --------------- */

extern char members[MAX_MEMBERS][NAME_LEN]; // 전체 멤버 배열
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

/* 이벤트 삭제 함수
- idx: 삭제할 이벤트의 인덱스 값
*/
void delete_event(int idx);

/* 멤버 추가 함수
- name: 추가할 멤버의 이름
*/
void add_member(char name[]);

/* --------------- Calculation.c --------------- */

extern int eventCost[MAX_EVENTS]; // 이벤트별 총 결제 금액 배열
extern Transfer trans[MAX_MEMBERS]; // 송금 내역 배열

int calculate(struct Event *event, int memberCount, int eventCount);
int optimizeTransfers(int memberCount);

/* --------------- Storage.c --------------- */

int saveData(const char *filename);
int loadData(const char *filename);

/* --------------- MemberEdit.c --------------- */

int delete_member(int idx);

/* ---------------- EqualSplit.c --------------- */

/*균등 분할 함수
- total: 분배 금액
- checks: 분배할 인원 수(check된 인원 수)
- costs[]: 분배할 인원들의 금액을 담을 배열(입력시에 기존 누적된 금액을 입력)
- unit: 분배 금액 단위 (잉여 금액의 자릿수) (일단은 1로 고정, 후에 분할 단위를 추가 할 경우 사용)
*/
int equalSplit(int total, int checks, int costs[], int unit);

#endif
