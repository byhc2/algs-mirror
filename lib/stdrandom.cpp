#include <cstdlib>
#include <sys/random.h>
#include <ctime>
#include <cmath>
#include "stdrandom.h"

namespace algs
{

Void StdRandom::initialize(long seed)
{
    unsigned short s[7] = {0x12, 0x34, 0x56, 0x78, 0x90, 0x12, 0x34};
    getrandom(s, sizeof(unsigned short) * 7, 0);
    lcong48(s);
    return;
}

Double StdRandom::random()
{
    return drand48();
}

Int StdRandom::uniform(Int N)
{
    return lrand48() % N;
}

Int StdRandom::uniform(Int lo, Int hi)
{
    return lrand48() % (hi - lo) + lo;
}

Double StdRandom::uniform(Double lo, Double hi)
{
    return random() * (hi - lo) + lo;
}

Bool StdRandom::bernoulli(Double p)
{
    return random() < p ? true : false;
}

//采用极坐标形式的Box-Muller变换
Double StdRandom::gaussian()
{
    double x, y, r;

    do
    {
        x = random() * 2 - 1;
        y = random() * 2 - 1;
        r = x * x + y * y;
    }
    while (r > 1.0 || r == 0); //去掉不合理的随机点

    return x * sqrt(-2.0 * log(r) / r);
}

}
