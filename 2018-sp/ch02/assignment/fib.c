#include <stdio.h>
#include <stdlib.h>

struct bigInt {
    int nSegment;
    int *addr;
};

int fib(int n)
{
    int a = 0,
        b = 1;
    for (int i = 0; i < n/2; i++) {
        a += b;
        b += a;
    }
    return (n % 2)? b: a;
}

int main()
{
    int input;
    struct bigInt a;
    a.nSegment = 3;
    a.addr = (int *)malloc(3 * sizeof(int));
    for (int i = 0; i < a.nSegment; i++)
        a.addr[i] = i;
    for (int i = 0; i < a.nSegment; i++)
        printf("%3d,", a.addr[i]);
    printf("\n");
    free(a.addr);
    while (scanf("%d", &input) != EOF)
        printf("   %d\n", fib(input));
    return 0;
}

