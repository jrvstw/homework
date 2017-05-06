#include <iostream>
using namespace std;

int main()
{
    int robert = 20;
    int& bob = robert;
    bob = 30;
    cout << bob << "\n" << robert << endl;
    bob = 40;
    cout << bob << "\n" << robert << endl;

    return 0;
}

