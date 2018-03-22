#include "bigInt.h"
#include <stdio.h>

bigInt fib(int n); // returns the nth value of Fibonacci sequence.

int main()
{
    int    input;
    bigInt output;
    while (scanf("%d", &input) != EOF) {
        printf("   ");
        output = fib(input);
        print_bigInt(output);
        free(output.addr);
        printf("\n");
    }
    return 0;
}

bigInt fib(int n)
{
    bigInt a = construct(0),
           b = construct(1);
    for (int i = 0; i < n/2; i++) {
        plus_equal(&a, b);
        plus_equal(&b, a);
    }
    if (n % 2) {
        free(a.addr);
        return b;
    } else {
        free(b.addr);
        return a;
    }
}

