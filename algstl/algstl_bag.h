#ifndef __ALGSTL_BAG__
#define __ALGSTL_BAG__

#include "algstl_deque.h"

namespace algstl
{
template<typename _T, typename _Container = algstl::Deque<_T>>
class Bag
{
    public:
    typedef _T ValueType;
    typedef _Container::SizeType SizeType;
    Bag()
    {}
    Void add(const ValueType &v)
    {
        deque_.pushBack(v);
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
