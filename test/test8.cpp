#include <iostream>
#include "stdrandom.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    StdRandom::initialize();
    int trues = 0;
    int falses = 0;

    int i = 0;
    while (i < 10000)
    {
        if (StdRandom::bernoulli(0.3))
        {
            ++trues;
        }
        else
        {
            ++falses;
        }

        ++i;
    }
    cout << trues << "\t" << falses << endl;
    return 0;
}
