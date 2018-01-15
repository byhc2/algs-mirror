#ifndef __ALGSTL_MEMORY__
#define __ALGSTL_MEMORY__

#include <cstddef>
#include <cstdlib>
#include <exception>
#include <new>
#include <stdexcept>
#include "algs_type.h"
#include "algstl_iterator.h"

//负责内存分配、构造、析构等事宜

namespace algstl
{
#if 0
template<typename _Tp>
inline void destroy(_Tp *p)
{
    p->~_Tp();
}
#endif

template<typename _T>
inline void destroy(_T &v)
{
    v.~_T();
}

//析构一个序列的内容
template<typename _ForwardIterator>
void destroy(_ForwardIterator first, _ForwardIterator last)
{
    while (first != last)
    {
        destroy(*first);
        ++first;
    }
}

template<typename _Tp>
class Allocator
{
    public:
    typedef Uint SizeType;
    typedef ptrdiff_t DifferenceType;
    typedef _Tp *Pointer;
    typedef const _Tp *ConstPointer;
    typedef _Tp &Reference;
    typedef const _Tp &ConstReference;
    typedef _Tp ValueType;

    //这里需要单独声明一个struct
    //使容器层在使用这个allocator的时候
    //可以通过rebind来声明与容器相关的一种allocator
    //比如list容器，数据本身是存放在list_node中的
    //所以在知道了数据本身的allocator之后
    //可以通过rebind来得到list_node的allocator
    template<typename _Tp1>
    struct Rebind
    {
        typedef Allocator<_Tp1> Other;
    };

    Allocator() = default;
    Allocator(const Allocator &)
    {}
    template<typename _Tp1>
    Allocator(const Allocator<_Tp1> &)
    {}
    ~Allocator()
    {}

    Pointer address(Reference x) const
    {
        return &x;
    }

    ConstPointer address(ConstReference x) const
    {
        return &x;
    }

    Pointer allocate(SizeType n)
    {
        if (n == 0)
        {
            return 0;
        }

        void *p = malloc(n * sizeof(ValueType));
        if (p)
        {
            return static_cast<Pointer>(p);
        }
        throw std::bad_alloc();
    }

    void deallocate(Pointer p, SizeType n = 1)
    {
        //因为分配的时候调用的是malloc
        //操作系统已经记录了n的信息
        //所以这里不用再使用n
        free(p);
    }

    void construct(Pointer p, const ValueType &val)
    {
        new (p) ValueType(val);
    }

    void deconstruct(Pointer p)
    {
        p->~ValueType();
    }
};

//移动语义，旧数据会析构
template<typename _InputIterator, typename _ForwardIterator>
void move(_InputIterator first, _InputIterator last, _ForwardIterator dest)
{
    while (first != last)
    {
        new (&*dest)
            typename IteratorTraits<_ForwardIterator>::ValueType(*first);
        destroy(*first);
        ++dest;
        ++first;
    }
}

template<typename _InputIterator, typename _ForwardIterator>
void uninitializedCopy(_InputIterator first, _InputIterator last,
                       _ForwardIterator dest)
{
    try
    {
        while (first != last)
        {
            new (&*dest)
                typename IteratorTraits<_ForwardIterator>::ValueType(*first);
            ++dest;
            ++first;
        }
    }
    catch (std::exception &e)
    {
        throw std::runtime_error(e.what());
    }
}

template<typename _InputIterator, typename _SizeType, typename _ForwardIterator>
void uninitializedCopyN(_InputIterator first, _InputIterator last,
                        _ForwardIterator dest, _SizeType n)
{
    _SizeType c = 0;
    try
    {
        while (first != last && c < n)
        {
            new (&*dest)
                typename IteratorTraits<_ForwardIterator>::ValueType(*first);
            ++dest;
            ++first;
            ++c;
        }
    }
    catch (std::exception &e)
    {
        throw std::runtime_error(e.what());
    }
}
}

#endif
