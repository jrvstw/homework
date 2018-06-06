// Team 15 #2 葉家瑋 402125039 哲學四

#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include "bigInt2.h"

namespace rationalJarvis
{
    using std::istream;
    using std::ostream;
    using namespace bigIntJarvis;
    class Rational
    {
    public:
        Rational();
        // sets the number to 0/1
        Rational(BigInt a);
        // sets the number to a/1
        Rational(BigInt a, BigInt b);
        /* sets the number to a/b when b is not 0. If b is 0, sets to 0/1 and
         * sends error message. */
        BigInt getNumerator() const;
        // returns numerator
        BigInt getDenominator() const;
        // returns denominator
        Rational normalize() const;
        // returns the normalized rational number.
        friend ostream& operator <<(ostream& outputStream,
                                    const Rational& value);
        /* The output is NOT normalized.
         * If the denominator equals 1, the rational number will be shown as
         * an integer. */
        //friend istream& operator >>(istream& inputStream, Rational& value);
        /* The input format must be and integer followed by a slash followed by
         * another integer. If the second integer is 0, the rational number will
         * be set to 0/1. */
        const Rational operator +(const Rational b) const;
        // the output is NOT normalized
        const Rational operator -(const Rational b) const;
        // the output is NOT normalized
        const Rational operator -() const;
        // the output is NOT normalized
        const Rational operator *(const Rational b) const;
        // the output is NOT normalized
        const Rational operator /(const Rational b) const;
        // the output is NOT normalized
        // returns 0/1 with error message if b equals 0
        const bool operator <(const Rational b) const;
        const bool operator <=(const Rational b) const;
        const bool operator ==(const Rational b) const;
        const bool operator >=(const Rational b) const;
        const bool operator >(const Rational b) const;
        const bool operator !=(const Rational b) const;
    private:
        BigInt numerator;
        BigInt denominator;
    };
} // rationalJarvis

#endif // RATIONAL_H

