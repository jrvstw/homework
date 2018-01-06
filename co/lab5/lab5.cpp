#include <iostream>
#include <string>
using namespace std;

class block
{
    public:
    private:
        int valid;
        int dirty;
        int tag;
        int data;
};

int main(int argc, char *argv[])
{
    // check validity of input
    int     cache_size  = atoi(argv[1]) << 8; // in terms of words
    int     block_size  = atoi(argv[2]) >> 2; // in terms of words
    int     assoc       = (argv[3]=="f")? 0: atoi(argv[3]);
    string  r_policy    = argv[4];

    cout << cache_size << " " << block_size << " " << assoc << " " << r_policy << endl;

    // freopen
    freopen(argv[5], "r", stdin);

    // declare a cache

    // calculate output
    int label;
    int addr;
    while (cin >> label >> hex >> addr) {
        cout << label << " " << hex << addr << endl;
    }

    return 0;
}

