#include "counter.h"
#include "algsnum.h"

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

algs::String Counter::toString()
{
    return id_ + ": " + Num::toString(count_);
}

Counter &Counter::operator++()
{
    ++count_;
    return *this;
}

Counter Counter::operator++(Int)
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

Counter &operator=(const Counter &rhs)
{
    if (this == $rhs)
    {
        return *this;
    }

    id_ = rhs.id_;
    count_ = rhs.count_;

    return *this;
}

}
