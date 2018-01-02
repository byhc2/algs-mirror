#include <iostream>
#include "geometry.h"
#include "algsnum.h"
#include "algsrandom.h"
#include "algsdraw.h"
#include "algsmath.h"
#include "algstl_array.h"

using namespace std;
using namespace algs;
using namespace algstl;

int main(int argc, char *argv[])
{
    assert(argc == 2);
    AlgsRandom::initialize();

    Int n = Num::parseInt(argv[1]);
    Array<Point2D> points;

    AlgsDraw::setXscale(0, 1);
    AlgsDraw::setYscale(0, 1);
    AlgsDraw::setPenRadius(3.0);

    for (auto i = 0; i < n; ++i)
    {
        auto x = AlgsRandom::random();
        auto y = AlgsRandom::random();
        points += Point2D(x, y);

        AlgsDraw::point(x, y);
    }
    decltype(points.size()) a, b;
    a = 0;
    b = 0;
    Double min_distance = 2.1; //单位正方形内任意两点间距平方不会超过2.0
    for (auto i = 0; i < points.size(); ++i)
    {
        for (auto j = i; j < points.size(); ++j)
        {
            if (i == j)
            {
                continue;
            }

            auto d = AlgsMath::pow(points[i].x_ - points[j].x_, 2)
                + AlgsMath::pow(points[i].y_ - points[j].y_, 2);
            if (d < min_distance)
            {
                min_distance = d;
                a = i;
                b = j;
            }
        }
    }
    cout << "任意两点间距离最短为" << min_distance << endl;

    AlgsDraw::line(points[a].x_, points[a].y_,
            points[b].x_, points[b].y_);

    AlgsDraw::show();

    return 0;
}
