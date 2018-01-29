#include <iostream>
#include "algstl_array.h"
#include "counter.h"

//习题1.2.9

using namespace std;
using namespace algs;
using namespace algstl;

template<typename _T>
static typename algstl::Array<_T>::SizeType lrank(const _T &key,
                                                 const algstl::Array<_T> &a,
                                                 Counter &c)
{
    if (a.size() == 0)
    {
        return -1;  //坚决防止数组大小为0的情况
    }
    typename algstl::Array<_T>::SizeType lo = 0;
    typename algstl::Array<_T>::SizeType hi = a.size() - 1;
    while (lo <= hi)
    {
        auto mid = lo + (hi - lo) / 2;
        if (key < a[mid])
        {
            ++c;
            hi = mid - 1;
        }
        else if (a[mid] < key)
        {
            ++c;
            lo = mid + 1;
        }
        else
        {
            return mid;
        }
    }

    return algstl::Array<_T>::npos;
}

int main(int argc, char *argv[])
{
    Array<Int> a;

    Int x;
    while (cin >> x)
    {
        a += x;
    }

    a.sort([](Int x, Int y) { return x < y; });

    cin.clear();
    while (cin >> x)
    {
        Counter c;
        lrank(x, a, c);
        cout << c << endl;
    }
    return 0;
}
