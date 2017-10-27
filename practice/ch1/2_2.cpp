#include <iostream>
#include <cassert>
#include "geometry.h"
#include "algsnum.h"
#include "algstl_array.h"

using namespace std;
using namespace algs;
using namespace algstl;

int main(int argc, char *argv[])
{
    assert(argc == 2);

    Int n = Num::parseInt(argv[1]);
    Array<Interval1D> intervals;

    for (auto i = 0; i < n; ++i)
    {
        Double x, y;
        cin >> x >> y;
        intervals += Interval1D(x, y);
    }

    intervals.sort([](const Interval1D &l, const Interval1D &r)
            { return l.lo_ < r.lo_; });

    for (auto &r: intervals)
    {
        cout << r.lo_ << endl;
    }

    return 0;
}
