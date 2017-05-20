// 402125039
//dealing with the problem that I can change the value of addr[i]
// deal with 0 in different digits
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#define MAXDIGIT 3
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
        int nSegment;
};

int main()
{
    BigInt a("111111111"), c(-a);
    BigInt *b = new BigInt(110112112);
    c = a - *b;
    cout << a << endl;
    cout << *b << endl;
    cout << c << endl;
    return 0;
}

BigInt::BigInt()
{
    nSegment = 1;
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
    nSegment = (A.length() - 1) / MAXDIGIT + 1;
    addr = new int[nSegment];
    //assigning numbers
    int i = 0;
    for (i = 0; i < nSegment - 1; i++) {
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
    int divisor = 1;
    for (int i = MAXDIGIT; i > 0; i--)
        divisor *= 10;
    // counting nSegment and assigning numbers
    int tmp[10] = {0};
    for (nSegment = 0; A != 0; nSegment++, A /= divisor)
        tmp[nSegment] = A % divisor;
    addr = new int[nSegment];
    for (int i = 0; i < nSegment; i++)
        addr[i] = tmp[i];
}

BigInt::BigInt(const BigInt &A)
{
    addr = new int[A.nSegment];
    for (nSegment = 0; nSegment < A.nSegment; nSegment++)
        addr[nSegment] = A.addr[nSegment];
}

const BigInt BigInt::operator =(const BigInt B)
{
    if (this != &B) {
        delete [] addr;
        addr = new int[B.nSegment];
        for (nSegment = 0; nSegment < B.nSegment; nSegment++)
            addr[nSegment] = B.addr[nSegment];
    }
    return *this;
}

const BigInt BigInt::operator +(const BigInt B) const
{
    // constructing a BigInt (overflow is considered)
    BigInt Result;
    delete [] Result.addr;
    Result.nSegment = max(nSegment, B.nSegment) + 1;
    Result.addr = new int[Result.nSegment];
    // setting divisor according to maxdigit
    int divisor = 1;
    for (int i = MAXDIGIT; i > 0; i--)
        divisor *= 10;
    // adding up assuming the result is posotive
    int carry = 0;
    for (int i = 0; i < Result.nSegment; i++) {
        Result.addr[i] = carry;
        if (i < nSegment)
            Result.addr[i] += addr[i];
        if (i < B.nSegment)
            Result.addr[i] += B.addr[i];
        // computing the next carry
        carry = Result.addr[i] / divisor - (Result.addr[i] < 0);
        Result.addr[i] -= carry * divisor;
        /*
        carry = Result.addr[i] / divisor;
        Result.addr[i] %= divisor;
        if (Result.addr[i] < 0) {
            carry--;
            Result.addr[i] += divisor;
        }
        */
    }
    // dealing with negative number
    if (carry == -1) {
        carry = 0;
        for (int i = 0; i < Result.nSegment; i++) {
            Result.addr[i] += carry;
            carry = 0;
            if (Result.addr[i] == 0)
                continue;
            Result.addr[i] -= divisor;
            carry = 1;
        }
    }
    // picking the proper number of segments
    int properSegment = Result.nSegment;
    while (Result.addr[properSegment - 1] == 0 && properSegment > 1)
        properSegment--;
    if (properSegment != Result.nSegment) {
        int *tmp = new int[properSegment];
        for (int i = 0; i < properSegment; i++)
            tmp[i] = Result.addr[i];
        delete [] Result.addr;
        Result.addr = tmp;
        Result.nSegment = properSegment;
    }
    return Result;
    /*
    if (carry > 0)
        return Result;
    else {
        BigInt Result2;
        delete [] Result2.addr;
        Result2.nSegment = Result.nSegment + 1;
        for (int i = 0; i < Result.nSegment; i++)
            Result2.addr[i] = Result.addr[i];
        Result2.addr[Result.nSegment] = carry;
        return Result2;
    }
    */
}

const BigInt BigInt::operator -(const BigInt B) const
{
    BigInt C(-B);
    BigInt Result = *this + C;
    return Result;
}

const BigInt BigInt::operator -() const
{
    BigInt A(*this);
    int i;
    for (i = 0; i < nSegment; i++)
        A.addr[i] = -A.addr[i];
    return A;
}

BigInt::~BigInt()
{
    delete [] addr;
}

ostream& operator <<(ostream& outputStream, const BigInt& A)
{
    outputStream << A.addr[A.nSegment - 1];
    for (int i = A.nSegment - 2; i >= 0; i--)
        outputStream << ',' << setw(MAXDIGIT) << setfill('0') << abs(A.addr[i]);
    return outputStream;
}

