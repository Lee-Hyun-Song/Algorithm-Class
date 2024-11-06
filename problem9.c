#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    double x;
    double y;
} DOTS;

double calculate_distance(DOTS dot1, DOTS dot2);



int main(void) {
    // Three test cases
    int testCase = 3;

    for (int i = 0; i < testCase; i++) {
        // n : the number of dots
        int n;
        scanf("%d", &n);

        // Make structure array for dots
        DOTS dots[n];

        // n만큼 dots 좌표 입력받음
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf", &dots[i].x, &dots[i].y);
        }

        // initialize distance matrix
        double distance_matrix[n][n];

        // make distance matrix
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    distance_matrix[i][j] = 1000.0;  
                } else {
                    distance_matrix[i][j] = calculate_distance(dots[i], dots[j]);
                }
            }
        }

        double result = 0;
        bool visited[n];  // 각 행이 이미 선택되었는지 여부를 기록하는 배열
        for (int i = 0; i < n; i++) {
            visited[i] = false;
        }

        int start = 0;  // 초기 시작 점
        visited[start] = true;  // 첫 번째 점 선택

        for (int k = 0; k < n - 1; k++) {
            double min = 1000.0;
            int selected_row = -1;
            int selected_col = -1;

            // 현재 선택된 점에서 다른 점으로의 최소 거리를 찾음
            for (int i = 0; i < n; i++) {
                if (visited[i]) {  // 이미 방문한 점에서만 최소값을 찾음
                    for (int j = 0; j < n; j++) {
                        if (!visited[j] && distance_matrix[i][j] < min) {
                            min = distance_matrix[i][j];
                            selected_row = i;
                            selected_col = j;
                        }
                    }
                }
            }

            // 선택된 최소 거리를 결과에 더하고, 방문 처리
            result += min;
            visited[selected_col] = true;  // 최소 거리가 선택된 열을 방문 처리
        }

        // print result
        printf("%.2lf\n\n", result);
    }

    return 0;
}

double calculate_distance(DOTS dot1, DOTS dot2) {
    return sqrt(pow(dot1.x - dot2.x, 2) + pow(dot1.y - dot2.y, 2));
}
