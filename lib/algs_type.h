#ifndef __ALGS_TYPE__
#define __ALGS_TYPE__

#include <cstddef>

//为满足类型命名一致性而定义
typedef int Int;
typedef double Double;
typedef long double Ldouble;
typedef long Long;
typedef void Void;
typedef bool Bool;
typedef char Char;
typedef unsigned Uint;
typedef unsigned char Uchar;
typedef unsigned long Ulong;
typedef ptrdiff_t PtrDiff;
typedef Uint SizeType;

#if 0
namespace algs
{

template<typename T>
String toString(const T &v)
{
    return v.toString();
}

template<>
String toString(const Char v)
{
    String(&v, 1);
}

}
#endif

#endif
