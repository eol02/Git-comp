#define _CRT_SECURE_NO_WARNINGS // fscanf/strcpy의 unsafe 함수 사용 경고를 무시

#include "common.h"

// ================== 데이터 저장 함수 ==========================
int saveData(const char *filename) {

    FILE *fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("[ERROR] 파일을 열 수 없습니다: %s\n", filename);
        return 0;
    }

    // 전체 멤버 정보 저장

    fprintf(fp, "%d\n", member_count);

    for (int i = 0; i < member_count; i++) {
        fprintf(fp, "%s\n", members[i]);
    }

    // 전체 결제 이벤트 정보 저장
    fprintf(fp, "%d\n", event_count);

    for (int i = 0; i < event_count; i++) {

        fprintf(fp, "%s\n", events[i].title);
        fprintf(fp, "%d\n", events[i].payer);

        for (int j = 0; j < member_count; j++) {
            fprintf(fp, "%d ", events[i].participants[j]);
        }
        fprintf(fp, "\n");

        for (int j = 0; j < member_count; j++) {
            fprintf(fp, "%d ", events[i].costs[j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    printf("[저장 완료] %s\n", filename);
    return 1;
}

// =================데이터 불러오기 함수==========================
int loadData(const char *filename) {

    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("[저장된 파일이 없습니다: %s]\n", filename);
        return 0;
    }

    // 전체 멤버 정보 불러오기

    fscanf(fp, "%d", &member_count);

    for (int i = 0; i < member_count; i++) {
        fscanf(fp, "%19s", members[i]);
    }

    // 전체 결제 이벤트 정보 불러오기
    memset(events, 0, sizeof(events));
    fscanf(fp, "%d", &event_count);

    for (int i = 0; i < event_count; i++) {

        fscanf(fp, "%99s", events[i].title);
        fscanf(fp, "%d", &events[i].payer);

        for (int j = 0; j < member_count; j++) {
            fscanf(fp, "%d", &events[i].participants[j]);
        }

        for (int j = 0; j < member_count; j++) {
            fscanf(fp, "%d", &events[i].costs[j]);
        }
    }
    fclose(fp);

    printf("[불러오기 완료] %s\n", filename);

    return 1;
}
