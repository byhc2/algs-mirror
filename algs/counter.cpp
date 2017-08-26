#include "counter.h"

namespace algs
{

Counter &Counter::increment()
{
    ++count_;
    return *this;
}

Int Counter::tally()
{
    return count_;
}

algs::String toString()
{
    return id_ + ": " + Num::toString(count_);
}

Counter &Counter::operator++()
{
    ++count_;
    return *this;
}

Counter Counter::operator++(int)
{
    auto tmp = *this;
    ++count_;
    return tmp;
}

std::ostream &operator<<(std::ostream &os, const Counter &rhs)
{
    os << rhs.count_;
    return os;
}

}
