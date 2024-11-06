#include <stdio.h>

#define AVAILABLE 480
#define START_TIME 600
#define END_TIME 1080

int timeToMinute(int hour, int minute);


int main(void)
{
    int data_set = 1;
    while(1) {
        int time[AVAILABLE] = {0};

        // number of inputs
        int s;
        scanf("%d", &s);

        int h1, m1, h2, m2;
        char schedule[256];

        int calculate = 0;

        for (int i = 0; i < s; i++) {
            scanf("%d:%d %d:%d", &h1, &m1, &h2, &m2);
            // 공백도 읽기 위해 fgets를 써줌. stdin을 쓰면 꼭 파일에서 안 읽어도 됨
            fgets(schedule, sizeof(schedule), stdin);

            // 분으로 입력받은 시간 변환
            int start = timeToMinute(h1, m1);
            int end = timeToMinute(h2, m2);

            // schedule이 있는 시간을 1로 바꿈
            for (int i = start - 600; i < end - 600; i++) {
                time[i] = 1;
            }
        }

        // 연속된 0 이 가장 긴 구간을 찾아야 함.
        int longest_nap = 0;
        int nap_start = 0;
        int nap_finish = 0;
        int best_start = 0;
        int best_finish = 0;
        // flag -1 : Not counting, flag 0 : counting
        int flag = -1;
        for (int i = 0; i < AVAILABLE; i++) {
            if (time[i] == 0 && flag == -1) {
                nap_start = i;
                flag = 0;
            }
            if (time[i] == 1 && flag == 0) {
                nap_finish = i;
                int nap_cal = nap_finish - nap_start;
                if (nap_cal > longest_nap) {
                    best_start = nap_start;
                    best_finish = nap_finish;
                    longest_nap = nap_cal;
                }
                flag = -1;
            }
        }
        best_start += 600;
        best_finish += 600;

        int hour, minute;
        hour = best_start / 60;
        minute = best_start % 60;



        if (longest_nap < 60) {
            printf("Day #%d: the longest nap starts at %d:%d and will last for %d minutes\n", data_set, hour, minute, longest_nap);
        }
        else {
            printf("Day #%d: the longest nap starts at %d:%d and will last for %d hours and %d minutes\n", data_set, hour, minute, longest_nap / 60, longest_nap % 60);
        }

        
    }

   


    return 0;
}

int timeToMinute(int hour, int minute)
{
    return 60 * hour + minute;
}