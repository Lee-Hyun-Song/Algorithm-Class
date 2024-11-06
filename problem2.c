#include <stdio.h>
#include <stdlib.h>


void flip(int* pancake, int index1, int index2);
int isSorted(int* pancake, int n);

int main(void)
{
    int test_case = 0;

    const char* input_file = "input.txt";
    FILE* file = fopen(input_file, "r");

     if (!file) {
        printf("Error: Could not open file %s", input_file);
        exit(1);
    }

    // three test cases
    while(1) {
        
        if (test_case == 3) {
            break;
        }
        test_case++;

        int pancake[30] = {0};

        int i = 0;
        int a;
        int original[30];
        // 파일에서 입력 읽기
        while(fscanf(file, "%d", &a) == 1) {
            pancake[i] = a;
            original[i] = a;
            i++;
            if (fgetc(file) == '\n') {
                break; // 한 줄을 읽고 나면 중단
            }
        }

        int n = i;

        // k: 반복횟수
        int k = 0;
        int result[30] = {0};
        // j: result index
        int j = 0;

        while(1) {
            k++;
            // Check if pancakes are sorted
            if (isSorted(pancake, n) == 1) {
                break;
            }
            // Not sorted
            else {
                int index1 = 0;
                int index2 = n - k;
                
                // find max
                int max = pancake[0];
                for (int i = 1; i < n - k; i++) {
                    if (pancake[i] > max) {
                        max = pancake[i];
                        index1 = i;
                    }
                }
                // flip 불필요
                if (index1 >= index2) {
                    continue;
                }
                else {
                    flip(pancake, index1, index2);
                    result[j] = n - index2;
                    j++;
                }

            }

        }

        printf("Test case %d\n", test_case);

        
        

        // print original
        for (int i = 0; i < n; i++) {
            printf("%d ", original[i]);
        }
        printf("(");
        // print result
        for (int i = 0; i < n; i++) {
            printf("%d ", pancake[i]);
        }
        printf("\b)");
        printf("\n");

        for (int i = 0; i < j; i++) {
            printf("%d ", result[i]);
        }
        printf("%d", 0);

        printf("\n");
        

    }
    fclose(file);
    

    return 0;
} 

void flip(int* pancake, int index1, int index2)
{
    int num = index2 - index1 + 1;

    int tmp[100] = {0};

    // array 생성 후 flip할 내용 저장
    for (int i = 0; i < num; i++) {
        tmp[i] = pancake[index2 - i];
    }

    // flip 값 pancake array에 저장
    for (int i = 0; i < num; i++) {
        pancake[i + index1] = tmp[i];
    }
}



int isSorted(int* pancake, int n)
{
    for (int i = 0; i < n - 1; i++) {
        // Not sorted!
        if (pancake[i] > pancake[i + 1]) {
            return 0;
        }
    }
    return 1;
}