#include <iostream>
#include "algs_type.h"
#include "algstl_array.h"
#include "algsrandom.h"

using namespace std;
using namespace algstl;

Array<Int> histgram(const Array<Int> &a)
{
    Array<Int> hist(0, a.size());
    for (auto r: a)
    {
        hist[r] += 1;
    }
    return hist;
}

#define N 1000
int main(int argc, char *argv[])
{
    Array<Int> a(N);
    for (auto i = 0; i < N; ++i)
    {
        a[i] = algs::AlgsRandom::uniform(N);
    }

    auto r = histgram(a);

    cout << r.toString() << endl;

    return 0;
}
