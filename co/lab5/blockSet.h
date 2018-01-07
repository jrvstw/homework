#include <iostream>
#include "block.h"
using namespace std;

class blockSet
{
public:
    blockSet();
    blockSet(int assoc);
    void    print();
    void    read(int tag, int rpo, int &miss, int &fromM, int &toM);
    void    write(int tag, int rpo, int &miss, int &fromM, int &toM);
    void    writeBack(int &toM);
    ~blockSet();
private:
    int     checkHit(int tag);
    void    rotate(int tail);
    int     nBlocks;
    block   *head;
};

