#include <iostream>
//#include "bigInt.h"
//#include "rational.h"
#include "complex.h"

//int factorial(int x);

int main()
{
    using std::cout;
    using std::endl;
    //using namespace rationalJarvis;
    using namespace complexHuang;
    Complex C1(Rational(1, 3),
               Rational(6, 17)),
            C2(Rational(factorial(81), factorial(320)),
               Rational(factorial(128), factorial(520)));
    //a = factorial(81) / factorial(320);
    //b = factorial(128) / factorial(520);
    //cout << "Let C1 = 1/3 - (6/17)i,\n    C2 = 81!/320! + (128!/520!)i\n\n"
    cout << "Let C1 = " << C1 << endl
         << "    C2 = " << C2 << endl << endl
         << " C1/C2 = " << C1 / C2 << endl;
    return 0;
}

/*
int factorial(int x)
{
    int A(1);
    for (int i = x; i > 1; i--)
        A = A * i;
    return A;
}
*/

