#ifndef __ALGSTL_DEQUE__
#define __ALGSTL_DEQUE__

#include "algstl_iterator.h"
#include "algstl_memory.h"

//双向队列

namespace algstl
{
//或为我实现之最复杂迭代器
template<typename _T, typename _Alloc>
class DequeIterator
{
    public:
    typedef _T ValueType;
    typedef _T *Pointer;
    typedef _T &Reference;
    typedef _Alloc Allocator;
    DequeIterator()
    {}

    private:
    Pointer start_;
    Pointer end_;
    Pointer 
};

template<typename _T, typename _Alloc = Allocator<_T>>
class Deque
{
    public:
    typedef _T ValueType;
    typedef _T *Pointer;
    typedef _T &Reference;
    typedef _Alloc Allocator;
    typedef Deque Deque()
    {}

    private:
    Pointer *map_;  //二级索引的指针
};
};

#endif
