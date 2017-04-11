#include <cstdlib>
#include <sys/random.h>
#include <unistd.h>
#include <ctime>
#include <cmath>
#include "stdrandom.h"

namespace algs
{

Void StdRandom::initialize(long seed)
{
    static char s[256]; //相当于用一个buffer来保存random的中间状态，所以这里需要用static
    getrandom(s, 256, 0);
    initstate(time(NULL) + getpid(), s, 256);
    return;
}

Double StdRandom::random()
{
    return static_cast<double>(::random()) / RAND_MAX;
}

Int StdRandom::uniform(Int N)
{
    return ::random() % N;
}

Int StdRandom::uniform(Int lo, Int hi)
{
    return ::random() % (hi - lo) + lo;
}

Double StdRandom::uniform(Double lo, Double hi)
{
    return StdRandom::random() * (hi - lo) + lo;
}

Bool StdRandom::bernoulli(Double p)
{
    return StdRandom::random() < p ? true : false;
}

//采用极坐标形式的Box-Muller变换
Double StdRandom::gaussian()
{
    double x, y, r;

    do
    {
        x = StdRandom::random() * 2 - 1;
        y = StdRandom::random() * 2 - 1;
        r = x * x + y * y;
    }
    while (r > 1.0 || r == 0); //去掉不合理的随机点

    return x * sqrt(-2.0 * log(r) / r);
}

Double StdRandom::gaussian(Double m, Double s)
{
    return StdRandom::gaussian() * s + m;
}

}
