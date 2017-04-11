#include <iostream>
#include "stdrandom.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    StdRandom::initialize();

    int i = 0;
    while (i < 100)
    {
        cout << StdRandom::gaussian() << endl;
        ++i;
    }
    return 0;
}
