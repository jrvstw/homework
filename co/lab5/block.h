#include <iostream>

class block
{
    public:
        block();
        int     getValid();
        int     getTag();
        ~block();
    private:
        int     valid;
        int     dirty;
        int     tag;
        block   next;
};

