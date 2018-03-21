#include <stdio.h>
#include <stdlib.h>
#define CAP 1000   // the upper bound of each integer composing a bigInt.
#define MAXDIGIT 3 // must equal log(CAP)


/*
 * This defines a type bigInt which has unlimited digits, but is limited to
 * be non-negative.
 */
typedef struct _bigInt {
    int nParts;
    int *addr;
} bigInt;


/*
 * This function constructs a bigInt with a integer.
 * The integer must not exceed CAP.
 */
bigInt construct(int value)
{
    bigInt tmp = {1, malloc(sizeof(int))};
    tmp.addr[0] = value;
    return tmp;
}


/*
 * This function returns a bigInt = a + b.
 */
bigInt add(bigInt a, bigInt b)
{
    bigInt sum;
    sum.nParts = (a.nParts > b.nParts)? a.nParts: b.nParts;
    sum.addr   = calloc(sum.nParts, sizeof(int));

    for (int i = 0; i < a.nParts; i++)
        sum.addr[i] += a.addr[i];

    for (int i = 0; i < b.nParts; i++)
        sum.addr[i] += b.addr[i];

    int carry = 0;
    for (int i = 0; i < sum.nParts; i++) {
        sum.addr[i] += carry;
        carry = sum.addr[i] / CAP;
        sum.addr[i] -= carry * CAP;
    }

    if (!carry) {
        return sum;
    } else {
        bigInt tmp;
        tmp.nParts = sum.nParts + 1;
        tmp.addr   = calloc(tmp.nParts, sizeof(int));
        tmp.addr[tmp.nParts - 1] = carry;
        for (int i = 0; i < sum.nParts; i++)
            tmp.addr[i] = sum.addr[i];
        return tmp;
    }
}


/*
 * This prints out a bigInt.
 */
void print_bigInt(bigInt input)
{
    printf("%d", input.addr[input.nParts - 1]);
    for (int i = input.nParts - 2; i >= 0; i--)
        printf("%0*d", MAXDIGIT, input.addr[i]);
}

