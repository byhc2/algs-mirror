#ifndef __ALGSTL_ALGOBASE__
#define __ALGSTL_ALGOBASE__

#include "algs_type.h"

namespace algstl
{

template<typename _T>
Void swap(_T &lhs, _T &rhs)
{
    _T t = lhs;
    lhs = rhs;
    rhs = t;
}

}

#endif
