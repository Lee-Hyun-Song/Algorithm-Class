#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define POINTNUM 10


typedef struct Cartesian {
    double x;
    double y;
} Cartesian;

typedef struct STACK {
    Cartesian point;
} STACK;

void startPoint(Cartesian* points, int n);
void calculateAngleAndSort(Cartesian* points, int n);
// push to stack
void push(Cartesian point);
// pop data that is in top of the stack
void pop(void);
// compare function for qsort
int compare(const void* a, const void* b);
int ccw(Cartesian p0, Cartesian p1, Cartesian p2);
double calculateDistance(Cartesian p1, Cartesian p2);

STACK stack[POINTNUM];
int bottom = -1;
int top = -1;
Cartesian start;

int main(void)
{
    int testCase;
    printf("Please type number of test cases: ");
    scanf("%d", &testCase);

    for (int i = 0; i < testCase; i++) {
        int numOfItems;
        double result = 0.0;

        printf("Please type number of items: ");
        scanf("%d", &numOfItems);

        Cartesian points[numOfItems];
        

        printf("Please type %d x, y points: ", numOfItems);
        for (int i = 0; i < numOfItems; i++) {
            scanf("%lf %lf", &points[i].x, &points[i].y);
        }

        // find the starting point, points[0] will be the starting point
        startPoint(points, numOfItems);

        // add distance from (0,0) -> starting point
        result += sqrt(pow(points[0].x, 2) + pow(points[0].y, 2));

        

        // calculate angles and sort
        calculateAngleAndSort(points, numOfItems);

        // push p0, p1 to stack
        push(points[0]);
        push(points[1]);

        for (int i = 2; i < numOfItems; i++) {
            while (top > 0 && ccw(stack[top - 1].point, stack[top].point, points[i]) <= 0) {
                pop();
            }
            push(points[i]);
        }

        

        // calculate convex hull points
        for (int i = top; i > 0; i--) {
            result += calculateDistance(stack[i].point, stack[i - 1].point);
        }

        // last point to start point distance
        result += calculateDistance(stack[top].point, stack[bottom].point);

        // calculate distance starting point from (0,0)
        result += sqrt(pow(points[0].x, 2) + pow(points[0].y, 2));

        

        printf("%.2lf\n", result);
    }

    return 0;
}

// find the smallest y
void startPoint(Cartesian* points, int n)
{
    Cartesian tmp;
    tmp = points[0];
    int min = tmp.y;

    // swap small y to points[0], the last point[0] will be the starting point
    for (int i = 1; i < n; i++) {
        if (points[i].y < tmp.y) {
            tmp = points[i];
            points[i] = points[0];
            points[0] = tmp;
        }
        if (points[i].y == tmp.y) {
            if (points[i].x < tmp.x) {
                tmp = points[i];
                points[i] = points[0];
                points[0] = tmp;
            }
        }
    }
    start = points[0];
}

int compare(const void* a, const void* b)
{
    Cartesian* p1 = (Cartesian*)a;
    Cartesian* p2 = (Cartesian*)b;

    double angle1 = atan2(p1->y - start.y, p1->x - start.x);
    double angle2 = atan2(p2->y - start.y, p2->x - start.x);

    if (angle1 < angle2) return -1;
    if (angle1 > angle2) return 1;
    return 0;
}

// p0에서 출발하여 껍질을 반시계 방향으로 따라갈 수 있도록
void calculateAngleAndSort(Cartesian* points, int n)
{
    qsort(&points[1], n - 1, sizeof(Cartesian), compare);
}

int ccw(Cartesian p0, Cartesian p1, Cartesian p2)
{
    // use cross product 
    int val = (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
    if (val > 0) return 1;     // ccw
    else if (val < 0) return -1; // cw
    else return 0;              // straight
}

void push(Cartesian point)
{
    // first push
    if (bottom == -1 && top == -1) {
        bottom = 0;
        top = 0;
        stack[top].point = point;
    }

    top += 1;
    stack[top].point = point;

}

void pop(void)
{
    // Cartesian tmp;
    // tmp = stack[top].point;
    top -= 1;
}

double calculateDistance(Cartesian p1, Cartesian p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}