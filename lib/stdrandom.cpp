#include "stdrandom.h"

namespace algs
{

std::random_device *StdRandom::_rd = 0;

void StdRandom::initialize(long seed)
{
    if (!_rd)
    {
        _rd = new std::random_device;
    }
}

double StdRandom::random()
{
    initialize();
    return static_cast<double>((*_rd)()) / _rd->max();
}

int StdRandom::uniform(int N)
{
    initialize();
    //转化为long是为了避免结果出现负数
    //_rd()返回unsigned类型，扩展成long时
    //先按无符号类型进行位扩展，再转换为long
    //因此结果一定是正数
    return static_cast<long>((*_rd)()) % N;
}

int StdRandom::uniform(int lo, int hi)
{
    initialize();
    return static_cast<long>((*_rd)()) % (hi - lo) + lo;
}

double StdRandom::uniform(double lo, double hi)
{
    initialize();
    return random() * (hi - lo) + lo;
}

}
