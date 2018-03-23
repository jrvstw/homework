#include "bigInt.h"
#include <stdio.h>

/*
 * fib() returns the nth value of Fibonacci sequence, using linear algebra
 * solution in a O(log(n)) way.
 */
bigInt fib(int n);

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
    bigInt F[3]  = {construct(0), construct(1), construct(1)},  // F1
           out[3] = {construct(1), construct(0), construct(1)}; // I(2)

    for (int i = 1; i <= n; i <<= 1) {
        if (i & n)
            matrix_multiply(out, F, out);
        matrix_multiply(F, F, F);
    }
    return out[1];
}

