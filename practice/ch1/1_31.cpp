#include <iostream>
#include "algsdraw.h"
#include "algsmath.h"
#include "algsnum.h"
#include "algsrandom.h"
#include "algstl_array.h"

using namespace std;
using namespace algs;
using namespace algstl;

//写不出来tuple类，暂时用这个
struct Point
{
    Double x_;
    Double y_;

    Point(Double x, Double y): x_(x), y_(y) {}
};

int main(int argc, char *argv[])
{
    Int n = Num::parseInt(argv[1]);
    Double p = Num::parseDouble(argv[2]);

    //假定圆的半径为1
    AlgsDraw::setXscale(-1.2, 1.2);
    AlgsDraw::setYscale(-1.2, 1.2);
    AlgsDraw::setPenRadius(0.1);
    AlgsDraw::circle(0, 0, 1.0);
    AlgsDraw::setPenRadius(1.0);
    AlgsDraw::setPenColor(AlgsDraw::Color(0.0, 0.0, 0.4));

    Double step = 2 * AlgsMath::pi_ / n;
    Double w = 0;

    Array<Point> points;

    for (auto i = 0; i < n; ++i)
    {
        Double x = AlgsMath::cos(w);
        Double y = AlgsMath::sin(w);

        cout << x << ", " << y << endl;

        AlgsDraw::point(x, y);

        points += Point(x, y);

        w += step;
    }

    //随机连接
    AlgsDraw::setPenRadius(0.1);
    for (auto i = 0u; i < points.size(); ++i)
    {
        for (auto j = i; j < points.size(); ++j)
        {
            if (AlgsRandom::bernoulli(p))
            {
                AlgsDraw::line(points[i].x_,
                        points[i].y_,
                        points[j].x_,
                        points[j].y_);
            }
        }
    }

    AlgsDraw::show();

    return 0;
}
