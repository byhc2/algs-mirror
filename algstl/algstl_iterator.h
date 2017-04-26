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
template<typename _Tp*>
struct IteratorTraits
{
    typedef typename 
};

template<typename _Iterator>
class ReverseIterator
{
public:
    typedef _Iterator IteratorType;
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
