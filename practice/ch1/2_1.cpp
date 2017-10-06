#include <iostream>
#include "geometry.h"
#include "algsnum.h"
#include "algsrandom.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    assert(argc == 2);
    AlgsRandom::initialize();

    Int n = Num::parseInt(argv[1]);

    for (auto i = 0; i < n; ++i)
    {
        auto x = AlgsRandom::random();
        auto y = AlgsRandom::random();
    }
}
