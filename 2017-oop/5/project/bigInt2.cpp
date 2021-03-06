// Team 15 #2 葉家瑋 402125039 哲學四

#include <iostream>
#include "bigInt2.h"
#define MAXDIGIT 3
#define CAP 1000
/* MAXDIGIT is the number of digits of every segment BigInt stores. It must not
 * exceed 3. CAP must be equal to 10^MAXDIGIT
 */
using namespace std;

namespace bigIntJarvis
{
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
               divisor = B.abs();
        for (int i = nSegment - 1; i >= 0; i--) {
            remainer = remainer * CAP;
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

    BigInt factorial(int x)
    {
        BigInt A(1);
        for (int i = x; i > 1; i--)
            A = A * i;
        return A;
    }
}

