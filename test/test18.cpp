#include "algsdraw.h"
#include "algsrandom.h"
#include "algstl_array.h"

using namespace algs;
using namespace algstl;

int main(int argc, char *argv[])
{
    const Int N = 50;

    Array<Double> a;

    AlgsRandom::initialize();
    for (auto i = 0; i < N; ++i)
    {
        a += AlgsRandom::random();
    }

    a.sort([](const Double &a, const Double &b) {return a < b;});

    AlgsDraw::setXscale(0, 1);
    AlgsDraw::setYscale(0, 1);
    for (auto i = 0; i < N; ++i)
    {
        Double x = 1.0 * i / N;
        Double y = a[i] / 2.0;
        Double rw = 0.5 / N;
        Double rh = a[i];
        AlgsDraw::filledRectangle(x + rw, y, rw, rh);
    }

    AlgsDraw::show();

    return 0;
}
