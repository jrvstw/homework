#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

typedef struct {
    int x;
    int y;
} point;

int compare(const void* C, const void* D)
{
    point A = *(point *)C,
          B = *(point *)D;
    if (A.x != B.x)
        return A.x - B.x;
    else
        return A.y - B.y;
}

int cross(point O, point A, point B)
{
    return (A.x - O.x) * (B.y - A.y) - (B.x - A.x) * (A.y - O.y);
}

void ConvexHull(point convex[MAX], int *top, point input[MAX], int ninput)
{
    int i = 0;
    for (i = 0; i < ninput; i++) {
        while (*top > 0 &&
               cross(convex[*top - 1], convex[*top], input[i]) <= 0)
            (*top)--;
        convex[++(*top)] = input[i];
    }
    int middle = *top;
    for (i = ninput - 2; i >= 0; i--) {
        while (*top > middle &&
               cross(convex[*top - 1], convex[*top], input[i]) <= 0)
            (*top)--;
        convex[++(*top)] = input[i];
    }
    (*top)--;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    point input[MAX];
    int ninput = 0;
    while (scanf("%d %d ", &(input[ninput].x), &(input[ninput].y)) != EOF)
        ninput++;
    qsort(input, ninput, sizeof(point), compare);
    point convex[MAX];
    int top = -1;
    ConvexHull(convex, &top, input, ninput);
    int i = 0;
    for (i = 0; i <= top; i++)
        printf("%d %d\n" ,convex[i].x, convex[i].y);
    return 0;
}

