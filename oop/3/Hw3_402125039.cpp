/* 葉家瑋 402125039 哲學四 */

#include <iostream>
using namespace std;

class Rational
{
public:
    Rational();
    Rational(int a);
    Rational(int a, int b);
    int getNumerator() const;
    int getDenominator() const;
    friend ostream& operator <<(ostream& outputStream, const Rational& value);
    friend istream& operator >>(istream& inputStream, Rational& value);
    friend const Rational operator *(const Rational a, const Rational b);
    friend const Rational operator /(const Rational a, const Rational b);
    friend const bool operator ==(const Rational a, const Rational b);
    const bool operator <(const Rational b);
    const bool operator <=(const Rational b);
    const bool operator >(const Rational b);
    const bool operator >=(const Rational b);
    const int& operator [](int index);
    void normalize();
private:
    int numerator;
    int denominator;
};

int GCD(int a, int b);
const Rational operator +(const Rational a, const Rational b);
const Rational operator -(const Rational a, const Rational b);
const Rational operator -(const Rational a);
const Rational normalize(Rational a);

int main()
{
    Rational X, Y;
    cout << "Input a Rational number: ";
    cin >> X;
    cout << "A = " << X << "\nInput another rational number: ";
    cin >> Y;
    cout << "Y = " << Y << "\n\n";
    X.normalize();
    Y = normalize(Y);
    cout << "X + Y = " << X + Y << endl;
    cout << "X - Y = " << X - Y << endl;
    cout << "-X = " << -X << endl;
    cout << "X * Y = " << X * Y << endl;
    cout << " X / Y = " << X / Y << endl;
    if (X == Y)
        cout << "X == Y" << endl;
    if (X < Y)
        cout << "X < Y" << endl;
    if (X <= Y)
        cout << "X <= Y" << endl;
    if (X > Y)
        cout << "X > Y" << endl;
    if (X >= Y)
        cout << "X >= Y" << endl;
    return 0;
}

Rational::Rational()
                  : numerator(0), denominator(1)
{
    /*intentionally empty*/
}

Rational::Rational(int wholeNumber)
                  : denominator(1)
{
    numerator = wholeNumber;
}

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
    if ( value.denominator < 0)
        outputStream << -value.numerator << '/' << -value.denominator;
    else
        outputStream << value.numerator << '/' << value.denominator;
    return outputStream;
}

istream& operator >>(istream& inputStream, Rational& value)
{
    int num, denom;
    char slash;
    cin >> num >> slash >> denom;
    value.numerator = num;
    value.denominator = denom;
    return inputStream;
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

const bool Rational::operator <(const Rational b)
{
    bool i = this->numerator * b.denominator < b.numerator * this->denominator;
    if (this->denominator * b.denominator > 0)
        return i;
    else
        return 1 - i;
}

const bool Rational::operator <=(const Rational b)
{
    return !(*this > b);
}

const bool Rational::operator >(const Rational b)
{
    bool i = this->numerator * b.denominator > b.numerator * this->denominator;
    if (this->denominator * b.denominator > 0)
        return i;
    else
        return 1 - i;
}

const bool Rational::operator >=(const Rational b)
{
    return !(*this < b);
}

const int& Rational::operator [](int index)
{
    if (index == 1)
        return numerator;
    if (index == 2)
        return denominator;
    else
        cout << "Illegal index.\n";
}

const Rational normalize(Rational a)
{
    a.normalize();
    return a;
}

