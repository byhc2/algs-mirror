#include <iostream>
#include <iomanip>
#include <algs_type.h>
#include "algstl_array.h"
#include "algsrandom.h"

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
        cout << Num::toString(a[i], 3, 11) << "\t";
    }
    cout << endl;

    //实验：
    Int n = Num::parseInt(argv[1]);
    AlgsRandom::initialize();
    Array<Int> b(0, 2 * SIDES + 1);
    for (auto i = 0; i < n; ++i)
    {
        //模拟掷两次骰子
        auto x = AlgsRandom::uniform(1, 7); //[1, 7)之间的均匀分布
        auto y = AlgsRandom::uniform(1, 7); //[1, 7)之间的均匀分布

        ++b[x + y];
    }
    for (auto i = 2; i <= 2 * SIDES; ++i)
    {
        cout << b[i] << "\t";
    }
    cout << endl;

    for (auto i = 2; i <= 2 * SIDES; ++i)
    {
        cout << Num::toString(b[i] / static_cast<Double>(n), 3, 11) << "\t";
    }
    cout << endl;

    //实验结果：掷骰子次数大于等于562974576时，结果与理论一致（3位小数精度）
    //环境：Vbox虚拟机，archlinux

    return 0;
}
