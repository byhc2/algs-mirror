#include <iostream>
#include "algsdraw.h"
#include "algsmath.h"
#include "algsnum.h"
#include "algsrandom.h"
#include "algstl_array.h"

using namespace std;
using namespace algs;
using namespace algstl;

int main(int argc, char *argv[])
{
    AlgsRandom::initialize();

    Int n = Num::parseInt(argv[1]);
    Int m = Num::parseInt(argv[2]);
    Double l = Num::parseDouble(argv[3]);
    Double r = Num::parseDouble(argv[4]);

    auto step = (r - l) / n;
    Array<Int> arr(0, n + 1);
    Int max = 0;

    for (auto i = 0; i < m; ++i)
    {
        Uint v = AlgsRandom::uniform(l, r) / step;
        arr[v]++;
        if (arr[v] > max)
        {
            max = arr[v];
        }
    }

    cout << max << endl;

    //直方图
    AlgsDraw::setXscale(-0.5, arr.size() + 0.5);
    AlgsDraw::setYscale(0, max + 1);
    for (auto i = 0u; i < arr.size(); ++i)
    {
        Double x = i;
        Double y = arr[i] / 2.0;
        Double rw = 0.4;
        Double rh = arr[i];
        cout << x << "\t" << y << "\t" << rw << "\t" << rh << endl;
        AlgsDraw::filledRectangle(x, y, rw, rh);
    }
    AlgsDraw::show();

    return 0;
}
