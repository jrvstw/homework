#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#define MAXDIGIT 3
#define CAP 1000
/* maxdigit is the number of digits of every segment BigInt stores. It must not
 * exceed 3.
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
        const BigInt operator =(const BigInt B);
        const BigInt operator +(const BigInt B) const;
        const BigInt operator -(const BigInt B) const;
        const BigInt operator -() const;
        const BigInt operator *(const BigInt B) const;
        // has problems of overflow when numbers get big
        const BigInt operator /(const BigInt B) const;
        const BigInt operator %(const BigInt B) const;
        const BigInt abs() const;
        const bool operator <(const BigInt B) const;
        const bool operator <=(const BigInt B) const;
        const bool operator ==(const BigInt B) const;
        const bool operator >=(const BigInt B) const;
        const bool operator >(const BigInt B) const;
        const bool operator !=(const BigInt B) const;
        ~BigInt();
    private:
        int *addr;    // address of the dynamic array of int
        int nSegment; // number of int used to store this big integer
        void correctSegment();
        const int compare(const BigInt B) const;
};

BigInt factorial(int x)
{
    BigInt A(1);
    for (int i = 2; i <= x; i++)
        A = A * i;
    return A;
}

int main()
{
    //BigInt a("314159265358979323846264338327950288419716939937510"), c(a);
    //BigInt *b = new BigInt(1618033998);
    BigInt e = factorial(81),
           f = factorial(320),
           c = factorial(128),
           d = factorial(520);
    cout << e * d * 17 - f * c * 18 << endl;
    cout << f * d * 51 << endl;
    //BigInt a(f / e),
           //b(d % c);
    //cout << a * b * (b / 3 - a * 6 / 17) << endl;
    //cout << a << endl << b << endl;
    //cout << a * b * (b/3 - a * 6 /17) / (a * a + b * b) << endl;
    //cout << a * a * b * b * (b * 17 - a * 18)/ (a * 3 * 17 * b) / (a * a + b * b) << endl;
    /*
    cout << " a + b = " << (a + *b) << endl;
    cout << " a - b = " << (a - *b) << endl;
    cout << " a * b = " << (a * *b) << endl;
    cout << " a < b : " << (a < *b) << endl;
    cout << " a <= b : " << (a <= *b) << endl;
    cout << " a == b : " << (a == *b) << endl;
    cout << " a >= b : " << (a >= *b) << endl;
    cout << " a > b : " << (a > *b) << endl;
    */
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
    int tmp[10] = {0};
    for (nSegment = 0; A != 0; nSegment++, A /= CAP)
        tmp[nSegment] = A % CAP;
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
        outputStream << setw(MAXDIGIT) << setfill('0') << abs(A.addr[i]);
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
    // adds up assuming the result is positive
    int carry = 0;
    for (int i = 0; i < Result.nSegment; i++) {
        Result.addr[i] = carry;
        if (i < nSegment)
            Result.addr[i] += addr[i];
        if (i < B.nSegment)
            Result.addr[i] += B.addr[i];
        // makes the segment positive and computes the next carry
        carry = Result.addr[i] / CAP;
        if (Result.addr[i] < 0 && (Result.addr[i] % CAP) != 0)
            carry--;
        Result.addr[i] -= carry * CAP;
    }
    // corrects every segment if the result should be negative
    if (carry == -1) {
        carry = 0;
        for (int i = 0; i < Result.nSegment; i++) {
            Result.addr[i] += carry;
            carry = (Result.addr[i] > 0)? 1: 0;
            Result.addr[i] -= carry * CAP;
        }
    }
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

const BigInt BigInt::operator *(const BigInt B) const
{
    BigInt Result;
    delete [] Result.addr;
    Result.nSegment = nSegment + B.nSegment;
    Result.addr = new int[Result.nSegment];
    for (int i = 0; i < Result.nSegment; i++)
        Result.addr[i] = 0;
    for (int i = 0; i < nSegment; i++)
        for (int j = 0; j < B.nSegment; j++)
            Result.addr[i + j] += addr[i] * B.addr[j];
    int carry = 0;
    for (int i = 0; i < Result.nSegment - 1; i++) {
        Result.addr[i] += carry;
        carry = Result.addr[i] / CAP;
        Result.addr[i] %= CAP;
    }
    Result.addr[Result.nSegment - 1] = carry;
    Result.correctSegment();
    return Result;
}

const BigInt BigInt::operator /(const BigInt B) const
{
    if (B.addr[B.nSegment - 1] == 0) {
        cout << "ERROR: divisor is zero" << endl;
        return *this;
    }
    BigInt remainer,
           quotient,
           divisor = B.abs();
    for (int i = nSegment - 1; i >= 0; i--) {
        remainer = remainer * CAP;
        quotient = quotient * CAP;
        remainer.addr[0] = std::abs(addr[i]);
        int low = 0,
            high = CAP - 1,
            mid;
        while (low < high) {
            mid = (low + high + 1) >> 1;
            if (divisor * mid <= remainer)
                low = mid;
            else
                high = mid - 1;
        }
        quotient.addr[0] = low;
        remainer = remainer - divisor * quotient.addr[0];
        remainer.correctSegment();
    }
    if (addr[nSegment - 1] * B.addr[nSegment - 1] < 0)
        quotient = -quotient;
    return quotient;
}

const BigInt BigInt::operator %(const BigInt B) const
{
    if (B.addr[B.nSegment - 1] == 0) {
        cout << "ERROR: divisor is zero" << endl;
        return *this;
    }
    BigInt remainer,
           //quotient,
           divisor = B.abs();
    for (int i = nSegment - 1; i >= 0; i--) {
        remainer = remainer * CAP;
        //quotient = quotient * CAP;
        remainer.addr[0] = std::abs(addr[i]);
        int low = 0,
            high = CAP - 1,
            mid;
        while (low < high) {
            mid = (low + high + 1) >> 1;
            if (divisor * mid <= remainer)
                low = mid;
            else
                high = mid - 1;
        }
        //quotient.addr[0] = low;
        //remainer = remainer - divisor * quotient.addr[0];
        remainer = remainer - divisor * low;
        remainer.correctSegment();
    }
    if (addr[nSegment - 1] < 0)
        remainer = -remainer;
    return remainer;
}

const BigInt BigInt::abs() const
{
    if (addr[nSegment - 1] >= 0)
        return *this;
    BigInt A(*this);
    for (int i = 0; i < nSegment; i++)
        A.addr[i] = -addr[i];
    return A;
}

const bool BigInt::operator <(const BigInt B) const
{
    return compare(B) < 0;
}

const bool BigInt::operator <=(const BigInt B) const
{
    return compare(B) <= 0;
}

const bool BigInt::operator ==(const BigInt B) const
{
    return compare(B) == 0;
}

const bool BigInt::operator >=(const BigInt B) const
{
    return compare(B) >= 0;
}

const bool BigInt::operator >(const BigInt B) const
{
    return compare(B) > 0;
}

const bool BigInt::operator !=(const BigInt B) const
{
    return compare(B) != 0;
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

const int BigInt::compare(const BigInt B) const
{
    if (nSegment > B.nSegment)
        return addr[nSegment - 1];
    else if (nSegment < B.nSegment)
        return -B.addr[B.nSegment - 1];
    else {
        int i = nSegment - 1;
        while (addr[i] == B.addr[i] && i > 0)
            i--;
        return addr[i] - B.addr[i];
    }
}

