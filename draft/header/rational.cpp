#include "rational.h"

rational::rational(int a, int b)
{
    numerator = a;
    if (b == 0)
        denominator = 1;
    else
        denominator = b;
}

int rational::getNumerator()
{
    return numerator;
}

int rational::getDenominator()
{
    return denominator;
}

