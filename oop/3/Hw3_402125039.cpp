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
    // sets the number to a/b when b is not 0. Otherwise, sets to 0/1.
    int getNumerator() const;
    // returns numerator
    int getDenominator() const;
    // returns denominator
    friend ostream& operator <<(ostream& outputStream, const Rational& value);
    // output the number in the format numerator/denominator
    friend istream& operator >>(istream& inputStream, Rational& value);
    /* The input format must be and integer followed by a slash followed by
     * another integer.
     */
    friend const Rational operator *(const Rational a, const Rational b);
    friend const Rational operator /(const Rational a, const Rational b);
    friend const bool operator ==(const Rational a, const Rational b);
    const bool operator <(const Rational b) const;
    const bool operator <=(const Rational b) const;
    const bool operator >(const Rational b) const;
    const bool operator >=(const Rational b) const;
    const int& operator [](const int index);
    // [1] returns numerator, [2] returns denominator, others return error.
    void normalize();
    // normalizes the number and guarantees the denominator will be positive.
private:
    int numerator;
    int denominator;
};

int GCD(int a, int b);
// returns the G.C.D. of integer a and b
const Rational operator +(const Rational a, const Rational b);
const Rational operator -(const Rational a, const Rational b);
const Rational operator -(const Rational a);
const Rational normalize(Rational a);
// returns a normalized rational number of which the denominator is positive.

int main()
{
    Rational X, Y;
    cout << "Input a rational number: ";
    cin >> X;
    cout << "X = " << X << "\nInput another rational number: ";
    cin >> Y;
    cout << "Y = " << Y << "\n\n";

    cout << "X + Y = " << normalize(X + Y) << endl;
    cout << "X - Y = " << normalize(X - Y) << endl;
    cout << "-X = " << normalize(-X) << endl;
    cout << "X * Y = " << normalize(X * Y) << endl;
    cout << " X / Y = " << normalize(X / Y) << endl;
    if (X == Y)
        cout << "X == Y\n";
    if (X < Y)
        cout << "X < Y\n";
    if (X <= Y)
        cout << "X <= Y\n";
    if (X > Y)
        cout << "X > Y\n";
    if (X >= Y)
        cout << "X >= Y\n";
    return 0;
}

Rational::Rational()
                  : numerator(0), denominator(1)
{ /*intentionally empty*/ }

Rational::Rational(int wholeNumber)
                   : numerator(wholeNumber), denominator(1)
{ /*intentionally empty*/ }

Rational::Rational(int inputNum, int inputDenom)
{
    if (inputDenom != 0) {
        numerator = inputNum;
        denominator = inputDenom;
    } else {
        cout << "Invalid input! The number is set to 0/1." << endl;
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

ostream& operator <<(ostream& outputStream, const Rational& value)
{
    /*
    if (value.denominator < 0)
        outputStream << -value.numerator;
    else
        outputStream << value.numerator;
    if (value.denominator != 1 && value.denominator != -1)
        outputStream << '/' << value.denominator;
    */
    outputStream << value.numerator << '/' << value.denominator;
    return outputStream;
}

istream& operator >>(istream& inputStream, Rational& value)
{
    char slash;
    cin >> value.numerator >> slash >> value.denominator;
    if ( value.denominator == 0 || slash != '/') {
        cout << "\nInvalid input! The number is set to 0/1. \n\n";
        value = Rational();
    }
    return inputStream;
}

const Rational operator *(const Rational a, const Rational b)
{
    return Rational(a.numerator * b.numerator, a.denominator * b.denominator);
}

const Rational operator /(const Rational a, const Rational b)
{
    return Rational(a.numerator * b.denominator, a.denominator * b.numerator);
}

const bool operator ==(const Rational a, const Rational b)
{
    return (a.numerator * b.denominator == b.numerator * a.denominator);
}

const bool Rational::operator <(const Rational b) const
{
    bool i = this->numerator * b.denominator < b.numerator * this->denominator;
    if (this->denominator * b.denominator > 0)
        return i;
    else
        return 1 - i;
}

const bool Rational::operator <=(const Rational b) const
{
    return !(*this > b);
}

const bool Rational::operator >(const Rational b) const
{
    bool i = this->numerator * b.denominator > b.numerator * this->denominator;
    if (this->denominator * b.denominator > 0)
        return i;
    else
        return 1 - i;
}

const bool Rational::operator >=(const Rational b) const
{
    return !(*this < b);
}

const int& Rational::operator [](const int index)
{
    if (index == 1)
        return numerator;
    if (index == 2)
        return denominator;
    else
        cout << "\nIllegal index.\n\n";
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

int GCD(int a, int b)
{
    while (b != 0) {
        int c = a % b;
        a = b;
        b = c;
    }
    return a;
}

const Rational operator +(const Rational a, const Rational b)
{
    return Rational(a.getNumerator() * b.getDenominator()
                    +b.getNumerator() * a.getDenominator(),
                    a.getDenominator() * b.getDenominator());
}

const Rational operator -(const Rational a, const Rational b)
{
    return Rational(a.getNumerator() * b.getDenominator()
                    -b.getNumerator() * a.getDenominator(),
                    a.getDenominator() * b.getDenominator());
}

const Rational operator -(const Rational a)
{
    return Rational(-a.getNumerator(), a.getDenominator());
}

const Rational normalize(Rational a)
{
    a.normalize();
    return a;
}

