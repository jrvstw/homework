#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#define MAXDIGIT 3
/* maxdigit is the number of digits of every segment BigInt stores. It must not
 * exceed 9.
 */
using namespace std;

class BigInt
/* An object of this class stores an integer of uncertain number of digits, and
 * the integer can be negative. Objects of this class can do "+", "-", "=", and
 * "<<" operations. Other operations are not supported.
 */
{
    public:
        BigInt();
        // constructs an BigInt with value 0
        BigInt(string A);
        /* the string must contain only number characters 0 ~ 9, except that
         * the first character can be the negative sign.
         */
        BigInt(int A);
        BigInt(const BigInt &A);
        friend ostream& operator <<(ostream& outputStream, const BigInt& A);
        // prints the number with a comma between segments
        const BigInt operator =(const BigInt B);
        const BigInt operator +(const BigInt B) const;
        const BigInt operator -(const BigInt B) const;
        const BigInt operator -() const;
        ~BigInt();
    private:
        int *addr;    // address of the dynamic array of int
        int nSegment; // number of int used to store this big integer
        void correctSegment();
};

int main()
{
    //BigInt a("314159265358979323846264338327950288419716939937510"), c(a);
    //BigInt *b = new BigInt(1618033998);
    BigInt a("1000000000"), c(-a);
    BigInt *b = new BigInt(-999001);
    c = a + *b;
    cout << a << " + " << *b << " = " << c << endl;
    c = a - *b;
    cout << a << " - " << *b << " = " << c << endl;
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
    bool isNegative = (A[0] == '-')? 1: 0;
    nSegment = (A.length() - 1 - isNegative) / MAXDIGIT + 1;
    addr = new int[nSegment];
    for (int i = 0; i < nSegment - 1; i++) {
        addr[i] = atoi(A.substr(A.length() - MAXDIGIT, MAXDIGIT).c_str());
        A.resize(A.length() - MAXDIGIT);
        if (isNegative == true)
            addr[i] = -addr[i];
    }
    addr[nSegment - 1] = atoi(A.c_str());
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
    Result.correctSegment();
    return Result;
}

const BigInt BigInt::operator -(const BigInt B) const
{
    BigInt C(-B);
    return BigInt(*this + C);
}

const BigInt BigInt::operator -() const
{
    BigInt A(*this);
    for (int i = 0; i < nSegment; i++)
        A.addr[i] = -A.addr[i];
    return A;
}

BigInt::~BigInt()
{
    delete [] addr;
}

void BigInt::correctSegment()
{
    int properSegment = nSegment;
    while (addr[properSegment - 1] == 0 && properSegment > 1)
        properSegment--;
    if (properSegment != nSegment) {
        int *tmp = new int[properSegment];
        for (int i = 0; i < properSegment; i++)
            tmp[i] = addr[i];
        delete [] addr;
        nSegment = properSegment;
        addr = tmp;
    }
}

