#include <iostream>
#include "block.h"

class blockSet
{
    public:
        blockSet();
        void setAssoc(int assoc);
        void setBlocks();
        ~blockSet();
    private:
        int     nBlocks;
        block   *head;
}

blockSet::blockSet()
{
    nBlocks = 0;
}

void blockSet::setAssoc(int assoc)
{
    nBlocks = assoc;
}

void blockSet::setBlocks()
{
    head = new block;
}

blockSet::~blockSet()
{
    delete [] head;
}

