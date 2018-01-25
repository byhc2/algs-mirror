#ifndef __ALGSTL_MEMORY__
#define __ALGSTL_MEMORY__

#include <cstddef>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <new>
#include <stdexcept>
#include "algs_type.h"
#include "algstl_iterator.h"

//负责内存分配、构造、析构等事宜

namespace algstl
{
template<typename _Tp>
inline void destroy(_Tp *p)
{
    p->~_Tp();
}

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

    //此处单声明一struct
    //容器层用allocator时
    //可用rebind声明与容器相关的allocator
    //如List，数据实存放于ListNode中
    // List知道数据本身allocator后
    //可通过rebind得到ListNode之allocator
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
        //因分配时调用malloc
        //操作系统已记录所分配大小信息
        //故此处不用n
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

//移动，析构旧数据
template<typename _InputIterator, typename _ForwardIterator>
_ForwardIterator move(_InputIterator first, _InputIterator last,
                      _ForwardIterator dest)
{
    while (first != last)
    {
        *dest++ = *first;
        destroy(*first++);
    }
    return dest;
}

//从尾部移动
template<typename _InputIterator, typename _ForwardIterator>
_ForwardIterator moveBackward(_InputIterator first, _InputIterator last,
                              _ForwardIterator dest)
{
    if (last != dest)
    {
        while (first != last)
        {
            *--dest = *--last;
            destroy(*last);
        }
    }
    else
    {
        while (first != last)
        {
            --dest;
            --last;
        }
    }
    return dest;
}

//普通复制
template<typename _InputIterator, typename _ForwardIterator>
_ForwardIterator copy(_InputIterator first, _InputIterator last,
                      _ForwardIterator dest)
{
    while (first != last)
    {
        *dest = *first;
        ++dest;
        ++first;
    }
    return dest;
}

//将对象复制到原始内存中
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
