#include "accumulator.h"

namespace algs
{
Accumulator::Accumulator() : v_(0), m_(0), s_(0), c_(0)
{}

Accumulator::Accumulator(const Accumulator &a)
    : v_(a.v_), m_(a.m_), s_(a.s_), c_(a.c_)
{}

Accumulator &Accumulator::operator=(const Accumulator &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    v_ = rhs.v_;
    m_ = rhs.m_;
    s_ = rhs.s_;
    c_ = rhs.c_;
    return *this;
}

//习题2.18
Accumulator &Accumulator::operator+=(Double a)
{
    //计算新的均值和方差
    //该公式与书中不同
    //一开始，我以为书中的结论是错的
    //后来发现书中结论正确，只是表述形式不同
    //书中代码的s_保存的是(n-1)Sn
    //我这里直接就算出Sn了
    if (c_ > 0)
    {
        //下面的写法是错的，因为(c_-1)/c_*s_是0
        // s_ = (c_ - 1) / c_ * s_ + (a - m_) * (a - m_) / (c_ + 1);
        s_ = s_ * (c_ - 1) / c_ + (a - m_) * (a - m_) / (c_ + 1);
        m_ = (c_ * m_ + a) / (c_ + 1);
        v_ += a;
        ++c_;
    }
    else  //第一个数要区别对待
    {
        s_ = 0;
        m_ = a;
        v_ += a;
        ++c_;
    }
    return *this;
}

Double Accumulator::mean() const
{
    return m_;
}

Double Accumulator::var() const
{
    if (c_ > 1)
    {
        return s_;
    }
    else
    {
        return 0;
    }
}

std::ostream &operator<<(std::ostream &os, const Accumulator &rhs)
{
    return (os << rhs.mean() << "(" << rhs.v_ << "/" << rhs.c_ << ")");
}
}
