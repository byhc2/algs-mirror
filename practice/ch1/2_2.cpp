#include <unistd.h>
#include <cassert>
#include <iostream>
#include "algsnum.h"
#include "algstl_array.h"
#include "geometry.h"

using namespace std;
using namespace algs;
using namespace algstl;

int main(int argc, char *argv[])
{
    int c;
    Int n = -1;
    while ((c = getopt(argc, argv, "n:")) != -1)
    {
        switch (c)
        {
        case 'n':
            n = Num::parseInt(optarg);
            break;
        default:
            cerr << "usage: " << argv[0] << " -n<num>" << endl;
            return -1;
            break;
        }
    }
    if (n == -1)
    {
        cerr << "usage: " << argv[0] << " -n<num>" << endl;
        return -1;
    }

    Array<Interval1D> intervals;

    for (auto i = 0; i < n; ++i)
    {
        Double x, y;
        cin >> x >> y;
        intervals += Interval1D(x, y);
    }

    intervals.sort(
        [](const Interval1D &l, const Interval1D &r) { return l.lo_ < r.lo_; });

    for (decltype(intervals.size()) i = 0; i < intervals.size(); ++i)
    {
        for (auto j = i + 1; j < intervals.size(); ++j)
        {
            if (intervals[i] & intervals[j])
            {
                cout << "找到相交区间: " << intervals[i] << "和" << intervals[j]
                     << endl;
            }
        }
    }

    return 0;
}
