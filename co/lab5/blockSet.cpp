#include <iostream>
#include "blockSet.h"
using namespace std;

blockSet::blockSet()
{
    nBlocks = 0;
    head = NULL;
}

blockSet::blockSet(int assoc)
{
    nBlocks = assoc;
    head = new block[assoc];
}

void blockSet::print()
{
    for (int i = 0; i < nBlocks; i++) {
        cout << i << ": ";
        head[i].print();
    }
}

int blockSet::checkHit(int tag)
{
    for (int i = 0; i < nBlocks; i++)
        if (tag == head[i].getTag())
            return i;
    return -1;
}

blockSet::~blockSet()
{
    delete [] head;
}

