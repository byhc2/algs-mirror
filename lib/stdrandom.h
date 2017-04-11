#ifndef __ALGS_STDRANDOM__
#define __ALGS_STDRANDOM__

#include <cstring>
#include "algs_type.h"

namespace algs
{

class StdRandom
{
public:
    static   Void initialize(Long seed=0);
    static Double random(); //返回[0, 1)之间的浮点数
    static    Int uniform(Int N); //[0, N - 1]之间的整数，N < 2^31
    static    Int uniform(Int lo, Int hi); //[lo, hi - 1]之间的数，hi < 2^31
    static Double uniform(Double lo, Double hi); //[lo, hi]之间的浮点数
    static   Bool bernoulli(Double p); //以p的概率返回true
    static Double gaussian(); //返回N(0, 1)分布的浮点数
    static Double gaussian(Double m, Double s);

    //因为discrete函数不能保存状态，因此这里使用线性探查法而非别名方法（Alias
    //method），在n较小时性能问题不大
    template<Int n>
    static Int discrete(Double (&a)[n])
    {
        Double b[n + 1];
        memcpy(&b[1], a, n * sizeof(Double));

        for (auto i = 1; i < n + 1; ++i)
        {
            b[i] += b[i - 1];
        }

        //如果概率表的最大概率不为1，这里的乘号恰好起归一化作用
        Double r = StdRandom::random() * b[n];

        for (auto i = 0; i < n; ++i)
        {
            if (r > b[i] && r < b[i + 1])
            {
                return i;
            }
        }

        return -1; //应该不会到这里
    }
private:
};

}

#endif
