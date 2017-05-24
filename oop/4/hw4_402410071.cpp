//莊亞晉 402410071 資工四
#include <iostream>
#include <string>

using namespace std;

class BigInt
//An object of this class stores an integer of uncertain number of digits, and
//all big integer should be positive.
{
    friend ostream &operator<<(ostream &out, BigInt const &obj);
public:
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
private:
    int *big_int;
    int digit;
};
ostream &operator<<(ostream &out, const BigInt &obj)
{
    int i;
    for(i=0;i<obj.digit;i++)
    {
        out<<obj.big_int[i];
    }
    return out;
}
BigInt::BigInt(string bigint)
{
    int i;
    digit=bigint.size();
    big_int=new int[digit];
    for(i=0;i<digit;i++)
    {
        big_int[i]=bigint[i]-'0';
    }
}
BigInt::BigInt(int bigint)
{
    int temp=bigint;
    int count=0;
    int i;
    while(temp)
    {
        temp=temp/10;
        count++;
    }
    digit=count;
    big_int=new int[digit];
    for(i=digit-1;i>-1;i--)
    {
        big_int[i]=bigint%10;
        bigint=bigint/10;
    }
}
BigInt::BigInt(const BigInt &bigint)
{
    big_int=new int[bigint.digit];
    for(digit=0;digit<bigint.digit;digit++)
    {
        big_int[digit]=bigint.big_int[digit];
    }
}
BigInt::~BigInt()
{
    delete [] big_int;
}
const BigInt BigInt::operator =(const BigInt right)
{
    delete [] big_int;
    big_int=new int[right.digit];
    for(digit=0;digit<right.digit;digit++)
    {
        big_int[digit]=right.big_int[digit];
    }
    return *this;
}
const BigInt BigInt::operator +(const BigInt right) const
{
    BigInt result(*this);
    int carry=0;
    int i;
    int j;
    for(i=digit-1,j=right.digit-1;i>-1&&j>-1;i--,j--)
    {
        result.big_int[i]=big_int[i]+right.big_int[j]+carry;
        if(result.big_int[i]>9)
        {
            result.big_int[i]=result.big_int[i]%10;
            carry=1;
        }
        else
        {
            carry=0;
        }
    }
    for(i=i;i>-1;i--)
    {
        result.big_int[i]=big_int[i]+carry;
        if(result.big_int[i]>9)
        {
            result.big_int[i]=result.big_int[i]%10;
            carry=1;
        }
        else
        {
            carry=0;
        }
    }
    return result;
}
const BigInt BigInt::operator -(const BigInt right) const
{
    BigInt result(*this);
    int borrow=0;
    int i;
    int j;
    for(i=digit-1,j=right.digit-1;i>-1&&j>-1;i--,j--)
    {
        result.big_int[i]=big_int[i]-right.big_int[j]-borrow;
        if(result.big_int[i]<0)
        {
            result.big_int[i]=result.big_int[i]+10;
            borrow=1;
        }
        else
        {
            borrow=0;
        }
    }
    for(i=i;i>-1;i--)
    {
        result.big_int[i]=big_int[i]-borrow;
        if(result.big_int[i]<0)
        {
            result.big_int[i]=result.big_int[i]+10;
            borrow=1;
        }
        else
        {
            borrow=0;
        }
    }
    return result;
}

int main()
{
    BigInt a("314159265358979323846264338327950288419716939937510"),c(a);
    BigInt *b = new BigInt(1618033998);
    //cout<<a<<"\n"<<*b<<"\n"<<c<<"\n";
    c=a+*b;
    cout<<a<<" + "<<*b<<" = "<<c<<endl;
    c=a-*b;
    cout<<a<<" - "<<*b<<" = "<<c<<endl;
    return 0;
}
