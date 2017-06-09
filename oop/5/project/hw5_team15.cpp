#include <iostream>
//#include "bigInt.h"
//#include "rational.h"
#include "complex.h"


int main()
{
    using std::cout;
    using std::endl;
    //using namespace bigIntJarvis;
    //using namespace rationalJarvis;
    using namespace complexHuang;
    Complex C1(Rational(1, 3),
               Rational(6, 17)),
            C2(Rational(factorial(81), factorial(320)).normalize(),
               Rational(factorial(128), factorial(520)).normalize());
    cout << "Let C1 = 1/3 - (6/17)i\n    C2 = 81!/320! + (128!/520!)i\n\n"
         << " C1/C2 = " << C1 / C2 << endl;
    return 0;
}

