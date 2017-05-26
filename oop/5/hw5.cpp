#include <iostream>
#include "bigInt.h"
#include "rational.h"
#include "complex.h"
using namespace std;

BigInt factorial(int x);

int main()
{
    Rational a = 1/3,
             b = -6/17;
    Complex C1(a, b);
    //a = factorial(81) / factorial(320);
    //b = factorial(128) / factorial(520);
    a = factorial(4) / factorial(16);
    b = factorial(6) / factorial(26);
    Complex C2(a, b);
    //cout << "Let C1 = 1/3 - (6/17)i,\n    C2 = 81!/320! + (128!/520!)i\n\n"
    cout << "Let C1 = 1/3 - (6/17)i, \n"
         << "    C2 = 4!/16! + (6!/26!)i\n\n"
         << " C1/C2 = " << C1/C2 << endl;
    return 0;
}

BigInt factorial(int x)
{
    BigInt A(1);
    for (int i = x; i > 1; i--)
        A = A * i;
    return A;
}

