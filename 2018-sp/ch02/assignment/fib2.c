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

void matrix_multiply(bigInt *out, bigInt *a, bigInt *b)
{
    bigInt tmp1, tmp2;

    tmp1 = multiply(a[2], b[2]);
    tmp2 = multiply(a[1], b[1]);
    out[2] = add(tmp1, tmp2);
    free(tmp1.addr);
    free(tmp2.addr);

    tmp1 = multiply(a[2], b[1]);
    tmp2 = multiply(a[1], b[0]);
    out[1] = add(tmp1, tmp2);
    free(tmp1.addr);
    free(tmp2.addr);

    tmp1 = multiply(a[1], b[1]);
    tmp2 = multiply(a[0], b[0]);
    out[0] = add(tmp1, tmp2);
    free(tmp1.addr);
    free(tmp2.addr);
}

bigInt fib(int n)
{
    bigInt a[3] = {construct(0), construct(1), construct(1)},
           b[3] = {construct(1), construct(0), construct(1)},
           tmp[3];
    for (int i = 1; i <= n; i <<= 1) {
        if (i & n) {
            matrix_multiply(tmp, a, b);
            free(b[0].addr);
            free(b[1].addr);
            free(b[2].addr);
            b[0] = tmp[0];
            b[1] = tmp[1];
            b[2] = tmp[2];
        }
        matrix_multiply(tmp, a, a);
        free(a[0].addr);
        free(a[1].addr);
        free(a[2].addr);
        a[0] = tmp[0];
        a[1] = tmp[1];
        a[2] = tmp[2];
    }
    return b[1];
}

