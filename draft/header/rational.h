#ifndef _RATIONAL_H_
#define _RATIONAL_H_

class rational
{
    public:
        rational(int a, int b);
        int getNumerator();
        int getDenominator();
    private:
        int numerator;
        int denominator;
};

#endif // _RATIONAL_H_

