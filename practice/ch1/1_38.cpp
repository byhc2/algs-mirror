#include <iostream>
#include <cassert>
#include <algorithm>
#include "algsrandom.h"
#include "algs_type.h"
#include "algstl_array.h"
#include "binary_search.h"

using namespace std;
using namespace algs;
using namespace algstl;

template<typename _T>
typename algstl::Array<_T>::SizeType brouteForceSearch(const _T &key, const algstl::Array<_T> &a)
{
    for (auto i = 0; i < a.size(); ++i)
    {
        if (a[i] == key)
        {
            return i;
        }
    }

    return -1;
}

int main(int argc, char *argv[])
{
    assert(argc == 4);

    auto method = Num::parseInt(argv[1]);
    ifstream r(argv[2]);
    ifstream t(argv[3]);

    Int x;
    Array<Int> arr;
    while (r >> x)
    {
        arr += x;
    }
    cin.clear();

    arr.sort([](const Int a, const Int b) {return a < b;});
    while (t >> x)
    {
        decltype(brouteForceSearch(0, arr)) ret;
        if (method == 1)
        {
            ret = BinarySearch::rank(x, arr);
        }
        else
        {
            ret = brouteForceSearch(x, arr);
        }

        if (ret != static_cast<decltype(ret)>(-1))
        {
            cout << x << endl;
        }
    }

    return 0;
}
