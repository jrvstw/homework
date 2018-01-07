#include <iostream>
#include "block.h"
using namespace std;

class blockSet
{
    public:
        blockSet();
        blockSet(int assoc);
        void    print();
        int     checkHit(int tag);
        ~blockSet();
    private:
        int     nBlocks;
        block   *head;
};

