#ifndef __UTILALGS_MISC__
#define __UTILALGS_MISC__

#include "algs_type.h"

class Date
{
    //TODO 暂不实现
};

class Transaction
{
    //TODO 暂不实现
};

class Accumulator
{
friend std::ostream &operator<<(std::ostream &os, const Counter &rhs);
public:
    Accumulator(): v_(0), c_(0) {}
    Accumulator(const Accumulator &a): v_(a.v_), c_(a.c_) {}
    Accumulator &operator=(const Accumulator &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        v_ = rhs.v_;
        c_ = rhs.c_;
    }

    Accumulator &operator+=(Double a)
    {
        v_ += a;
        ++c_;
        return *this;
    }

    Double mean()
    {
        return v_ / (c_ == 0 ? 1 : c_);
    }

private:
    Double v_;
    unsigned c_;
};

#endif
