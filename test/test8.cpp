#include <iostream>
#include "algsrandom.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    AlgsRandom::initialize();
    int trues = 0;
    int falses = 0;

    int i = 0;
    while (i < 10000)
    {
        if (AlgsRandom::bernoulli(0.3))
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
