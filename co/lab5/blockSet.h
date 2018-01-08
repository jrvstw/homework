#include <iostream>
#include <string>
#include "block.h"
using namespace std;

class blockSet
{
public:
    blockSet();
    blockSet(int assoc);
    blockSet(const blockSet &B);
    blockSet operator =(blockSet B);
    void    print();
    void    read(int tag, string rpo, int &miss, int &fromM, int &toM);
    void    write(int tag, string rpo, int &miss, int &fromM, int &toM);
    void    writeBack(int &toM);
    ~blockSet();
private:
    int     checkHit(int tag);
    void    rotate(int tail);
    int     nBlocks;
    block   *head;
};

