#include <iostream>
#include "algs_type.h"
#include "algsmath.h"
#include "algsout.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    {

    Double t = 9.0;
    while (AlgsMath::abs(t - 9.0 / t) > 0.001)
    {
        t = (9.0 / t + t) / 2.0;
    }

    AlgsStdOut::printf("%.5f\n", t);

    }

    {

    Int sum = 0;
    for (auto i = 0; i < 1000; ++i)
    {
        sum++;
    }
    cout << sum << endl;

    }

    {

    Int sum = 0;
    for (auto i = 1; i < 1000; i *= 2)
    {
        for (auto j = 0; j < 1000; ++j)
        {
            sum++;
        }
    }
    cout << sum << endl;

    }

    {
        AlgsStdOut::println('b');
        AlgsStdOut::println('b' + 'c');
        AlgsStdOut::println((char)('b' + 4));
    }

    return 0;
}
