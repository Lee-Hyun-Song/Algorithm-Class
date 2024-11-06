#include <stdio.h>
#include <string.h>

#define MAXLEN 10

#define MATCH 0
#define INSERT 1
#define DELETE 2

typedef struct 
{
    int cost;
    int parent;
} cell;

cell m[MAXLEN + 1][MAXLEN + 1];


int string_compare(char* s, char* t);
void row_init(int i);
void column_init(i);

int main(void)
{
    char s[100], t[100];

    scanf("%s", s);
    scanf("%s", t);

    int result = string_compare(s, t);

    printf("%d\n", result);

    return 0;
}

int string_compare(char* s, char* t)
{
    int i, j, k;
    int opt[3];

    for (i = 0; i < MAXLEN; i++) {
        row_init(i);
        column_init(i);
    }

    for (i = 1; i < strlen(s); i++) {
        for (j = 1; j < strlen(t); j++) {
            opt[MATCH] = m[i - 1][j - 1].cost + match(s[i], t[i]);
        }
    }

    goal_cell(s, t, &i, &j);
    
}

void row_init(int i) 
{
    m[0][i].cost = i;
    if (i > 0) {
        m[0][i].parent = INSERT;
    }
    else {
        m[0][i].parent = -1;
    }
}

void column_init(int i)
{
    m[i][0].cost = i;
    if (i > 0) {
        m[i][0].parent = DELETE;
    }
    else {
        m[i][0].parent = -1;
    }
}