#include "common.h"

Session sessions[MAX_SESSIONS];
int session_count = 0;
int current_session = -1;

// 세션 생성
int create_session(char name[]) {

    if (session_count >= MAX_SESSIONS) {
        printf("더 이상 세션을 만들 수 없습니다.\n");
        return 0;
    }

    if (current_session != -1) {
        save_to_session(current_session);
    }

    strcpy(sessions[session_count].name, name);
    sessions[session_count].member_count = 0;
    sessions[session_count].event_count = 0;

    current_session = session_count;
    session_count++;

    member_count = 0;
    event_count = 0;

    printf("'%s' 세션이 생성되었습니다. (번호: %d)\n", name, current_session + 1);
    return 1;
}

// 지금 쓰고 있는 멤버/이벤트를 idx번 세션 자리에 저장
void save_to_session(int idx) {
    for (int i = 0; i < member_count; i++) {
        strcpy(sessions[idx].members[i], members[i]);
    }

    for (int i = 0; i < event_count; i++) {
        sessions[idx].events[i] = events[i];
    }

    sessions[idx].member_count = member_count;
    sessions[idx].event_count = event_count;
}

// idx번 세션에 든 내용을 멤버/이벤트로 꺼내옴
void load_from_session(int idx) {
    member_count = sessions[idx].member_count;
    event_count = sessions[idx].event_count;

    for (int i = 0; i < member_count; i++) {
        strcpy(members[i], sessions[idx].members[i]);
    }

    for (int i = 0; i < event_count; i++) {
        events[i] = sessions[idx].events[i];
    }
}

// 세션 목록 출력
void print_session_list(void) {
    printf("\n===== 세션 목록 =====\n");
    for (int i = 0; i < session_count; i++) {
        printf("[%d] %s\n", i + 1, sessions[i].name);
    }
}

// index번째 세션으로 전환
int select_session(int index) {
    int idx = index - 1;

    if (idx < 0 || idx >= session_count) {
        printf("잘못된 세션 번호입니다.\n");
        return 0;
    }

    if (current_session != -1) {
        save_to_session(current_session);
    }

    load_from_session(idx);
    current_session = idx;

    printf("'%s' 세션으로 전환되었습니다.\n", sessions[idx].name);
    return 1;
}

// 현재 세션을 파일로 저장
int save_current_session(void) {
    char filename[30];

    if (current_session == -1) {
        printf("저장할 세션이 없습니다.\n");
        return 0;
    }

    save_to_session(current_session);

    sprintf(filename, "%s.txt", sessions[current_session].name);
    return saveData(filename);
}

// 파일을 새 세션으로 불러오기
int load_session(const char *filename, char name[]) {

    if (session_count >= MAX_SESSIONS) {
        printf("더 이상 세션을 만들 수 없습니다.\n");
        return 0;
    }

    if (current_session != -1) {
        save_to_session(current_session);
    }

    if (loadData(filename) == 0) {
        return 0;
    }

    strcpy(sessions[session_count].name, name);
    save_to_session(session_count);

    current_session = session_count;
    session_count++;

    printf("'%s' 세션으로 불러왔습니다.\n", name);
    return 1;
}
