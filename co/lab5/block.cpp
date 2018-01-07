#include <iostream>
#include "block.h"
using namespace std;

block::block()
{
    valid = 0;
    dirty = 0;
}

int block::getValid()
{
    return valid;
}

int block::getDirty()
{
    return dirty;
}

int block::getTag()
{
    return tag;
}

void block::setValid()
{
    valid = 1;
}

void block::setDirty()
{
    dirty = 1;
}

void block::setClean()
{
    dirty = 0;
}

void block::setTag(int input)
{
    tag = input;
}

void block::print()
{
    cout << valid << "," << dirty << "," << tag << "  ";
}

