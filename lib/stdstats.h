#ifndef __ALGS_STDSTATS__
#define __ALGS_STDSTATS__

#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include "algs_type.h"

namespace algs
{

class StdStats
{
public:
    template<Int n>
    static Double max(Double (&a)[n])
    {
        assert(n > 0);

        double m = a[0];
        for (auto x: a)
        {
            m = x > m ? x : m;
        }

        return m;
    }

    template<Int n>
    static Double min(Double (&a)[n])
    {
        assert(n > 0);

        double m = a[0];
        for (auto x: a)
        {
            m = x < m ? x : m;
        }

        return m;
    }

    template<Int n>
    static Double mean(Double (&a)[n])
    {
        assert(n > 0);

        double s = 0.0;
        for (auto x: a)
        {
            s += x;
        }

        return s / n;
    }

    template<Int n>
    static Double var(Double (&a)[n])
    {
        assert(n > 1);

        auto mean = StdStats::mean(a);
        Double s = 0.0;

        for (auto x: a)
        {
            auto v = x - mean;
            s += v * v;
        }

        return s / (n - 1);
    }

    template<Int n>
    static Double stddev(Double (&a)[n])
    {
        assert(n > 1);
        return sqrt(StdStats::var(a));
    }

    template<Int n>
    static Double median(Double (&a)[n])
    {
        assert(n > 0);
        Double b[n];
        memcpy(b, a, n * sizeof(Double));

        qsort(b, n, sizeof(Double),
                [](const Void *x, const Void *y)
                {return static_cast<int>(*(static_cast<const Double *>(x)) < *(static_cast<const Double *>(y)));});

        return b[n / 2];
    }
};

}

#endif
