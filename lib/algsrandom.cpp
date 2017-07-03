#include <cstdlib>
#include <sys/random.h>
#include <unistd.h>
#include <ctime>
#include <cmath>
#include "algsrandom.h"

namespace algs
{

Void AlgsRandom::initialize(long seed)
{
    static char s[256]; //相当于用一个buffer来保存random的中间状态，所以这里需要用static
    getrandom(s, 256, 0);
    initstate(time(NULL) + getpid(), s, 256);
    return;
}

Double AlgsRandom::random()
{
    return static_cast<double>(::random()) / RAND_MAX;
}

Int AlgsRandom::uniform(Int N)
{
    return ::random() % N;
}

Int AlgsRandom::uniform(Int lo, Int hi)
{
    return ::random() % (hi - lo) + lo;
}

Double AlgsRandom::uniform(Double lo, Double hi)
{
    return AlgsRandom::random() * (hi - lo) + lo;
}

Bool AlgsRandom::bernoulli(Double p)
{
    return AlgsRandom::random() < p ? true : false;
}

//采用极坐标形式的Box-Muller变换
Double AlgsRandom::gaussian()
{
    double x, y, r;

    do
    {
        x = AlgsRandom::random() * 2 - 1;
        y = AlgsRandom::random() * 2 - 1;
        r = x * x + y * y;
    }
    while (r > 1.0 || r == 0); //去掉不合理的随机点

    return x * ::sqrt(-2.0 * ::log(r) / r);
}

Double AlgsRandom::gaussian(Double m, Double s)
{
    return AlgsRandom::gaussian() * s + m;
}

}
