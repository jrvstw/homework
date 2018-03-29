#include <stdio.h>
#include <stdlib.h>

#define CAP 1000   // the upper bound of each integer composing a bigInt.
#define MAXDIGIT 3 // must equal log10(CAP)


/*
 * This defines a type bigInt which stores a non-negative integer with
 * unlimited digits.
 */
typedef struct _bigInt {
    int nSegment;
    int *addr;
} bigInt;


/*
 * This function constructs a bigInt with a integer not exceeding CAP.
 */
bigInt construct(int value)
{
    // exit if value is invalid.
    if (value < 0 || CAP <= value) {
        printf("failure: constructing a bigInt with a invalid value.");
        exit(1);
    }

    // constructing
    bigInt tmp = {1, calloc(1, sizeof(int))};
    if (tmp.addr == NULL) {
        printf("cannot allocate memory!\n");
        exit(1);
    }
    tmp.addr[0] = value;
    return tmp;
}


/*
 * This is invoked when a bigInt needs an additional segment.
 */
void add_segment(int carry, bigInt *input)
{
    // allocating a new section of memory.
    int *tmp = calloc(input->nSegment + 1, sizeof(int));
    if (tmp == NULL) {
        printf("cannot allocate memory!\n");
        exit(1);
    }

    // copying to this new one.
    for (int i = 0; i < input->nSegment; i++)
        tmp[i] = input->addr[i];
    tmp[input->nSegment] = carry;

    // replacing old with new.
    input->nSegment++;
    free(input->addr);
    input->addr = tmp;
    return;
}


/*
 * bigInt version of " *out = a + b ".
 */
void plus(bigInt *out, bigInt a, bigInt b)
{
    // constructin a new bigInt.
    bigInt sum;
    sum.nSegment = (a.nSegment > b.nSegment)? a.nSegment: b.nSegment;
    sum.addr   = calloc(sum.nSegment, sizeof(int));
    if (sum.addr == NULL) {
        printf("cannot allocate memory!\n");
        exit(1);
    }

    // adding a and b.
    for (int i = 0; i < a.nSegment; i++)
        sum.addr[i] += a.addr[i];

    for (int i = 0; i < b.nSegment; i++)
        sum.addr[i] += b.addr[i];

    // carrying
    int carry = 0;
    for (int i = 0; i < sum.nSegment; i++) {
        sum.addr[i] += carry;
        carry = sum.addr[i] / CAP;
        sum.addr[i] -= carry * CAP;
    }

    // if overflow, add a segment.
    if (carry)
        add_segment(carry, &sum);

    free(out->addr);
    *out = sum;
    return;
}


/*
 * bigInt version of " *out = a * b ".
 */
void multiply(bigInt *out, bigInt a, bigInt b)
{
    bigInt result;

    // a special case in which a == 0 or b == 0.
    if ((a.nSegment == 0 && a.addr[0] == 0) ||
        (b.nSegment == 1 && b.addr[0] == 0)) {
        result.nSegment = 1;
        result.addr   = calloc(1, sizeof(int));
        result.addr[0] = 0;
        free(out->addr);
        *out = result;
        return;
    }

    // constructing result.
    result.nSegment = a.nSegment + b.nSegment - 1;
    result.addr   = calloc(result.nSegment, sizeof(int));
    if (result.addr == NULL) {
        printf("cannot allocate memory!\n");
        exit(1);
    }

    // multiplying
    for (int i = 0; i < a.nSegment; i++)
        for (int j = 0; j < b.nSegment; j++)
            result.addr[i + j] += a.addr[i] * b.addr[j];

    // carrying
    int carry = 0;
    for (int i = 0; i < result.nSegment; i++) {
        result.addr[i] += carry;
        carry = result.addr[i] / CAP;
        result.addr[i] -= carry * CAP;
    }

    // if overflow, add a segment.
    if (carry)
        add_segment(carry, &result);

    free(out->addr);
    *out = result;
    return;
}


/*
 * bigInt version of matrix multiplication " out[] = a[] * b[] "
 *
 * This is ONLY for 2 by 2 matrices in which M[1][0] = M[0][1], and
 * matrices are simplified to 1 by 3: { M[0][0], M[1][0], M[1][1] }.
 */
void matrix_multiply(bigInt *out, bigInt *a, bigInt *b)
{
    bigInt tmp1 = construct(0),
           tmp2 = construct(0);
    bigInt result[3] = {construct(0),construct(0),  construct(0)};

    // doing matrix multiplication
    multiply(&tmp1, a[2], b[2]);
    multiply(&tmp2, a[1], b[1]);
    plus(result + 2, tmp1, tmp2);

    multiply(&tmp1, a[2], b[1]);
    multiply(&tmp2, a[1], b[0]);
    plus(result + 1, tmp1, tmp2);

    multiply(&tmp1, a[1], b[1]);
    multiply(&tmp2, a[0], b[0]);
    plus(result, tmp1, tmp2);

    // freeing and copying
    free(tmp1.addr);
    free(tmp2.addr);
    for (int i = 0; i < 3; i++) {
        free(out[i].addr);
        out[i] = result[i];
    }

    return;
}


/*
 * This prints out a bigInt.
 */
void print_bigInt(bigInt input)
{
    printf("%d", input.addr[input.nSegment - 1]);
    for (int i = input.nSegment - 2; i >= 0; i--)
        printf("%0*d", MAXDIGIT, input.addr[i]);
    return;
}

