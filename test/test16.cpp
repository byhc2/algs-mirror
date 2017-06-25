#include "algsdraw.h"

using namespace algs;

int main(int argc, char *argv[])
{
    AlgsDraw::setXscale(-12, 15);
    AlgsDraw::setYscale(0, 15);
    AlgsDraw::line(0, 0, 10, 10);
    AlgsDraw::point(1, 2);
    AlgsDraw::point(1, 3);
    AlgsDraw::point(1, 4);
    AlgsDraw::show();
    return 0;
}
