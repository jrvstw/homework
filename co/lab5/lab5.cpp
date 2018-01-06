#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    // check validity of input

    // freopen
    freopen("gcc100.din", "r", stdin);

    // calculate output
    int label;
    string addr;
    while (cin >> label >> addr) {
        cout << label << " " << addr << endl;
    }

    return 0;
}

