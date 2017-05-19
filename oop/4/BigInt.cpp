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
        BigInt(int A);
        BigInt(const BigInt &A);
        const BigInt operator =(const BigInt B);
        const BigInt operator +(const BigInt B) const;
        const BigInt operator -(const BigInt B) const;
        const BigInt operator -() const;
        ~BigInt();
        friend ostream& operator <<(ostream& outputStream, const BigInt& A);
    private:
        int *addr;
        int nInteger;
};

int main()
{
    /*
    BigInt a("23549");
    cout << a << endl;
    BigInt *b = new BigInt(3492);
    cout << *b << endl;
    BigInt c(a);
    */
    BigInt a("12321"), c(-a);
    BigInt *b = new BigInt(11111);
    c = a - *b;
    cout << a << endl;
    cout << *b << endl;
    cout << c << endl;
    return 0;
}

BigInt::BigInt()
{
    nInteger = 1;
    addr = new int(0);
}

BigInt::BigInt(string A)
{
    //checking if the number is negative
    bool isNegative = 0;
    if (A[0] == '-') {
        isNegative = 1;
        A = A.substr(1, A.length() - 1);
    }
    //declaring dynamic array
    nInteger = (A.length() - 1) / MAXDIGIT + 1;
    addr = new int[nInteger];
    //assigning numbers
    int i = 0;
    for (i = 0; i < nInteger - 1; i++) {
        addr[i] = atoi(A.substr(A.length() - MAXDIGIT, MAXDIGIT).c_str());
        if (isNegative)
            addr[i] = -addr[i];
        A.resize(A.length() - MAXDIGIT);
    }
    addr[i] = atoi(A.c_str());
    if (isNegative)
        addr[i] = -addr[i];
}

BigInt::BigInt(int A)
{
    // setting divisor according to maxdigit
    int i = MAXDIGIT;
    int divisor = 1;
    while (i-- > 0)
        divisor *= 10;
    // assigning numbers
    int tmp[10] = {0};
    for (i = 0; A != 0; i++, A /= divisor)
        tmp[i] = A % divisor;
    nInteger = i;
    addr = new int[nInteger];
    for (i = 0; i < nInteger; i++)
        addr[i] = tmp[i];
}

BigInt::BigInt(const BigInt &A)
{
    addr = new int[A.nInteger];
    for (nInteger = 0; nInteger < A.nInteger; nInteger++)
        addr[nInteger] = A.addr[nInteger];
}

const BigInt BigInt::operator =(const BigInt B)
{
    if (this != &B) {
        delete [] addr;
        addr = new int[B.nInteger];
        for (nInteger = 0; nInteger < B.nInteger; nInteger++)
            addr[nInteger] = B.addr[nInteger];
    }
    return *this;
}

const BigInt BigInt::operator +(const BigInt B) const
{
    // constructing a BigInt
    BigInt Result;
    delete [] Result.addr;
    Result.nInteger = max(nInteger, B.nInteger);
    Result.addr = new int[Result.nInteger];
    // setting divisor according to maxdigit
    int divisor = 1;
    for (int i = MAXDIGIT; i > 0; i--)
        divisor *= 10;
    // adding up
    int carry = 0;
    for (int i = 0; i < Result.nInteger; i++) {
        Result.addr[i] = addr[i] + B.addr[i] + carry;
        carry = Result.addr[i] / divisor;
        if (carry != 0)
            Result.addr[i] %= divisor;
    }
    // dealing with overflow
    if (carry == 0)
        return Result;
    else {
        BigInt Result2;
        delete [] Result2.addr;
        Result2.nInteger = Result.nInteger + 1;
        for (int i = 0; i < Result.nInteger; i++)
            Result2.addr[i] = Result.addr[i];
        Result2.addr[Result.nInteger] = carry;
        return Result2;
    }
}

const BigInt BigInt::operator -(const BigInt B) const
{
    BigInt C(-B);
    BigInt Result = *this + C;
}

const BigInt BigInt::operator -() const
{
    BigInt A(*this);
    int i;
    for (i = 0; i < nInteger; i++)
        A.addr[i] = -A.addr[i];
    return A;
}

BigInt::~BigInt()
{
    delete [] addr;
}

ostream& operator <<(ostream& outputStream, const BigInt& A)
{
    outputStream << A.addr[A.nInteger - 1];
    int i;
    for (i = A.nInteger - 2; i >= 0; i--)
        outputStream << abs(A.addr[i]);
    return outputStream;
}

