#ifndef __ALGSTL_ITERATOR__
#define __ALGSTL_ITERATOR__

#include "algs_type.h"

namespace algstl
{
// IteratorTag的作用
//当某个算法需要使用某种类型的Iterator时，需要检测迭代器的类型
//比如某些算法需要随机访问的迭代器，某些则只需要前向迭代器
//因此需要这个IteratorTag来表明迭代器的种类
struct InputIteratorTag
{};
struct ForwardIteratorTag : public InputIteratorTag
{};
struct BidirectionalIteratorTag : public ForwardIteratorTag
{};
struct RandomAccessIteratorTag : public ForwardIteratorTag
{};
struct OutputIteratorTag
{};  //单独的，不参与继承

#if 0

//C++标准定义了两种迭代器基础类，第一种是下面这种InputIterator或者其他什么xxxIterator
//某个容器的迭代器继承某一种xxxIterator类型，然后扩展自己的++、--等方法
//第二种就是下下面的struct Iterator基类，所有迭代器继承这个类，再扩展自己的方法
//
//然而，上面这两种，都没卵用，坑货C++标准委员会
//迭代器，本质上，是容器实现一个内部类，实现++、--、解引用等方法即可
//并不一定要继承而来
//继承的唯一好处是，代码看起来统一，并不会带来什么性能优势或者编码方便
//以 ListIterator继承Iterator为例：
//template<typename _T>
//class ListIterator: Iterator<xxxTag, _T> {
//public:
//  using Base = Iterator<xxxTag, _T>;
//  using typename Base::ValueType;
//  //必须写上这么一大堆using声明，把ValueType等从父类中提出来
//  //这么做，编码并没有变得很方便
//  using typename Base::Pointer;
//  using typename Base::Reference;
//}
//所以，其实，实现迭代器的时候，完全不需要继承！
//最后，妈的C++委员会也不建议用继承：http://cplusplus.github.io/LWG/lwg-defects.html#2438

template<typename _T, typename _Distance>
struct InputIterator
{
    typedef InputIteratorTag IteratorTag;
    typedef _T               ValueType;
    typedef _Distance        DifferenceType;
    typedef _T*              Pointer;
    typedef _T&              Reference;
};

template<typename _Category, typename _T, typename _Distance=PtrDiff,
         typename _Pointer=_T*, typename _Reference=_T&>
struct Iterator
{
    typedef _Category  IteratorCategory;
    typedef _T         ValueType;
    typedef _Distance  DifferenceType;
    typedef _Pointer   Pointer;
    typedef _Reference Reference;
};
#endif

//使用IteratorTraits的原因：
//理论上，我们需要使用Iterator::ValueType等
//来获取迭代器所包含的类型等
//但是由于普通指针也是迭代器而没有ValueType
//因此需要引入一个中间层IteratorTraits
//对于普通迭代器，IteratorTraits::ValueType就是Iterator::ValueType
//对于指针，特化出一个版本，IteratorTraits::ValueType就是指针所指向的类型
template<typename _Iterator>
struct IteratorTraits
{
    typedef typename _Iterator::IteratorCategory IteratorCategory;
    typedef typename _Iterator::ValueType ValueType;
    typedef typename _Iterator::DifferenceType DifferenceType;
    typedef typename _Iterator::Pointer Pointer;
    typedef typename _Iterator::Reference Reference;
};

//偏特化给特定指针用
//指针一定是可以随机访问的迭代器
template<typename _Tp>
struct IteratorTraits<_Tp *>
{
    typedef RandomAccessIteratorTag IteratorCategory;
    typedef _Tp ValueType;
    typedef ptrdiff_t DifferenceType;
    typedef _Tp *Pointer;
    typedef _Tp &Reference;
};

template<typename _Tp>
struct IteratorTraits<const _Tp *>
{
    typedef RandomAccessIteratorTag IteratorCategory;
    typedef _Tp ValueType;
    typedef ptrdiff_t DifferenceType;
    typedef const _Tp *Pointer;
    typedef const _Tp &Reference;
};

template<typename _Iterator>
class ReverseIterator
{
    template<typename _T>
    friend bool operator!=(const ReverseIterator<_T> &lhs,
                           const ReverseIterator<_T> &rhs);

    public:
    typedef _Iterator IteratorType;
    typedef typename IteratorTraits<IteratorType>::ValueType
        ValueType;  //必须用IteratorTraits
    typedef typename IteratorTraits<IteratorType>::IteratorCategory
        IteratorCategory;
    typedef
        typename IteratorTraits<IteratorType>::DifferenceType DifferenceType;
    typedef typename IteratorTraits<IteratorType>::Pointer Pointer;
    typedef typename IteratorTraits<IteratorType>::Reference Reference;

    ReverseIterator()
    {}
    explicit ReverseIterator(IteratorType it) : current_(it)
    {}

    ReverseIterator &operator++()
    {
        --current_;
        return *this;
    }

    ReverseIterator &operator++(int)
    {
        auto tmp = *this;
        --current_;
        return tmp;
    }

    ReverseIterator &operator--()
    {
        ++current_;
        return *this;
    }

    ReverseIterator &operator--(int)
    {
        auto tmp = *this;
        ++current_;
        return tmp;
    }

    Reference operator*()
    {
        IteratorType tmp = current_;
        return *--tmp;
    }

    private:
    IteratorType current_;
};

template<typename _T>
bool operator!=(const ReverseIterator<_T> &lhs, const ReverseIterator<_T> &rhs)
{
    return lhs.current_ != rhs.current_;
}
}

#endif
