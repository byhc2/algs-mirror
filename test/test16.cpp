#include "algsdraw.h"

using namespace algs;

int main(int argc, char *argv[])
{
    AlgsDraw::setXscale(-10, 10);
    AlgsDraw::setYscale(-10, 10);
    AlgsDraw::line(0, 0, 10, 10);
    AlgsDraw::point(1, 2);
    AlgsDraw::point(1, 3);
    AlgsDraw::point(1, 4);
    AlgsDraw::setPenColor(AlgsDraw::Color(1.0, 0, 0));
    AlgsDraw::text(0, 0, "Hello world");
    AlgsDraw::circle(0, 0, 10);
    AlgsDraw::circle(0, 0, 10);
    AlgsDraw::filledCircle(0, 5, 3);
    AlgsDraw::rectangle(0, 0, 3, 4);
    AlgsDraw::show();
    return 0;
}
