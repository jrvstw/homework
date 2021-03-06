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
    void    read(int tag, string rpo, int &miss, int &fromM, int &toM);
    void    write(int tag, string rpo, int &miss, int &fromM, int &toM);
    void    clean(int &toM);
    ~blockSet();
private:
    int     checkHit(int tag);
    void    rotate(int tail);
    int     nBlocks;
    block   *head;
};

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

blockSet::blockSet(const blockSet &B)
{
    head = new block[B.nBlocks];
    for (nBlocks = 0; nBlocks < B.nBlocks; nBlocks++)
        head[nBlocks] = B.head[nBlocks];
}

blockSet blockSet::operator =(blockSet B)
{
    if (this != &B) {
        delete [] head;
        head = new block[B.nBlocks];
        for (nBlocks = 0; nBlocks < B.nBlocks; nBlocks++)
            head[nBlocks] = B.head[nBlocks];
    }
    return *this;
}

void blockSet::read(int tag, string rpo, int &miss, int &fromM, int &toM)
{
    int hit = checkHit(tag);
    if (hit > -1) {
        if (rpo == "LRU")
            rotate(hit);
    } else {
        miss++;
        rotate(nBlocks-1);
        if (head[0].getDirty())
            toM++;
        fromM++;
        head[0].setValid();
        head[0].setClean();
        head[0].setTag(tag);
    }
}

void blockSet::write(int tag, string rpo, int &miss, int &fromM, int &toM)
{
    int hit = checkHit(tag);
    if (hit > -1) {
        head[hit].setDirty();
        if (rpo == "LRU")
            rotate(hit);
    } else {
        miss++;
        rotate(nBlocks-1);
        if (head[0].getDirty())
            toM++;
        fromM++;
        head[0].setValid();
        head[0].setDirty();
        head[0].setTag(tag);
    }
}

void blockSet::clean(int &toM)
{
    for (int i = 0; i < nBlocks; i++)
        if (head[i].getDirty()) {
            head[i].setClean();
            toM++;
        }
}

blockSet::~blockSet()
{
    delete [] head;
}

int blockSet::checkHit(int tag)
{
    for (int i = 0; i < nBlocks; i++)
        if (head[i].getTag() == tag && head[i].getValid() == 1)
            return i;
    return -1;
}

void blockSet::rotate(int tail)
{
    block tmp = head[tail];
    for (int i = tail; i > 0; i--)
        head[i] = head[i-1];
    head[0] = tmp;
}

