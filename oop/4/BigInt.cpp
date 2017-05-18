#include <iostream>
#include <string>
#include <cstdlib>
#define MAXDIGIT 5
using namespace std;

class BigInt
{
    public:
        BigInt();
        BigInt(string A);
        const int *getLocation();
        friend ostream& operator <<(ostream& outputStream, BigInt& A);
    private:
        int *addr;
        int nInteger;
};

int main()
{
    BigInt k("12345678901234567");
    cout << k << endl;;
    //cout << *k.getLocation() << endl;
    /*
    string tmpStr;
    cin >> tmpStr;
    cout << tmpStr << '\n';
    int tmp = atoi(tmpStr.substr(tmpStr.length() - 3, 3).c_str());
    const int length = tmpStr.length() / MAXDIGIT + 1;
    int n[length];
    */
    return 0;
}

BigInt::BigInt()
{
    nInteger = 1;
    addr = new int(0);
}

BigInt::BigInt(string A)
{
    nInteger = (A.length() - 1) / MAXDIGIT + 1;
    addr = new int[nInteger];
    int i = 0;
    for (i = 0; i < nInteger - 1; i++) {
        addr[i] = atoi(A.substr(A.length() - MAXDIGIT, MAXDIGIT).c_str());
        A.resize(A.length() - MAXDIGIT);
    }
    addr[i] = atoi(A.c_str());
}

const int* BigInt::getLocation()
{
    return addr;
}

ostream& operator <<(ostream& outputStream, BigInt& A)
{
    int i;
    for (i = A.nInteger - 1; i >= 0; i--)
        outputStream << A.addr[i];
    return outputStream;
}

