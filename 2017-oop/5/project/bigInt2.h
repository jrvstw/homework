// Team 15 #2 葉家瑋 402125039 哲學四

#ifndef BIGINT2_H
#define BIGINT2_H

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
namespace bigIntJarvis
{
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
    BigInt factorial(int x);
}

#endif // BIGINT2_H

