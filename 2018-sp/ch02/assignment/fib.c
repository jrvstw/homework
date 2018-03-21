#include <stdio.h>
#include "bigInt.h"

bigInt fib(int n); // returns the nth value of Fibonacci sequence.

int main()
{
    int input;
    while (scanf("%d", &input) != EOF) {
        printf("   ");
        print_bigInt(fib(input));
        printf("\n");
    }
    return 0;
}

bigInt fib(int n)
{
    bigInt a = construct(0),
           b = construct(1);
    for (int i = 0; i < n/2; i++) {
        a = add(a, b);
        b = add(a, b);
    }
    return (n % 2)? b: a;
}

