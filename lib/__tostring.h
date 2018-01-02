#ifndef ____TOSTRING_H__
#define ____TOSTRING_H__

#include "algsnum.h"

namespace algs
{

template<typename _T>
String toString(const _T &v)
{
    return v.toString();
}

template<>
String toString(const Int &v)
{
    return algs::Num::toString(v);
}

template<>
String toString(const Uint &v)
{
    return algs::Num::toString(v);
}

template<>
String toString(const Double &v)
{
    return algs::Num::toString(v);
}

template<>
String toString(const Bool &v)
{
    return v ? "T" : "F";
}

}

#endif
