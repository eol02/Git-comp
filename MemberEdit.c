#include "common.h"

int delete_member(int idx) {

    if (idx < 0 || idx >= member_count) {
        printf("잘못된 번호입니다.\n");
        return 0;
    }

    // 결제자로 등록된 이벤트에서는 삭제 불가
    for (int i = 0; i < event_count; i++) {
        if (events[i].payer == idx) {
            printf("%s는 '%s'의 결제자라서 삭제할 수 없습니다.\n", members[idx], events[i].title);
            return 0;
        }
    }

    // 멤버를 이벤트에서 삭제
    for (int i = 0; i < event_count; i++) {
        events[i].participants[idx] = 0;
        events[i].costs[idx] = 0;
    }

    // 뒤에 있던 멤버들 인덱스를 한 칸씩 앞으로 당김
    for (int i = idx; i < member_count - 1; i++) {
        strcpy(members[i], members[i + 1]);

        for (int j = 0; j < event_count; j++) {
            events[j].participants[i] = events[j].participants[i + 1];
            events[j].costs[i] = events[j].costs[i + 1];
        }
    }
    // 결제자 인덱스 조정
    for (int j = 0; j < event_count; j++) {
        if (events[j].payer > idx) {
            events[j].payer--;
        }
    }

    member_count--;

    printf("삭제 완료\n");
    return 1;
}
