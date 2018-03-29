#include "bigInt.h"
#include <stdio.h>

// fib(n) returns the nth value of Fibonacci sequence.
bigInt fib(int n);


int main(void)
{
    int    input;
    bigInt output;

    for (input = 0; input < 10000; input++) {
        output = fib(input);
        printf("\n\nfib(%d)=", input);
        print_bigInt(output);
        free(output.addr);
    }
    return 0;
}

/*                                                                    n
 *                                 | fib(n+1)  fib(n)   |     | 1  1 |
 * fib(n) solves the equation Fn = | fib(n)    fib(n-1) |  =  | 1  0 |
 * with a fast power method.
 */
bigInt fib(int n)
{
    /*  2*2 matrices here are simplified to 1*3.
     *  | M(0,0)  M(0,1) |
     *  | M(1,0)  M(1,1) |  ==>  {M(0,0), M(1,0), M(1,1)}
     */
    bigInt F[3]   = {construct(1), construct(1), construct(0)}, // F1
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

