#include "geometry.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    auto i1 = Interval1D(0,2);
    auto i2 = Interval1D(1,3);

    cout << (i1 & i2) << endl;

    return 0;
}
