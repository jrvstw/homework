//莊亞晉 402410071 資工四
#include <iostream>
#include <cmath>
using namespace std;
class Rational
{
    friend ostream &operator<<(ostream &out, const Rational &obj);
    friend istream &operator>>(istream &in, Rational &obj);
    //You can only input a rational number in "numerator/denominator" format.
    friend Rational operator*(const Rational &left, const Rational &right);
    friend Rational operator/(const Rational &left, const Rational &right);
    friend bool operator==(const Rational &left, const Rational &right);
public:
    Rational();
    //Default constructor that initializes an object to 0 (i.e.0/1).
    Rational(int numerator_,int denominator_);
    //A constructor with two arguments that can be used to set the member variables of an object
    //to any legitimate values.
    Rational(int wholeNumber);
    //A constructor that has only a single parameter wholeNumber of type int and initializes an
    //object to the rational number wholeNumber/1.
    int getNumerator() const;
    int getDenominator() const;
    bool operator<(const Rational &right);
    bool operator>(const Rational &right);
    bool operator<=(const Rational &right);
    bool operator>=(const Rational &right);
    int operator[](int index);
    void normalize();
    //After normalization, the denominator is positive
    //and the numerator and denominator are as small as possible. For example, after normalization
    //4/-8 would be represented the same as -1/2.
private:
    int numerator;
    int denominator;
};
const Rational operator +(const Rational &left,const Rational &right);
const Rational operator -(const Rational &left,const Rational &right);
const Rational operator -(const Rational &right);
ostream &operator<<(ostream &out, const Rational &obj)
{
    out<<obj.numerator<<"/"<<obj.denominator;
    return out;
}
istream &operator>>(istream &in, Rational &obj)
{
    char temp;
    in>>obj.numerator>>temp>>obj.denominator;
    obj.normalize();
    return in;
}
Rational operator*(const Rational &left, const Rational &right)
{
    Rational temp;
    temp.numerator=left.numerator*right.numerator;
    temp.denominator=left.denominator*right.denominator;
    temp.normalize();
    return temp;
}
Rational operator/(const Rational &left, const Rational &right)
{
    Rational temp;
    temp.numerator=left.numerator*right.denominator;
    temp.denominator=left.denominator*right.numerator;
    temp.normalize();
    return temp;
}
bool operator==(const Rational &left, const Rational &right)
{
    return (left.numerator==right.numerator&&left.denominator==right.denominator);
}
Rational::Rational():numerator(0),denominator(1)
{

}
Rational::Rational(int numerator_,int denominator_):numerator(numerator_),denominator(denominator_)
{
    normalize();
}
Rational::Rational(int wholeNumber):numerator(wholeNumber),denominator(1)
{

}
int Rational::getNumerator() const
{
    return numerator;
}
int Rational::getDenominator() const
{
    return denominator;
}
bool Rational::operator<(const Rational &right)
{
    int lside=numerator*right.denominator;
    int rside=denominator*right.numerator;
    return (lside<rside);
}
bool Rational::operator>(const Rational &right)
{
    int lside=numerator*right.denominator;
    int rside=denominator*right.numerator;
    return (lside>rside);
}
bool Rational::operator<=(const Rational &right)
{
    Rational temp;
    temp.numerator=numerator;
    temp.denominator=denominator;
    return ((temp<right)||(temp==right));
}
bool Rational::operator>=(const Rational &right)
{
    Rational temp;
    temp.numerator=numerator;
    temp.denominator=denominator;
    return ((temp>right)||(temp==right));
}
int Rational::operator[](int index)
{
    if(index==0)
    {
        return numerator;
    }
    else
    {
        return denominator;
    }
}
void Rational::normalize()
{
    int temp=numerator*denominator;
    int MIN=0;
    int GCD=1;
    int i;
    if(temp>0)
    {
        numerator=abs(numerator);
        denominator=abs(denominator);
    }
    else
    {
        numerator=-abs(numerator);
        denominator=abs(denominator);
    }
    if(abs(numerator)>abs(denominator))
    {
        MIN=abs(denominator);
    }
    else
    {
        MIN=abs(numerator);
    }
    for(i=MIN;i>0;i--)
    {
        if(numerator%i==0&&denominator%i==0)
        {
            GCD=i;
            break;
        }
    }
    //cout<<MIN<<" "<<GCD<<"\n";
    numerator=numerator/GCD;
    denominator=denominator/GCD;
}
const Rational operator +(const Rational &left,const Rational &right)
{
    int numerator_=left.getNumerator()*right.getDenominator()+right.getNumerator()*left.getDenominator();
    int denominator_=left.getDenominator()*right.getDenominator();
    return Rational(numerator_,denominator_);
}
const Rational operator -(const Rational &left,const Rational &right)
{
    int numerator_=left.getNumerator()*right.getDenominator()-right.getNumerator()*left.getDenominator();
    int denominator_=left.getDenominator()*right.getDenominator();
    return Rational(numerator_,denominator_);
}
const Rational operator -(const Rational &right)
{
    int numerator_=right.getNumerator()*-1;
    int denominator_=right.getDenominator();
    return Rational(numerator_,denominator_);
}
int main()
{
    Rational a,b(5),c(-2,3);
    cin>>a;
    a=a+b;
    cout<<a<<"\n";
    a=a-c;
    cout<<a<<"\n";
    a=-a;
    cout<<a<<"\n";
    a=a*b;
    cout<<a<<"\n";
    a=a/c;
    cout<<a<<"\n";
    cout<<"a==b?\n";
    if(a==b)
    {
        cout<<"yes\n";
    }
    else
    {
        cout<<"no\n";
    }
    cout<<"a<b?\n";
    if(a<b)
    {
        cout<<"yes\n";
    }
    else
    {
        cout<<"no\n";
    }
    cout<<"a<=b?\n";
    if(a<=b)
    {
        cout<<"yes\n";
    }
    else
    {
        cout<<"no\n";
    }
    cout<<"a>b?\n";
    if(a>b)
    {
        cout<<"yes\n";
    }
    else
    {
        cout<<"no\n";
    }
    cout<<"a>=b?\n";
    if(a>=b)
    {
        cout<<"yes\n";
    }
    else
    {
        cout<<"no\n";
    }
    cout<<a[0]<<"\n";
    cout<<a[1]<<"\n";
    return 0;
}
