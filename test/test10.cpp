#include <iostream>
#include "algsrandom.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    AlgsRandom::initialize();

    int i = 0;
    while (i < 100)
    {
        cout << AlgsRandom::random() << endl;
        ++i;
    }
    return 0;
}
