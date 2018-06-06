#include <iostream>
#include "rational.h"

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using namespace rationalJarvis;
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
    return 0;
}

