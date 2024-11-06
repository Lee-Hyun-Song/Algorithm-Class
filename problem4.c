#include <stdio.h>

void sort(ELEPHANT* elephant, int n);
void swap(ELEPHANT* a, ELEPHANT* b);

typedef struct {
    int id;
    int weight;
    int iq;
} ELEPHANT;

int main(void)
{
    ELEPHANT elephant[1000];

    const char* inFile = "elephant.txt";
    FILE* file = fopen(inFile, "r");

    int i = 0;
    int weight = 0;
    int iq = 0;
    while (fscanf(file, "%d %d", &elephant[i].weight, &elephant[i].iq) != EOF) {
        i++;
        elephant[i].id = i;
    }
    fclose(file);

    // n : number of elephants
    int n = i;

    // sort 무게순으로. 만약 무게가 똑같으면 iq가 낮은게 더 먼저 오도록.
    sort(elephant, n);
    
    
    
    return 0;
}

// bubble sort
void sort(ELEPHANT* elephant, int n)
{
    for (int i = n - 2; i > 0; i--) {
        for (int j = 0; j <= i; j++) {
            if (elephant[j].weight > elephant[j + 1].weight) {
                swap(&elephant[j], &elephant[j + 1]);
            }
            // 만약 무게가 같을 경우 iq 오름차순으로 정렬
            else if (elephant[j].weight == elephant[j + 1].weight) {
                if (elephant[j].iq > elephant[j + 1].iq) {
                    swap(&elephant[j], &elephant[j + 1]);
                }
            }
        }
    }
}

void swap(ELEPHANT* a, ELEPHANT* b)
{
    ELEPHANT tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}