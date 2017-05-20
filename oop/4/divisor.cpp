#include <iostream>
using namespace std;

int main()
{
    int divisor = 1000;
    int input;
    do {
        cin >> input;
        cout << input % divisor << endl;
    } while (input != 17);
    return 0;
}

