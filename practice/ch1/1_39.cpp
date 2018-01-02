#include <iostream>
#include <cassert>
#include <algorithm>
#include "algsrandom.h"
#include "algsmath.h"
#include "algs_type.h"
#include "algstl_array.h"
#include "binary_search.h"

using namespace std;
using namespace algs;
using namespace algstl;

Int fun(Int n)
{
    Array<Int> a;
    Array<Int> b;

    Int ret = 0;

    for (auto i = 0; i < n; ++i)
    {
        a += AlgsRandom::uniform(100000, 1000000);
    }
    for (auto i = 0; i < n; ++i)
    {
        b += AlgsRandom::uniform(100000, 1000000);
    }

    a.sort([](const Int a, const Int b) {return a < b;});

    for (auto i = 0; i < b.size(); ++i)
    {
        if (BinarySearch::rank(b[i], a) != -1)
        {
            ++ret;
        }
    }

    return ret;
}

int main(int argc, char *argv[])
{
    auto t = Num::parseInt(argv[1]);
    AlgsRandom::initialize();

    for (auto i = 3; i <= 6; ++i)
    {
        auto n = static_cast<decltype(i)>(AlgsMath::pow(10, i));
        Int sum = 0;
        for (auto i = 0; i < t; ++i)
        {
            sum += fun(n);
        }

        cout << i << ": " << sum / static_cast<Double>(t) << endl;
    }

    return 0;
}
