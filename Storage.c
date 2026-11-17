#define _CRT_SECURE_NO_WARNINGS // fscanf/strcpy의 unsafe 함수 사용 경고를 무시

#include <stdio.h>
#include <string.h>

#define MAX 100

struct Event {
    char title[MAX];      // 결제한 장소 또는 이벤트 이름
    int payer;            // 실제 결제한 멤버의 인덱스 번호
    int member[MAX];      // 소비에 참여한 멤버들의 인덱스 번호
    int cost[MAX];        // 각 멤버가 소비한 금액
    int count;            // 해당 이벤트에 참여한 멤버 수
};

char members[MAX][20];

// 현재 등록된 전체 멤버 수                                     
int memberCount = 0;

// 결제 이벤트 정보를 저장하는 구조체 배열
struct Event events[MAX];

// 현재 등록된 전체 이벤트 수
int eventCount = 0;



// ================== 데이터 저장 함수 ==========================
void saveData(const char* filename) {

    FILE* fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("[ERROR] 파일을 열 수 없습니다: %s\n", filename);
        return;
    }

    // 1. 전체 멤버 정보 저장

    // 현재 등록된 멤버 수를 파일에 저장
    fprintf(fp, "%d\n", memberCount);

    // 등록된 멤버들의 이름을 하나씩 파일에 저장
    for (int i = 0; i < memberCount; i++) {
        fprintf(fp, "%s\n", members[i]);
    }


    // 2. 전체 결제 이벤트 정보 저장

    // 현재 등록된 이벤트 수를 파일에 저장
    fprintf(fp, "%d\n", eventCount);

    
    for (int i = 0; i < eventCount; i++) {

        // 이벤트 이름 저장
        fprintf(fp, "%s\n", events[i].title);

        // 결제한 멤버의 인덱스 번호 저장
        fprintf(fp, "%d\n", events[i].payer);

        // 해당 이벤트에 참여한 멤버 수 저장
        fprintf(fp, "%d\n", events[i].count);


        // 3. 참여한 멤버들의 인덱스 번호 저장
        for (int j = 0; j < events[i].count; j++) {
            fprintf(fp, "%d ", events[i].member[j]);
        }
        fprintf(fp, "\n");


        // 4. 각 멤버가 소비한 금액 저장
        for (int j = 0; j < events[i].count; j++) {
            fprintf(fp, "%d ", events[i].cost[j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    printf("[저장 완료] %s\n", filename);
}

// =================데이터 불러오기 함수==========================
int loadData(const char* filename) {

    FILE* fp = fopen(filename, "r");

    
    if (fp == NULL) {
        printf("[저장된 파일이 없습니다: %s]\n", filename);
        return 0;
    }


    // 1. 전체 멤버 정보 불러오기

    // 파일에 저장된 전체 멤버 수 읽기
    fscanf(fp, "%d", &memberCount);


    for (int i = 0; i < memberCount; i++) {

        // 멤버 이름을 members 배열에 저장
        fscanf(fp, "%19s", members[i]);
    }


    // 2. 전체 결제 이벤트 정보 불러오기

    // 파일에 저장된 전체 이벤트 수 읽기
    fscanf(fp, "%d", &eventCount);


    for (int i = 0; i < eventCount; i++) {

        // 이벤트 이름 읽기
        fscanf(fp, "%99s", events[i].title);

        // 결제한 멤버의 인덱스 번호 읽기
        fscanf(fp, "%d", &events[i].payer);

        // 해당 이벤트에 참여한 멤버 수 읽기
        fscanf(fp, "%d", &events[i].count);


        // 3. 참여한 멤버들의 인덱스 번호 읽기
        for (int j = 0; j < events[i].count; j++) {
            fscanf(fp, "%d", &events[i].member[j]);
        }


        // 4. 각 멤버가 소비한 금액 읽기
        for (int j = 0; j < events[i].count; j++) {
            fscanf(fp, "%d", &events[i].cost[j]);
        }
    }
    fclose(fp);

    printf("[불러오기 완료] %s\n", filename);

    // 데이터 불러오기에 성공하면 1 반환
    return 1;
}