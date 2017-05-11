#include <iostream>
#include "rational.h"
using namespace std;

int main()
{
    rational a(3, 5);
    cout << a.getNumerator() << '\n' << a.getDenominator() << endl;

    return 0;
}

