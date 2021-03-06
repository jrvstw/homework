#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>
#include <string>
namespace bigint
{
using namespace std;
class BigInt
//An object of this class stores an integer of uncertain number of digits, and
//all big integer should be positive.
{
    friend ostream &operator<<(ostream &out, BigInt const &obj);
public:
    //BigInt();
    BigInt(string bigint);
    // the string contains only positive numbers
    BigInt(int bigint);
    // the integer contains only positive numbers
    BigInt(const BigInt &bigint);
    //copy constructor
    ~BigInt();
    //destructor
    const BigInt operator =(const BigInt right);
    const BigInt operator +(const BigInt right) const;
    const BigInt operator -(const BigInt right) const;
    const BigInt operator *(const BigInt right) const;
private:
    int *big_int;
    int digit;
};
BigInt factorial(int);
}
#endif
