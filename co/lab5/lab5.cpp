// remember to change a.out to cache when completed
#include <iostream>
#include <string>
//#include "block.h"
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
    int nSet = cache_size / block_size / assoc;
    blockSet cache[nSet];
    for (int i = 0; i < nSet; i++) {
        cache[i].setAssoc(assoc);
        cache[i].setBlocks();
    }

    // freopen
    freopen(argv[5], "r", stdin);

    // read files
    int label;
    int addr;
    while (cin >> label >> hex >> addr) {
        demand_fetch++;

        // locate block
        int tag     = addr / cache_size;
        int index   = (addr % cache_size) / block_size / assoc;

        int hit = 0;
        for (int i = 0; i < assoc; i++) {
            if (tag == cache[index][i].getTag())
                // hit
                ;
            else
                // keep searching
                ;

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
    cout << cache[0][0].getValid() << endl;

    // close
    return 0;
}

