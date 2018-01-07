#include <iostream>
using namespace std;

class block
{
    public:
        block();
        int     getValid();
        int     getDirty();
        int     getTag();
        void    setValid();
        void    setDirty();
        void    setClean();
        void    setTag(int input);
        void    print();
    private:
        int     valid;
        int     dirty;
        int     tag;
};

