#include "bigInt.h"
#include <stdio.h>

// fib(n) returns the nth value of Fibonacci sequence.
bigInt fib(int n);

int main()
{
    int    input;
    bigInt output;
    while (scanf("%d", &input) != EOF) {
        output = fib(input);
    //while (1) {
        //output = fib(1000);
        printf("    ");
        print_bigInt(output);
        printf("\n\n");
        free(output.addr);
    }
    return 0;
}


/*                              | F(n+1)  Fn     |     | 1  1 | n
 * fib(n) solves the equation   | Fn      F(n-1) |  =  | 1  0 |     in a
 * O(log(n)) way.
 */
bigInt fib(int n)
{
    bigInt F[3]  = {construct(0), construct(1), construct(1)},  // F1
           out[3] = {construct(1), construct(0), construct(1)}; // I(2)

    for (int i = 1; i <= n; i <<= 1) {
        if (i & n)
            matrix_multiply(out, F, out);
        matrix_multiply(F, F, F);
    }

    free(F[0].addr);
    free(F[1].addr);
    free(F[2].addr);
    free(out[0].addr);
    free(out[2].addr);
    return out[1];
}

