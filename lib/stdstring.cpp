#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "stdstring.h"

namespace algs
{

String operator+(const String &lhs, const String &rhs)
{
    String ret(lhs.size() + rhs.size());
    ret.append(lhs.c_str(), lhs.size());
    ret.append(rhs.c_str(), rhs.size());

    return ret;
}

String operator+(const String &lhs, const Char *rhs)
{
    auto rhs_size = strlen(rhs);
    String ret(lhs.size() + rhs_size);
    ret.append(lhs.c_str(), lhs.size());
    ret.append(rhs, rhs_size);

    return ret;
}

String operator+(const Char *lhs, const String &rhs)
{
    auto lhs_size = strlen(lhs);
    String ret(lhs_size + rhs.size());
    ret.append(lhs, lhs_size);
    ret.append(rhs.c_str(), rhs.size());

    return ret;
}

}
