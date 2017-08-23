#include <iostream>
#include <iomanip>
#include <algs_type.h>
#include "algstl_array.h"

using namespace std;
using namespace algstl;
using namespace algs;

int main(int argc, char *argv[])
{
    const Int SIDES = 6;
    Array<Double> a(0.0, 2 * SIDES + 1);

    for (auto i = 1; i <= SIDES; ++i)
    {
        for (auto j = 1; j <= SIDES; ++j)
        {
            a[i + j] += 1;
        }
    }
    for (auto i = 2; i <= 2 * SIDES; ++i)
    {
        a[i] /= SIDES * SIDES;
    }

    for (auto i = 2; i <= 2 * SIDES; ++i)
    {
        cout << setprecision(3) << a[i] << endl;
    }

    //实验：
    Int n = Num::parseInt(argv[1]);

    return 0;
}
