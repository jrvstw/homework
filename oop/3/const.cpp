#include <iostream>
using namespace std;

class test
{
    public:
        test(int i);
        void output() const;
    private:
        int num;
};

int main()
{
    test a(3);

    return 0;
}

test::test(int i)
    :num(i)
{ }

void test::output() const
{
}

void welcome(const test& a)
{
    a.output();
}

