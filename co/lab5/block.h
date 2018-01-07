#include <iostream>
using namespace std;

class block
{
    public:
        block();
        int     getValid();
        int     getTag();
        void    print();
    private:
        int     valid;
        int     dirty;
        int     tag;
};

