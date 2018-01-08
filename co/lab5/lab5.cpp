#include <iostream>
#include <string>
#include "blockSet.h"
using namespace std;

int main(int argc, char *argv[])
{
    // declare input variables
    int     cache_size  = atoi(argv[1]) << 10;
    int     block_size  = atoi(argv[2]);
    int     assoc       = (string(argv[3]) == "f")? cache_size/block_size:
                                                    atoi(argv[3]);
    string  r_policy    = string(argv[4]);
    string  input_file  = string(argv[5]);

    // declare a cache
    int      nSet = cache_size / block_size / assoc;
    blockSet cache[nSet];

    for (int i = 0; i < nSet; i++)
        cache[i] = blockSet(assoc);

    //declare output variables
    int     demand_fetch    = 0;
//  int     cache_hit       = 0;
    int     cache_miss      = 0;
//  double  miss_rate       = 0;
    int     read_data       = 0;
    int     write_data      = 0;
    int     B_from_mem      = 0;
    int     B_to_mem        = 0;

    // read files
    freopen(argv[5], "r", stdin);
    int label;
    int addr;
    while (cin >> label >> hex >> addr) {
        int tag     = (addr / block_size) / nSet;
        int index   = (addr / block_size) % nSet;

        demand_fetch++;

        switch (label) {
        case 0:
            read_data++;
            cache[index].read(tag, r_policy, cache_miss, B_from_mem, B_to_mem);
            break;
        case 1:
            write_data++;
            cache[index].write(tag, r_policy, cache_miss, B_from_mem, B_to_mem);
            break;
        case 2:
            cache[index].read(tag, r_policy, cache_miss, B_from_mem, B_to_mem);
            break;
        default:
            cout << "Invalid instance in " << input_file << endl;
            return -1;
        }
    }
    for (int i = 0; i < nSet; i++)
        cache[i].clean(B_to_mem);
    B_from_mem *= block_size;
    B_to_mem   *= block_size;


    // output
    cout << "Input file        = " << dec << input_file << endl
         << "Demand fetch      = " << demand_fetch << endl
         << "Cache hit         = " << demand_fetch - cache_miss << endl
         << "Cache miss        = " << cache_miss << endl
         << "Miss rate         = " ;
    printf("%.4f\n", double(cache_miss) / double(demand_fetch));
    cout << "Read data         = " << read_data << endl
         << "Write data        = " << write_data << endl
         << "Bytes from Memory = " << B_from_mem << endl
         << "Bytes to memory   = " << B_to_mem << endl << endl;

    return 0;
}

