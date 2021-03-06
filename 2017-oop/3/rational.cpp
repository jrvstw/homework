#include <iostream>
using namespace std;

class Rational
{
public:
    Rational();
    // sets the number to 0/1
    Rational(int a);
    // sets the number to a/1
    Rational(int a, int b);
    /* sets the number to a/b when b is not 0. If b is 0, sets to 0/1 and sends
     * error message. */
    int getNumerator() const;
    // returns numerator
    int getDenominator() const;
    // returns denominator
    Rational normalize() const;
    // returns the normalized rational number.
    friend ostream& operator <<(ostream& outputStream, const Rational& value);
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
    const bool operator ==(const Rational b) const;
    const bool operator <(const Rational b) const;
    const bool operator <=(const Rational b) const;
    const bool operator >(const Rational b) const;
    const bool operator >=(const Rational b) const;
    const int& operator [](const int index) const;
    // [0] returns numerator, [1] returns denominator, others return error.
private:
    int numerator;
    int denominator;
    const int compare(const Rational that) const;
    /* Returned value is positive when *this > that, 0 when *this == that,
     * negative when *this < that. */
};


int main()
{
    Rational X, Y;
    cout << "Input a rational number: ";
    cin >> X;
    cout << "X = " << X << "\nInput another rational number: ";
    cin >> Y;
    cout << "Y = " << Y << "\n\n";

    cout << "X + Y  = " << X + Y << endl;
    cout << "X - Y  = " << X - Y << endl;
    cout << " -X    = " <<  -X   << endl;
    cout << "X * Y  = " << X * Y << endl;
    cout << "X / Y  = " << X / Y << endl;
    cout << "X == Y : " << (X == Y) << endl;
    cout << "X <  Y : " << (X < Y)  << endl;
    cout << "X <= Y : " << (X <= Y) << endl;
    cout << "X >  Y : " << (X > Y)  << endl;
    cout << "X >= Y : " << (X >= Y) << endl;
    cout << "X[0] = " << X[0] << endl;
    cout << "X[1] = " << X[1] << endl;
    cout << "X[2] = " << X[2] << endl;
    return 0;
}

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

Rational Rational::normalize() const
{
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
    inputStream >> value.numerator >> slash >> value.denominator;
    value = Rational(value.numerator, value.denominator);
    return inputStream;
}

const Rational Rational::operator +(const Rational b) const
{
    return Rational(getNumerator() * b.getDenominator()
                    + b.getNumerator() * getDenominator(),
                    getDenominator() * b.getDenominator()).normalize();
}

const Rational Rational::operator -(const Rational b) const
{
    return Rational(getNumerator() * b.getDenominator()
                    -b.getNumerator() * getDenominator(),
                    getDenominator() * b.getDenominator()).normalize();
}

const Rational Rational::operator -() const
{
    return Rational(-getNumerator(), getDenominator()).normalize();
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

const int& Rational::operator [](const int index) const
{
    if (index == 0)
        return numerator;
    else if (index == 1)
        return denominator;
    else
        cout << "\nIllegal index.\n\n";
}

const int Rational::compare(const Rational that) const
{
    return (numerator * that.denominator - that.numerator * denominator)
           * (denominator * that.denominator);
}

