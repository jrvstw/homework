#include <iostream>
#include "rational.h"

namespace
{
    using namespace rationalJarvis;
    using namespace bigIntJarvis;
    const BigInt compare(const Rational A, const Rational B)
    {
        return (A.getNumerator() * B.getDenominator() -
                B.getNumerator() * A.getDenominator()) *
               (A.getDenominator() * B.getDenominator());
    }
}

namespace rationalJarvis
{
    using std::istream;
    using std::ostream;
    using std::cin;
    using std::cout;
    using std::endl;
    using namespace bigIntJarvis;
    Rational::Rational() : numerator(0), denominator(1)
    { /*intentionally empty*/ }

    Rational::Rational(BigInt wholeNumber) : numerator(wholeNumber), denominator(1)
    { /*intentionally empty*/ }

    Rational::Rational(BigInt inputNum, BigInt inputDenom)
    {
        if (inputDenom != 0) {
            numerator = inputNum;
            denominator = inputDenom;
        } else {
            cout << "Invalid number! The number is set to 0/1." << endl;
            numerator = 0;
            denominator = 1;
        }
    }

    BigInt Rational::getNumerator() const
    {
        return numerator;
    }

    BigInt Rational::getDenominator() const
    {
        return denominator;
    }

    Rational Rational::normalize() const
    {
        BigInt gcd = numerator,
            gcd2 = denominator;
        while (gcd2 != 0) {
            BigInt tmp = gcd % gcd2;
            gcd = gcd2;
            gcd2 = tmp;
        }
        if (gcd * denominator < 0)
            gcd = -gcd;
        return Rational(numerator / gcd, denominator / gcd);
    }

    ostream& operator <<(ostream& outputStream, const Rational& value)
    {
        outputStream << value.numerator;
        if (value.denominator != 1)
            outputStream << '/' << value.denominator;
        return outputStream;
    }

    /*
    istream& operator >>(istream& inputStream, Rational& value)
    {
        char slash;
        inputStream >> value.numerator >> slash >> value.denominator;
        value = Rational(value.numerator, value.denominator);
        return inputStream;
    }
    */

    const Rational Rational::operator +(const Rational b) const
    {
        return Rational(numerator * b.denominator + b.numerator * denominator,
                        denominator * b.denominator);
    }

    const Rational Rational::operator -(const Rational b) const
    {
        return Rational(numerator * b.denominator - b.numerator * denominator,
                        denominator * b.denominator);
    }

    const Rational Rational::operator -() const
    {
        return Rational(-numerator, denominator);
    }

    const Rational Rational::operator *(const Rational b) const
    {
        return Rational(numerator * b.numerator,
                        denominator * b.denominator);
    }

    const Rational Rational::operator /(const Rational b) const
    {
        return Rational(numerator * b.denominator,
                        denominator * b.numerator);
    }

    const bool Rational::operator <(const Rational b) const
    {
        return (compare(*this, b) < 0);
    }

    const bool Rational::operator <=(const Rational b) const
    {
        return (compare(*this, b) <= 0);
    }

    const bool Rational::operator ==(const Rational b) const
    {
        return (compare(*this, b) == 0);
    }

    const bool Rational::operator >=(const Rational b) const
    {
        return (compare(*this, b) >= 0);
    }

    const bool Rational::operator >(const Rational b) const
    {
        return (compare(*this, b) > 0);
    }

    const bool Rational::operator !=(const Rational b) const
    {
        return (compare(*this, b) != 0);
    }
}

