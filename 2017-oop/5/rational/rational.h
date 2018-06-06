#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

namespace rationalJarvis
{
    using std::istream;
    using std::ostream;
    class Rational
    {
    public:
        Rational();
        // sets the number to 0/1
        Rational(int a);
        // sets the number to a/1
        Rational(int a, int b);
        /* sets the number to a/b when b is not 0. If b is 0, sets to 0/1 and
         * sends error message. */
        int getNumerator() const;
        // returns numerator
        int getDenominator() const;
        // returns denominator
        Rational normalize() const;
        // returns the normalized rational number.
        friend ostream& operator <<(ostream& outputStream,
                                    const Rational& value);
        /* The output is NOT normalized.
         * If the denominator equals 1, the rational number will be shown as
         * an integer. */
        friend istream& operator >>(istream& inputStream, Rational& value);
        /* The input format must be and integer followed by a slash followed by
         * another integer. If the second integer is 0, the rational number will
         * be set to 0/1. */
        const Rational operator +(const Rational b) const;
        // the output is normalized
        const Rational operator -(const Rational b) const;
        // the output is normalized
        const Rational operator -() const;
        // the output is normalized
        const Rational operator *(const Rational b) const;
        // the output is normalized
        const Rational operator /(const Rational b) const;
        // the output is normalized
        // returns 0/1 with error message if b equals 0
        const bool operator <(const Rational b) const;
        const bool operator <=(const Rational b) const;
        const bool operator ==(const Rational b) const;
        const bool operator >=(const Rational b) const;
        const bool operator >(const Rational b) const;
        const bool operator !=(const Rational b) const;
    private:
        int numerator;
        int denominator;
    };
} // rationalJarvis

#endif // RATIONAL_H

