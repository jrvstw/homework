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
    private:
        int     valid;
        int     dirty;
        int     tag;
};

block::block(): valid(0), dirty(0)
{ /* intentionally empty */ }

int block::getValid()
{ return valid; }

int block::getDirty()
{ return dirty; }

int block::getTag()
{ return tag; }

void block::setValid()
{ valid = 1; }

void block::setDirty()
{ dirty = 1; }

void block::setClean()
{ dirty = 0; }

void block::setTag(int input)
{ tag = input; }

