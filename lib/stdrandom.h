#ifndef __ALGS_STDRANDOM__
#define __ALGS_STDRANDOM__

#include <ctime>
#include <random>

namespace algs
{

class StdRandom
{
public:
    static   void initialize(long seed=time(NULL));
    static double random(); //返回[0, 1]之间的浮点数
    static    int uniform(int N); //[0, N - 1]之间的整数
    static    int uniform(int lo, int hi); //[lo, hi - 1]之间的数
    static double uniform(double lo, double hi); //[lo, hi]之间的浮点数
private:
    //真随机数
    static std::random_device *_rd;
};

}

#endif
