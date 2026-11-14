#include <stdio.h>

#define MAX 100

struct Event{
    char title[MAX];   //결제 한 장소 혹은 사건의 이름
    int payer;   //결제한 멤버의 인덱스 번호
    int member[MAX];  //소비에 참여한 멤버의 인덱스 번호
    int cost[MAX];  //멤버별 소비한 금액
}

char members[MAX][20];  //전체 멤버

int main() {
    return 0;
}
