#include "algsdraw.h"
#include "algsmath.h"

using namespace algs;

int main(int argc, char *argv[])
{
    int N = 100;

    AlgsDraw::setXscale(0, N);
    AlgsDraw::setYscale(0, N * N);
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
