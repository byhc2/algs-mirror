#ifndef __ALGSTL_STACK__
#define __ALGSTL_STACK__

#include "algsstring.h"
#include "algstl_deque.h"
#include "algstl_exception.h"

namespace algstl
{
template<typename _T, typename _Container = algstl::Deque<_T>>
class Stack
{
    public:
    typedef _T ValueType;
    typedef typename _Container::SizeType SizeType;
    typedef typename _Container::ConstIterator ConstIterator;

    class StackEmptyError : public AlgstlException
    {
        public:
        StackEmptyError(const algs::String &e) : e_(e)
        {}

        ~StackEmptyError()
        {}

        const Char *what()
        {
            return e_.cStr();
        }

        private:
        algs::String e_;
    };

    ConstIterator cbegin() const
    {
        return deque_.cbegin();
    }

    ConstIterator cend() const
    {
        return deque_.cend();
    }

    Stack()
    {}

    Stack(const Stack &rhs) : deque_(rhs.deque_)
    {}

    Void push(const ValueType &v)
    {
        deque_.pushBack(v);
    }

    const ValueType &top()
    {
        return deque_.back();
    }

    ValueType pop()
    {
        if (empty())
        {
            throw StackEmptyError("stack is empty");
        }
        auto r = deque_.back();
        deque_.popBack();
        return r;
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
