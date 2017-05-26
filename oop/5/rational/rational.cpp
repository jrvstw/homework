#include <iostream>
#include "rational.h"
using namespace std;

Rational::Rational() : numerator(0), denominator(1)
{ /*intentionally empty*/ }

Rational::Rational(int wholeNumber) : numerator(wholeNumber), denominator(1)
{ /*intentionally empty*/ }

Rational::Rational(int inputNum, int inputDenom)
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

/*
int Rational::getNumerator() const
{
    return numerator;
}

int Rational::getDenominator() const
{
    return denominator;
}
*/

Rational Rational::normalize() const
{
    return *this;
    /*
    int gcd = numerator,
        gcd2 = denominator;
    while (gcd2 != 0) {
        int tmp = gcd % gcd2;
        gcd = gcd2;
        gcd2 = tmp;
    }
    if (gcd * denominator < 0)
        gcd = -gcd;
    return Rational(numerator / gcd, denominator / gcd);
    */
}

ostream& operator <<(ostream& outputStream, const Rational& value)
{
    outputStream << value.numerator;
    if (value.denominator != 1)
        outputStream << '/' << value.denominator;
    return outputStream;
}

istream& operator >>(istream& inputStream, Rational& value)
{
    char slash;
    cin >> value.numerator >> slash >> value.denominator;
    value = Rational(value.numerator, value.denominator);
    return inputStream;
}

const Rational Rational::operator +(const Rational b) const
{
    return Rational(numerator * b.denominator + b.numerator * denominator,
                    denominator * b.denominator).normalize();
}

const Rational Rational::operator -(const Rational b) const
{
    return Rational(numerator * b.denominator - b.numerator * denominator,
                    denominator * b.denominator).normalize();
}

const Rational Rational::operator -() const
{
    return Rational(-numerator, denominator).normalize();
}

const Rational Rational::operator *(const Rational b) const
{
    return Rational(numerator * b.numerator,
                    denominator * b.denominator).normalize();
}

const Rational Rational::operator /(const Rational b) const
{
    return Rational(numerator * b.denominator,
                    denominator * b.numerator).normalize();
}

const bool Rational::operator ==(const Rational b) const
{
    return (compare(b) == 0);
}

const bool Rational::operator <(const Rational b) const
{
    return (compare(b) < 0);
}

const bool Rational::operator <=(const Rational b) const
{
    return (compare(b) <= 0);
}

const bool Rational::operator >(const Rational b) const
{
    return (compare(b) > 0);
}

const bool Rational::operator >=(const Rational b) const
{
    return (compare(b) >= 0);
}

const int Rational::compare(const Rational that) const
{
    return (numerator * that.denominator - that.numerator * denominator)
           * (denominator * that.denominator);
}

