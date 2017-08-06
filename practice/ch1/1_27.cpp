#include <iostream>
#include "algs_type.h"
#include "algstl_array.h"
#include "algsnum.h"

using namespace std;
using namespace algs;
using namespace algstl;

Ulong recursive_counter = 0;

//经过观察，n < k时，递归调用次数为 2 ^ (n + 2) - 1次
//n > k时，结果可能是一个k + 1阶的等差数列
//所以binomial(100, 50, p)差不多是一个51阶等差数列，调用次数大约为100 ^ 51次
//
//备注，使用http://www.wolframalpha.com验证，k = 2时
//递归从n = 4开始，递归次数满足：63, 97, 143, 203, 279 ...
//通项公式：(n^3 + 12n^2 + 59n + 117) / 3
//
//k = 3时，递归从n = 5开始，递归次数满足：93 157 255 399 603 883 1257 1745 2369
//通项公式：(n^4 + 14n^3 + 95n^2 + 370n + 636) / 12
//
//综上，大约递归次数的数量级为 n^(k + 1)

Double binomial1(Int n, Int k, Double p)
{
    ++recursive_counter;
    if (n == 0 && k == 0)
        return 1.0;
    if (n < 0 || k < 0)
        return 0.0;
    return (1.0 - p) * binomial1(n - 1, k, p) + p * binomial1(n - 1, k - 1, p);
}

Array<Array<Double>> *preload = nullptr;
Double binomial2(Int n, Int k, Double p)
{
    if (!preload)
    {
        cout << "this should only once" << endl;
        preload = new Array<Array<Double>>(Array<Double>(-1.0, k + 1), n + 1);
        assert(preload);
    }

    if (n == 0 && k == 0)
    {
        (*preload)[n][k] = 1.0;
        return (*preload)[n][k];
    }
    else if (n < 0 || k < 0)
    {
        return 0.0;
    }
    else if ((*preload)[n][k] == -1.0)
    {
        auto v1 = binomial2(n - 1, k, p);
        auto v2 = binomial2(n - 1, k - 1, p);
        (*preload)[n][k] = (1.0 - p) * v1 + p * v2;
        return (*preload)[n][k];
    }
    else
    {
        return (*preload)[n][k];
    }
}

int main(int argc, char *argv[])
{
    cout << binomial2(Num::parseInt(argv[1]), Num::parseInt(argv[2]), 0.5) << endl;

    return 0;
}
