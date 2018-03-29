#ifndef BIGINT_H
#define BIGINT_H

#include <stdio.h>
#include <stdlib.h>


/*
 * This defines a type bigInt which stores a non-negative integer with
 * unlimited digits.
 */
typedef struct _bigInt {
    int nSegment;
    int *addr;
} bigInt;


// This function constructs a bigInt with a integer not exceeding CAP.
bigInt construct(int value);

// This is invoked when a bigInt needs an additional segment.
void add_segment(int carry, bigInt *input);

// bigInt version of " *out = a + b ".
void plus(bigInt *out, bigInt a, bigInt b);

// bigInt version of " *out = a * b ".
void multiply(bigInt *out, bigInt a, bigInt b);

/*
 * bigInt version of matrix multiplication " out[] = a[] * b[] "
 *
 * This is ONLY for 2*2 matrices in the form {M[0][0], M[1][0], M[1][1]}
 * in which M[0][1] == M[1][0].
 */
void matrix_multiply(bigInt *out, bigInt *a, bigInt *b);

// This prints out a bigInt.
void print_bigInt(bigInt input);

#endif //BIGINT_H

