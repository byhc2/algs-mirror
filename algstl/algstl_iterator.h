#ifndef __ALGSTL_ITERATOR_H__
#define __ALGSTL_ITERATOR_H__

struct InputIteratorTag {};
struct ForwardIteratorTag: public InputIteratorTag {};
struct BidirectionalIteratorTag: public ForwardIteratorTag {};
struct RandomAccessIteratorTag: ForwardIteratorTag {};
struct OutputIteratorTag {}; //单独的，不参与继承

template<typename _T, typename _Distance>
struct InputIterator
{
    typedef InputIteratorTag IteratorTag;
    typedef _T               ValueType;
    typedef _Distance        DifferenceType;
    typedef _T*              Pointer;
    typedef _T&              Reference;
};

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
    typedef typename _Iterator::ValueType        ValueType;
    typedef typename _Iterator::DifferenceType   DifferenceType;
    typedef typename _Iterator::Pointer          Pointer;
    typedef typename _Iterator::Reference        Reference;
};

//偏特化给特定指针用
//指针一定是可以随机访问的迭代器
template<typename _Tp>
struct IteratorTraits<_Tp*>
{
    typedef RandomAccessIteratorTag IteratorCategory;
    typedef _Tp                     ValueType;
    typedef ptrdiff_t               DifferenceType;
    typedef _Tp*                    Pointer;
    typedef _Tp&                    Reference;
};

template<typename _Tp>
struct IteratorTraits<const _Tp*>
{
    typedef RandomAccessIteratorTag IteratorCategory;
    typedef _Tp                     ValueType;
    typedef ptrdiff_t               DifferenceType;
    typedef const _Tp*              Pointer;
    typedef const _Tp&              Reference;
};

template<typename _Iterator>
class ReverseIterator
{
public:
    typedef _Iterator IteratorType;
    typedef IteratorTraits<IteratorType>::ValueType ValueType; //必须使用IteratorTraits
    typedef IteratorTraits<IteratorType>::IteratorCategory IteratorCategory;
    typedef IteratorTraits<IteratorType>::DifferenceType DifferenceType;
    typedef IteratorTraits<IteratorType>::Pointer Pointer;
    typedef IteratorTraits<IteratorType>::Reference Reference;

    ReverseIterator() {}
    explicit ReverseIterator(IteratorType it): current_(it) {}

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

private:
    IteratorType current_;
};

#endif
