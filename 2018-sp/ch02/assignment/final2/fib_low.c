#include "bigInt.h"
#include <stdio.h>

// fib(n) returns the nth value of Fibonacci sequence.
bigInt fib(int n);


int main(void)
{
    int    input;
    bigInt output;

    fib(1000)
    return 0;
}

fib(int n)
{
    bigInt a = construct(0),
           b = construct(1);
    for (int i = 0; i < n/2; i++) {
        plus(&a, a, b);
        plus(&b, a, b);
        printf("\n\nfib(%d)=", 2 * i);
        print_bigInt(a);
        printf("\n\nfib(%d)=", 2 * i + 1);
        print_bigInt(b);
    }
}

