#include <iostream>
#include "algsdraw.h"
#include "algsmath.h"
#include "algsnum.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    Int n = Num::parseInt(argv[1]);
    Double p = Num::parseDouble(argv[2]);

    //假定圆的半径为1
    AlgsDraw::setXscale(-1.2, 1.2);
    AlgsDraw::setYscale(-1.2, 1.2);
    AlgsDraw::setPenRadius(1.0);
    AlgsDraw::circle(0, 0, 1.0);
    AlgsDraw::setPenRadius(4.0);
    AlgsDraw::setPenColor(AlgsDraw::Color(0.0, 0.0, 0.0));

    Double step = 2 * AlgsMath::pi_ / n;
    Double w = 0;

    for (auto i = 0; i < n; ++i)
    {
        Double x = AlgsMath::cos(w);
        Double y = AlgsMath::sin(w);

        cout << x << ", " << y << endl;

        AlgsDraw::point(x, y);

        w += step;
    }

    AlgsDraw::show();

    return 0;
}
