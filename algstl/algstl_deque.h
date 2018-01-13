#ifndef __ALGSTL_DEQUE__
#define __ALGSTL_DEQUE__

#include "algstl_iterator.h"
#include "algstl_memory.h"

//双向队列
//此处暂与sgi之deque一致
//虽然，缓冲区可变长
//缓冲区各记其首尾，辅以B树索引之
//遇随机访问，则以序号大小，于B树寻至相应缓冲区
//再寻址于缓冲区内

namespace algstl
{
const Int bufcnt = 512;
//或为我实现之最复杂迭代器
template<typename _T, typename _Alloc, Uint bufsize = 512 * sizeof(_T)>
class DequeIterator
{
    public:
    typedef _T ValueType;
    typedef _T *Pointer;
    typedef _T &Reference;
    typedef _Alloc Allocator;
    DequeIterator() : start_(0), end_(0), cur_(0)
    {}

    //以下二函数俱不检查边界
    void gotoNext()
    {
        ++map_;
        start_ = *map_;
        end_   = start_ + bufcnt;
        cur_   = start_;
    }

    void gotoPrev()
    {
        --map_;
        start_ = *map_;
        end_   = start_ + bufcnt;
        cur_   = end_ - 1;
    }

    DequeIterator &operator++()  //前置加
    {
        if (cur_ + 1 != end_)
        {
            ++cur_;
            return *this;
        }
        else
        {
            gotoNext();
            return *this;
        }
    }

    DequeIterator &operator--()
    {
        if (cur_ != start_)
        {
            --cur_;
            return *this;
        }
        else
        {
            gotoPrev();
            return *this;
        }
    }

    private:
    Pointer start_;
    Pointer end_;
    Pointer cur_;
    Pointer *map_;
};

template<typename _T, typename _Alloc = Allocator<_T>,
         Uint bufsize = 512 * sizeof(_T)>
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
