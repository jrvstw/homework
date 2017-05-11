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

int Rational::getNumerator() const
{
    return numerator;
}

int Rational::getDenominator() const
{
    return denominator;
}

const Rational Rational::normalize() const
{
    int num = this->getNumerator(),
        denom = this->getDenominator();
    int gcd = GCD(num, denom);
    num /= gcd;
    denom /= gcd;
    if (denom < 0) {
        num = -num;
        denom = -denom;
    }
    return Rational(num, denom);
    /*
    Rational foo(this->getNumerator(), this->getDenominator());
    int gcd = GCD(foo.numerator, foo.denominator);
    foo.numerator /= gcd;
    foo.denominator /= gcd;
    if (foo.denominator < 0) {
        foo.numerator = -foo.numerator;
        foo.denominator = -foo.denominator;
    }
    */
        /*
    int gcd = GCD(numerator, denominator);
    Rational A(numerator / gcd, denominator / gcd);
    if (denominator < 0) {
        A.numerator = -A.numerator;
        A.denominator = - A.denominator;
    }
    */
    //return foo;
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
    if ( value.denominator == 0 || slash != '/') {
        cout << "\nInvalid input! The number is set to 0/1. \n\n";
        value.numerator = 0;
        value.denominator = 1;
    }
    return inputStream;
}

const Rational operator *(const Rational a, const Rational b)
{
    return Rational(a.numerator * b.numerator,
                              a.denominator * b.denominator).normalize();
}

const Rational operator /(const Rational a, const Rational b)
{
    return Rational(a.numerator * b.denominator,
                              a.denominator * b.numerator).normalize();
}

const bool operator ==(const Rational a, const Rational b)
{
    return (a.compare(b) == 0);
}

const bool Rational::operator <(const Rational b) const
{
    return (this->compare(b) < 0);
}

const bool Rational::operator <=(const Rational b) const
{
    return (this->compare(b) <= 0);
}

const bool Rational::operator >(const Rational b) const
{
    return (this->compare(b) > 0);
}

const bool Rational::operator >=(const Rational b) const
{
    return (this->compare(b) >= 0);
}

const int& Rational::operator [](const int index)
{
    if (index == 0)
        return numerator;
    if (index == 1)
        return denominator;
    else
        cout << "\nIllegal index.\n\n";
}

const int Rational::GCD(const int a, const int b)
{
    int A = a,
        B = b;
    while (B != 0) {
        int C = A % B;
        A = B;
        B = C;
    }
    return A;
}

const int Rational::compare(const Rational that) const
{
    return (numerator * that.denominator - that.numerator * denominator)
           * (denominator * that.denominator);
}

const Rational Rational::operator +(const Rational b)
{
    return Rational(this->getNumerator() * b.getDenominator()
                              +b.getNumerator() * this->getDenominator(),
                              this->getDenominator() * b.getDenominator()).normalize();
}

const Rational Rational::operator -(const Rational b)
{
    return Rational(this->getNumerator() * b.getDenominator()
                              -b.getNumerator() * this->getDenominator(),
                              this->getDenominator() * b.getDenominator()).normalize();
}

const Rational Rational::operator -()
{
    return Rational(-this->getNumerator(), this->getDenominator()).normalize();
}

