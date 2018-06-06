// 葉家瑋 402125039 哲學四

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
    void normalize();
    // normalizes the number and guarantees the denominator will be positive.
    friend ostream& operator <<(ostream& outputStream, const Rational& value);
    /* The output is NOT normalized.
     * If the denominator equals 1, the rational number will be shown as
     * an integer. */
    friend istream& operator >>(istream& inputStream, Rational& value);
    /* The input format must be and integer followed by a slash followed by
     * another integer. If the second integer is 0, the rational number will
     * be set to 0/1. */
    friend const Rational operator *(const Rational a, const Rational b);
    // the output is normalized
    friend const Rational operator /(const Rational a, const Rational b);
    // the output is normalized
    // returns 0/1 with error message if b equals 0
    const int compare(const Rational that) const;
    /* Returned value is positive when *this > that, 0 when *this == that,
     * negative when *this < that. */
    friend const bool operator ==(const Rational a, const Rational b);
    const bool operator <(const Rational b) const;
    const bool operator <=(const Rational b) const;
    const bool operator >(const Rational b) const;
    const bool operator >=(const Rational b) const;
    const int& operator [](const int index);
    // [0] returns numerator, [1] returns denominator, others return error.
private:
    int numerator;
    int denominator;
};

int GCD(int a, int b);
// returns the G.C.D. of integer a and b
const Rational normalize(Rational a);
// returns a normalized rational number of which the denominator is positive.
const Rational operator +(const Rational a, const Rational b);
// the output is normalized
const Rational operator -(const Rational a, const Rational b);
// the output is normalized
const Rational operator -(const Rational a);
// the output is normalized

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

void Rational::normalize()
{
    int gcd = GCD(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    return;
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
    return normalize(Rational(a.numerator * b.numerator,
                              a.denominator * b.denominator));
}

const Rational operator /(const Rational a, const Rational b)
{
    return normalize(Rational(a.numerator * b.denominator,
                              a.denominator * b.numerator));
}

const int Rational::compare(const Rational that) const
{
    return (numerator * that.denominator - that.numerator * denominator)
           * (denominator * that.denominator);
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

int GCD(int a, int b)
{
    while (b != 0) {
        int c = a % b;
        a = b;
        b = c;
    }
    return a;
}

const Rational normalize(Rational a)
{
    a.normalize();
    return a;
}

const Rational operator +(const Rational a, const Rational b)
{
    return normalize(Rational(a.getNumerator() * b.getDenominator()
                              +b.getNumerator() * a.getDenominator(),
                              a.getDenominator() * b.getDenominator()));
}

const Rational operator -(const Rational a, const Rational b)
{
    return normalize(Rational(a.getNumerator() * b.getDenominator()
                              -b.getNumerator() * a.getDenominator(),
                              a.getDenominator() * b.getDenominator()));
}

const Rational operator -(const Rational a)
{
    return normalize(Rational(-a.getNumerator(), a.getDenominator()));
}

