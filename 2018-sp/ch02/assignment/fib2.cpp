// 402125039

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#define MAXDIGIT 3 // number of digits of every segment BigInt stores.
using namespace std;

class BigInt
/*
 * An object of this class stores an integer of uncertain number of digits, and
 * the integer can be negative. Objects of this class can do "+", "-", "=", and
 * "<<" operations. Other operations are not supported.
 */
{
    public:
        BigInt();
        // constructs an BigInt with value 0
        BigInt(int A);
        BigInt(const BigInt &A);
        friend ostream& operator <<(ostream& outputStream, const BigInt& A);
        // prints the number with a comma between segments
        const BigInt operator =(const BigInt B);
        const BigInt operator +(const BigInt B) const;
        ~BigInt();
    private:
        int *addr;    // address of the dynamic array of int
        int nSegment; // number of int used to store this big integer
};

int fib(int n)
{
    int A[3] = {0},
        B[3] = {0, 1, 1};
    for (int i = 0; i < n/2; i++) {
        A[2] = B[2] * B[2] + B[1] * B[1];
        A[1] = B[2] * B[1] + B[1] * B[0];
        A[0] = B[1] * B[1] + B[0] * B[0];
        B[2] = A[2] * A[2] + A[1] * A[1];
        B[1] = A[2] * A[1] + A[1] * A[0];
        B[0] = A[1] * A[1] + A[0] * A[0];
    }
    return (n % 2)? B[1]: A[1];
    /*
    BigInt a = 0,
           b = 1;
    for (int i = 0; i < n/2; i++) {
        a = a + b;
        b = b + a;
    }
    return (n % 2)? b: a;
    */
}

int main()
{
    int input = 10;
    while (cin >> input)
        cout << "    " << fib(input) << endl;
    /*
    BigInt a("314159265358979323846264338327950288419716939937510"), c(a);
    BigInt *b = new BigInt(1618033998);
    c = a + *b;
    cout << a << " + " << *b << " = " << c << endl;
    c = a - *b;
    cout << a << " - " << *b << " = " << c << endl;
    */
    return 0;
}

BigInt::BigInt()
{
    nSegment = 1;
    addr = new int(0);
}

BigInt::BigInt(int A)
{
    // computes the divisor according to maxdigit
    int divisor = 1;
    for (int i = MAXDIGIT; i > 0; i--)
        divisor *= 10;
    // counts nSegment and assigns numbers
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

ostream& operator <<(ostream& outputStream, const BigInt& A)
{
    outputStream << A.addr[A.nSegment - 1];
    for (int i = A.nSegment - 2; i >= 0; i--)
        outputStream << ',' << setw(MAXDIGIT) << setfill('0') << abs(A.addr[i]);
    return outputStream;
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
    // constructs a BigInt with 1 extra segment in case of overflow
    BigInt Result;
    delete [] Result.addr;
    Result.nSegment = max(nSegment, B.nSegment) + 1;
    Result.addr = new int[Result.nSegment];
    // computes the divisor according to maxdigit
    int divisor = 1;
    for (int i = MAXDIGIT; i > 0; i--)
        divisor *= 10;
    // adds up assuming the result is positive
    int carry = 0;
    for (int i = 0; i < Result.nSegment; i++) {
        Result.addr[i] = carry;
        if (i < nSegment)
            Result.addr[i] += addr[i];
        if (i < B.nSegment)
            Result.addr[i] += B.addr[i];
        // makes the segment positive and computes the next carry
        carry = Result.addr[i] / divisor;
        if (Result.addr[i] < 0 && (Result.addr[i] % divisor) != 0)
            carry--;
        Result.addr[i] -= carry * divisor;
    }
    // corrects every segment if the result should be negative
    if (carry == -1) {
        carry = 0;
        for (int i = 0; i < Result.nSegment; i++) {
            Result.addr[i] += carry;
            carry = (Result.addr[i] > 0)? 1: 0;
            Result.addr[i] -= carry * divisor;
        }
    }
    // corrects the number of segments
    int properSegment = Result.nSegment;
    while (Result.addr[properSegment - 1] == 0 && properSegment > 1)
        properSegment--;
    if (properSegment != Result.nSegment) {
        int *tmp = new int[properSegment];
        for (int i = 0; i < properSegment; i++)
            tmp[i] = Result.addr[i];
        delete [] Result.addr;
        Result.nSegment = properSegment;
        Result.addr = tmp;
    }
    return Result;
}

BigInt::~BigInt()
{
    delete [] addr;
}
