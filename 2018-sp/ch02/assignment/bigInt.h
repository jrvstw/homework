#include <stdio.h>
#include <stdlib.h>
#define CAP 1000   // the upper bound of each integer composing a bigInt.
#define MAXDIGIT 3 // must equal log10(CAP)


/*
 * This defines a type bigInt in which stores a non-negative integer with
 * unlimited digits.
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
    bigInt tmp = {1, calloc(1, sizeof(int))};
    if (tmp.addr == NULL) {
        printf("cannot allocate memory!\n");
        exit(1);
    }
    tmp.addr[0] = value;
    return tmp;
}


/*
 * This is called when a bigInt needs an additional part.
 */
void add_part(int carry, bigInt *input)
{
    int *tmp = calloc(input->nParts + 1, sizeof(int));
    if (tmp == NULL) {
        printf("cannot allocate memory!\n");
        exit(1);
    }
    for (int i = 0; i < input->nParts; i++)
        tmp[i] = input->addr[i];
    tmp[input->nParts] = carry;

    input->nParts++;
    free(input->addr);
    input->addr = tmp;
}


/*
 * " *out = a + b " for bigInt.
 */
void plus(bigInt *out, bigInt a, bigInt b)
{
    bigInt sum;
    sum.nParts = (a.nParts > b.nParts)? a.nParts: b.nParts;
    sum.addr   = calloc(sum.nParts, sizeof(int));
    if (sum.addr == NULL) {
        printf("cannot allocate memory!\n");
        exit(1);
    }

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
    if (carry)
        add_part(carry, &sum);
    free(out->addr);
    *out = sum;
}


/*
 * " *out = a * b " for bigInt.
 */
void multiply(bigInt *out, bigInt a, bigInt b)
{
    bigInt result;
    result.nParts = a.nParts + b.nParts - 1;
    result.addr   = calloc(result.nParts, sizeof(int));
    if (result.addr == NULL) {
        printf("cannot allocate memory!\n");
        exit(1);
    }
    for (int i = 0; i < a.nParts; i++)
        for (int j = 0; j < b.nParts; j++)
            result.addr[i + j] += a.addr[i] * b.addr[j];

    int carry = 0;
    for (int i = 0; i < result.nParts; i++) {
        result.addr[i] += carry;
        carry = result.addr[i] / CAP;
        result.addr[i] -= carry * CAP;
    }
    if (carry)
        add_part(carry, &result);
    free(out->addr);
    *out = result;
}


void matrix_multiply(bigInt *out, bigInt *a, bigInt *b)
{
    bigInt tmp1 = construct(0),
           tmp2 = construct(0);
    bigInt result[3] = {construct(0),construct(0),  construct(0)};

    for (int i = 0; i < 3; i++) {
        multiply(&tmp1, a[(i > 0) + 1], b[(i > 1) + 1]);
        multiply(&tmp2, a[(i > 0)], b[(i > 1)]);
        plus(result + i, tmp1, tmp2);
    }
    free(tmp1.addr);
    free(tmp2.addr);

    for (int i = 0; i < 3; i++) {
        free(out[i].addr);
        out[i] = result[i];
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

