#include "misc.h"

std::ostream &operator<<(std::ostream &os, const Accumulator &rhs)
{
    return (os << rhs.mean() << "(" << rhs.v_ << "/" << rhs.c_ << ")");
}
