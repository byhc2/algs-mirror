#ifndef __ALGSTL_ARRAY__
#define __ALGSTL_ARRAY__

//动态数组，基本同stl中vector

#include "algstl_memory.h"
#include "algstl_iterator.h"

namespace algstl
{

template<typename _T, typename _Alloc=Allocator<_T>>
class Array
{
public:
    typedef _T ValueType;
    typedef _Alloc Allocator;
    typedef _T* Iterator;
    typedef typename algstl::ReverseIterator<Iterator> ReverseIterator;
    typedef DifferenceType SizeType;

    Array()
    {
        start_ = nullptr;
        end_ = nullptr;
        cap_ = nullptr;
    }

    ~Array()
    {
        //TODO
    }

    SizeType size()
    {
        return end_ - start_;
    }

    Array<ValueType> &operator+(const ValueType &rhs)
    {
        if (end_ + 1 == cap_)
        {
            //需要重新分配内存
            ValueType *tmp = alloc_.allocate(size() * incr_fact);
        }
    }

private:
    ValueType *start_;
    ValueType *end_;
    ValueType *cap_;
    static const Double incr_fact = 1.5;
};

}

#endif
