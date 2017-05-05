#include <iostream>
using namespace std;

typedef int* intPtr;

int main()
{
    int k(5);
    //intPtr a, b;
    int* a, * b;
    b = &k;
    cout << *b << endl;

    return 0;
}

