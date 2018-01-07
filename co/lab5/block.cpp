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

int block::getTag()
{
    return tag;
}

void block::print()
{
    cout << valid << "," << dirty << "," << tag << "  ";
}

