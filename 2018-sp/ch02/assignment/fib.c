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
           b = construct(1),
           tmp;
    for (int i = 0; i < n/2; i++) {
        tmp = add(a, b);
        free(a.addr);
        a = tmp;
        tmp = add(a, b);
        free(b.addr);
        b = tmp;
    }
    if (n % 2) {
        free(a.addr);
        return b;
    } else {
        free(b.addr);
        return a;
    }
    //return (n % 2)? b: a;
}

