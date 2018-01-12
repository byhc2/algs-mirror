#include <iostream>
#include "accumulator.h"
#include "algsnum.h"
#include "algsdraw.h"
#include "algsrandom.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    assert(argc == 2);
    Int n = Num::parseInt(argv[1]);

    AlgsRandom::initialize();
    AlgsDraw::setXscale(-1, n + 1);
    AlgsDraw::setYscale(0, 1);
    AlgsDraw::setPenRadius(1.0);

    Accumulator acc;
    for (auto i = 0; i < n; ++i)
    {
        auto x = AlgsRandom::random();
        AlgsDraw::setPenColor(AlgsDraw::Color());
        AlgsDraw::point(i, x);
        acc += x;
        AlgsDraw::setPenColor(AlgsDraw::Color(1.0, 0, 0));
        AlgsDraw::point(i, acc.mean());
    }
    cout << acc << endl;
    AlgsDraw::show();

    return 0;
}
