#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>

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

/* --------------- Session.c --------------- */

#define MAX_SESSIONS 20

typedef struct Session {
    char name[NAME_LEN];
    char members[MAX_MEMBERS][NAME_LEN];
    Event events[MAX_EVENTS];
    int member_count;
    int event_count;
} Session;

extern Session sessions[MAX_SESSIONS]; // 전체 세션 배열
extern int session_count; // 전체 세션 개수
extern int current_session; // 현재 선택된 세션 번호

void save_to_session(int idx);
void load_from_session(int idx);
int create_session(char name[]);
void print_session_list(void);
int select_session(int index);
int save_current_session(void);
int load_session(const char *filename, char name[]);

#endif
