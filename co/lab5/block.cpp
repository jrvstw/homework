#include <iostream>
#include "block.h"

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

