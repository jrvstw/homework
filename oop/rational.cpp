#include <iostream>
using namespace std;

class Rational
{
    public:
        Rational();
        Rational(int a);
        /*
        Rational(int a, int b);
        int getNumerator();
        int getDenominator();
        */
    private:
        int numerator;
        int denominator;
};

int main()
{
    //

    return 0;
}

Rational::Rational()
    :numerator(1), denominator(1);
{/*intentionally empty*/}

Rational::Rational(int a)
    :denominator(1);
{/*intentionally empty*/}

