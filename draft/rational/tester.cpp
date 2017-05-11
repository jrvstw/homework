// 葉家瑋 402125039 哲學四

#include <iostream>
#include "rational.h"
using namespace std;

int main()
{
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
    cout << "X[0] = " << X[0] << endl;
    cout << "X[1] = " << X[1] << endl;
    cout << "X[2] = " << X[2] << endl;
    return 0;
}

