#include <iostream>
#include "stdrandom.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    StdRandom::initialize();

    Double table[3] = {0.3, 0.1, 0.6};

    int i = 0;
    while (i < 10000)
    {
        cout << StdRandom::discrete(table) << endl;
        ++i;
    }
    return 0;
}
