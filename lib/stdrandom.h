#ifndef __ALGS_STDRANDOM__
#define __ALGS_STDRANDOM__

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
private:
};

}

#endif
