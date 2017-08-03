#include <iostream>
#include "algs_type.h"
#include "algstl_array.h"
#include "algsnum.h"

using namespace std;
using namespace algs;
using namespace algstl;

Ulong recursive_counter = 0;

Array<Array<Double>> preload;

//经过观察，n < k时，递归调用次数为 2 ^ (n + 2) - 1次
//n > k时，结果可能是一个k + 1阶的等差数列
//所以binomial(100, 50, p)差不多是一个51阶等差数列，调用次数大约为100 ^ 51次
//
//备注，使用http://www.wolframalpha.com验证，k = 2时
//递归从n = 4开始，递归次数满足：63, 97, 143, 203, 279 ...
//通项公式：(n^3 + 12n^2 + 59n + 117) / 3
//
//k = 3时，递归从n = 5开始
Double binomial(Int n, Int k, Double p)
{
    ++recursive_counter;
    if (n == 0 && k == 0)
        return 1.0;
    if (n < 0 || k < 0)
        return 0.0;
    return (1.0 - p) * binomial(n - 1, k, p) + p * binomial(n - 1, k - 1, p);
}

int main(int argc, char *argv[])
{
    binomial(Num::parseInt(argv[1]), Num::parseInt(argv[2]), 0.5);
    cout << recursive_counter << endl;

    return 0;
}
