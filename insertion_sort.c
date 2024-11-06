#include <stdio.h>

void sort(int* A, int n);
void insert(int* A, int first_index, int change_index, int value);



int main(void)
{
    int n = 6;

    int A[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    sort(A, n);

    return 0;
}

void insert(int* A, int first_index, int change_index, int value)
{
    for (int i = first_index; i >= change_index; i--) {
        A[i] = A[i - 1]; 
    }
    A[change_index] = value;
}

void sort(int* A, int n)
{
    // for (int i = 1; i < n; i++) {
    //     for (int j = 0; j < i; j++) {
    //         if (A[i] > A[j] && A[i] <= A[j + 1]) {
    //             insert(A, i, j + 1, A[i]);
    //         }
    //     }
    // }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (A[i] < A[0]) {
                insert(A, i, 0, A[i]);
            }
            else if(A[i] > A[j] && A[i] <= A[j + 1]) {
                insert(A, i, j + 1, A[i]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}