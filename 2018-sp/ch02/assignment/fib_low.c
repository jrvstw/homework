#include "bigInt.h"
#include <stdio.h>

// fib(n) returns the nth value of Fibonacci sequence.
bigInt fib(int n);


int main(void)
{
    int    input;
    bigInt output;

    //while (scanf("%d", &input) != EOF) {
    for (input = 8000; input < 10000; input++) {
        output = fib(input);
        printf("%d:\n    ", input);
        print_bigInt(output);
        printf("\n\n");
        free(output.addr);
    }
    return 0;
}

/*                                                              n
 *                              | F(n+1)  Fn     |     | 1  1 |
 * fib(n) solves the equation   | Fn      F(n-1) |  =  | 1  0 |     with a
 * fast power method.
 */
bigInt fib(int n)
{
    bigInt a = construct(0),
           b = construct(1);
    for (int i = 0; i < n/2; i++) {
        plus(&a, a, b);
        plus(&b, a, b);
    }
    if (n % 2) {
        free(a.addr);
        return b;
    } else {
        free(b.addr);
        return a;
    }
}

