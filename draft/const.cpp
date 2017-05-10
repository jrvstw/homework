#include <iostream>
using namespace std;

int func(int *input, int &inp2)
{
    *input = 12;
    return int(20);
}

int main()
{
    int a = 5, b = 3;
    int *c;
    int d;
    c = &a;
    d = func(c, b);
    cout << d << endl;

    return 0;
}

