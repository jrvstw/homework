#include <iostream>
using namespace std;

class TypeA
{
    public:
        const int funcA() const;
    private:
        int num;
};

int main()
{
    TypeA K;
    int a = K.funcA();
    cout << a << endl;
    return 0;
}

const int TypeA::funcA() const
{
    int i = this->num;
    return i;
}

