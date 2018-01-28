#ifndef __ALGSTL_QUEUE__
#define __ALGSTL_QUEUE__

#include "algstl_deque.h"

namespace algstl
{
template<typename _T, typename _Container = algstl::Deque<_T>>
class Queue
{
    public:
    typedef _T ValueType;
    typedef _Container::SizeType SizeType;

    Bag()
    {}

    Void enqueue(const ValueType &v)
    {
        deque_.pushBack(v);
    }

    ValueType dequeue()
    {
        auto v = deque_.front();
        deque_.popFront();
        return v;
    }

    Bool empty() const
    {
        return deque_.empty();
    }

    SizeType size() const
    {
        return deque_.size();
    }

    private:
    _Container deque_;
};
}

#endif
