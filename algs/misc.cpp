#include "misc.h"

std::ostream &operator<<(std::ostream &os, const Accumulator &rhs)
{
    return (os << rhs.v_ << "(mean: " << rhs.mean() << ")");
}
