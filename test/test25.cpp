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
    Double xlo = Num::parseInt(argv[1]);
    Double xhi = Num::parseInt(argv[2]);
    Double ylo = Num::parseInt(argv[3]);
    Double yhi = Num::parseInt(argv[4]);
    Int c = Num::parseInt(argv[5]);

    AlgsRandom::initialize();

    Interval2D a(Interval1D(xlo, xhi), Interval1D(ylo, yhi));

    AlgsDraw::setXscale(0, 1);
    AlgsDraw::setYscale(0, 1);

    cout << a.x_.lo_ << endl;
    cout << a.x_.hi_ << endl;
    cout << a.y_.lo_ << endl;
    cout << a.y_.hi_ << endl;

    auto x = (a.x_.lo_ + a.x_.hi_) / 2.0;
    auto y = (a.y_.lo_ + a.y_.hi_) / 2.0;
    auto rw = a.x_.hi_ - a.x_.lo_;
    auto rh = a.y_.hi_ - a.y_.lo_;
    cout << x << " " << y << " " << rw << " " << rh << endl;
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
    AlgsDraw::show();

    return 0;
}
