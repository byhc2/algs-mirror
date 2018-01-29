#include <unistd.h>
#include <iostream>
#include "algsdraw.h"
#include "algsmath.h"
#include "algsnum.h"
#include "algsrandom.h"
#include "algstl_array.h"
#include "geometry.h"

using namespace std;
using namespace algs;
using namespace algstl;

//习题1.2.1

int main(int argc, char *argv[])
{
    int c;
    Int n = -1;
    while ((c = getopt(argc, argv, "n:")) != -1)
    {
        switch (c)
        {
        case 'n':
            n = atoi(optarg);
        default:
            cout << "usage: " << argv[0] << " -n<num>" << endl;
        }
    }

    if (n == -1)
    {
        cout << "usage: " << argv[0] << " -n<num>" << endl;
        return -1;
    }

    AlgsRandom::initialize();

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
    a                   = 0;
    b                   = 0;
    Double min_distance = 2.1;  //单位正方形内任意两点间距平方不会超过2.0
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
                a            = i;
                b            = j;
            }
        }
    }
    cout << "任意两点间距离最短为" << min_distance << endl;

    AlgsDraw::line(points[a].x_, points[a].y_, points[b].x_, points[b].y_);

    AlgsDraw::show();

    return 0;
}
