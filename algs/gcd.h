#ifndef __ALGS_GCD__
#define __ALGS_GCD__

namespace algs
{

template<typename _T>
_T gcd(_T a, _T b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

}

#endif
