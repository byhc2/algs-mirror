#include <iostream>
#include "geometry.h"
#include "counter.h"
#include "algsdraw.h"
#include "algsnum.h"
#include "algsrandom.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    Double xlo = Num::parseDouble(argv[1]);
    Double xhi = Num::parseDouble(argv[2]);
    Double ylo = Num::parseDouble(argv[3]);
    Double yhi = Num::parseDouble(argv[4]);
    Int c = Num::parseInt(argv[5]);

    AlgsRandom::initialize();

    Interval2D a(Interval1D(xlo, xhi), Interval1D(ylo, yhi));

    AlgsDraw::setXscale(0, 1);
    AlgsDraw::setYscale(0, 1);

    auto x = (a.x_.lo_ + a.x_.hi_) / 2.0;
    auto y = (a.y_.lo_ + a.y_.hi_) / 2.0;
    auto rw = a.x_.hi_ - a.x_.lo_;
    auto rh = a.y_.hi_ - a.y_.lo_;
    AlgsDraw::setPenRadius(2.0);
    AlgsDraw::rectangle(x, y, rw, rh);

    Counter hits("hits");
    for (auto i = 0; i < c; ++i)
    {
        Point2D p(AlgsRandom::random(), AlgsRandom::random());
        if (a.contains(p))
        {
            ++hits;
        }
        else
        {
            AlgsDraw::point(p.x_, p.y_);
        }
    }
    cout << hits.tally() / static_cast<Double>(c) << endl;
    AlgsDraw::show();

    return 0;
}
