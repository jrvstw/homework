#include <iostream>
#include "rational.h"

BigInt factorial(int x)
{
    BigInt A(1);
    for (int i = 2; i <= x; i++)
        A = A * i;
    return A;
}


int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using namespace rationalJarvis;
    Rational A(BigInt(1), BigInt(3)),
             B(BigInt(-6), BigInt(17)),
             X(factorial(81), factorial(320)),
             Y(factorial(128), factorial(520));
    X = X.normalize();
    Y = Y.normalize();
    cout << X << endl << Y << endl;
    //cout << ((A*X + B*Y) / (X*X + Y*Y)).normalize() << endl;
    //cout << m * n * ((A * n) + (B * m)) << endl;
    //cout << m * m + n * n << endl;
    //cout << m * n * ((A / Y) + (B / X)) << endl;
    //cout << (A * X + B * Y) / (X * X + Y * Y) << endl;
    /*
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
    */
    return 0;
}

