#include <iostream>
#include <cassert>
#include <algorithm>
#include "algsrandom.h"
#include "algs_type.h"
#include "algstl_array.h"

using namespace std;
using namespace algstl;
using namespace algs;

template<typename T>
void shuffle(algstl::Array<T> &a)
{
    for (auto i = 0u; i < a.size(); ++i)
    {
        auto j = i + AlgsRandom::uniform((Int)a.size() - i);
        Double tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}

template<typename T>
void shuffle2(algstl::Array<T> &a)
{
    for (auto i = 0u; i < a.size(); ++i)
    {
        auto j = AlgsRandom::uniform((Int)a.size());
        Double tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}

int main(int argc, char *argv[])
{
    assert(argc == 3);
    Int m = Num::parseInt(argv[1]);
    Int n = Num::parseInt(argv[2]);

    Array<Int> a(0, m);
    Array<Array<Int>> b(Array<Int>(0, m), m);

    for (auto i = 0; i < n; ++i)
    {
        for (auto j = 0; j < m; ++j)
        {
            a[j] = j;
        }

        //AlgsRandom::shuffle(a);
        shuffle2(a);

        for (auto j = 0; j < m; ++j)
        {
            ++b[a[j]][j];
        }
    }

    for (auto i = 0; i < m; ++i)
    {
        for (auto j = 0; j < m; ++j)
        {
            cout << b[i][j] << "  ";
        }
        cout << endl;
    }

    return 0;
}
