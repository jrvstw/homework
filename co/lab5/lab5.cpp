// remember to change a.out to cache when completed

#include <iostream>
#include <string>
#include "blockSet.h"
using namespace std;

int main(int argc, char *argv[])
{
    // check validity of input

    // declare input variables
    int     cache_size  = atoi(argv[1]) << 10; // in terms of bytes
    int     block_size  = atoi(argv[2]);
    int     assoc;
    string  r_policy    = argv[4];

    if (string(argv[3]) == "f")
        assoc = cache_size / block_size;
    else
        assoc = atoi(argv[3]);

    //declare output variables
    string  input_file      = string(argv[5]);
    int     demand_fetch    = 0;
    int     cache_hit       = 0;
    int     cache_miss      = 0;
    double  miss_rate       = 0;
    int     read_data       = 0;
    int     write_data      = 0;
    int     B_from_mem      = 0;
    int     B_to_mem        = 0;

    // declare a cache
    int      nSet = cache_size / block_size / assoc;
    blockSet cache[nSet];

    for (int i = 0; i < nSet; i++)
        cache[i] = blockSet(assoc);

    // freopen
    freopen(argv[5], "r", stdin);

    // read files
    int label;
    int addr;
    while (cin >> label >> hex >> addr) {
        int tag     = addr / cache_size;
        int index   = (addr % cache_size) / block_size / assoc;
        int hit     = cache[index].checkHit(tag);

        demand_fetch++;

        if (hit == -1) {
            
        }

        if (label == 0)
            read_data++;
        else if (label == 1)
            write_data++;

        cout << label << " " << hex << addr
             << " " << tag << " " << index << endl;
    }
    cout << dec << demand_fetch << endl;

    // test output
    cout << cache_size << " " << block_size << " " << assoc << " " << r_policy << endl;
    cout << nSet << " " << assoc << endl;
    for (int i = 0; i < nSet; i++) {
        cout << "# of sets:" << i << endl;
        cache[i].print();
        cout << endl << endl;
    }

    // close
    return 0;
}

