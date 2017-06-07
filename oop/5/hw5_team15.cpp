#include <iostream>
//#include "bigInt.h"
#include "rational.h"
#include "complex.h"

int factorial(int x);

int main()
{
    using std::cout;
    using std::endl;
    using namespace rationalJarvis;
    using namespace complexHuang;
    Complex C1(Rational(1, 1), Rational(-6, 1)),
            C2(Rational(3, 1), Rational(4, 1));
            //C2(Rational(factorial(3), factorial(6)), Rational(factorial(5), factorial(7)));
    //a = factorial(81) / factorial(320);
    //b = factorial(128) / factorial(520);
    //cout << "Let C1 = 1/3 - (6/17)i,\n    C2 = 81!/320! + (128!/520!)i\n\n"
    cout << "Let C1 = 1/3 - (6/17)i, \n"
         << "    C2 = 4!/16! + (6!/26!)i\n\n"
         << " C1/C2 = " << C1 / C2 << endl;
    return 0;
}

int factorial(int x)
{
    int A(1);
    for (int i = x; i > 1; i--)
        A = A * i;
    return A;
}

