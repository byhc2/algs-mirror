#include "algsdraw.h"
#include "algsmath.h"

using namespace algs;

int main(int argc, char *argv[])
{
    const Int N = 50;

    Double a[N];

    for (auto i = 0; i < N; ++i)
    {
        a[i] = AlgsRandom::random();
    }

    AlgsDraw::setXscale(0, 1);
    for (auto i = 0; i < N; ++i)
    {
    }

    AlgsDraw::setPenRadius(1);

    for (int i = 1; i <= N; ++i)
    {
        AlgsDraw::point(i, i);
        AlgsDraw::point(i, i * i);
        AlgsDraw::point(i, AlgsMath::log(i));
    }

    AlgsDraw::show();

    return 0;
}
