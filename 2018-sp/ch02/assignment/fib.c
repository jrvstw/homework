#include <stdio.h>

int fib(int n)
{
    int a = 0,
        b = 1;
    for (int i = 0; i < n/2; i++) {
        a += b;
        b += a;
    }
}

int main()
{
    int input;
    while (scanf("%d", &input)) {
        printf("%d\n", fib(input));
    }
    return 0;
}

