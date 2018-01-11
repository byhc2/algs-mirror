#ifndef __UTILALGS_MISC__
#define __UTILALGS_MISC__

#include <iostream>
#include "algs_type.h"
#include "algsnum.h"
#include "algsstring.h"

class Date
{
    public:
    Date(Int year, Int month, Int day) : year_(year), month_(month), day_(day)
    {}

    Int day()
    {
        return day_;
    }
    Int year()
    {
        return year_;
    }
    Int month()
    {
        return month_;
    }

    algs::String toString(bool desc = false)
    {
        if (!desc)
        {
            return algs::Num::toString(year_) + "-"
                   + algs::Num::toString(month_) + "-"
                   + algs::Num::toString(day_);
        }

        algs::String ret = algs::Num::toString(year_) + "年"
                           + algs::Num::toString(month_) + "月"
                           + algs::Num::toString(day_) + "日";
        //此处涉及练习2.12，因星期几这个问题比较虚妄
        //涉及格里高利历和凯撒历的切换，且我不认同这种历法的合理性
        //故此处不再继续
    }

    private:
    Int year_;
    Int month_;
    Int day_;
};

class Transaction
{
    // TODO 暂不实现
};

class Accumulator
{
    friend std::ostream &operator<<(std::ostream &os, const Accumulator &rhs);

    public:
    Accumulator() : v_(0), c_(0)
    {}
    Accumulator(const Accumulator &a) : v_(a.v_), c_(a.c_)
    {}
    Accumulator &operator=(const Accumulator &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        v_ = rhs.v_;
        c_ = rhs.c_;
        return *this;
    }

    Accumulator &operator+=(Double a)
    {
        v_ += a;
        ++c_;
        return *this;
    }

    Double mean() const
    {
        return v_ / (c_ == 0 ? 1 : c_);
    }

    private:
    Double v_;
    unsigned c_;
};

#endif
