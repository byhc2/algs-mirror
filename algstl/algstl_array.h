#ifndef __ALGSTL_ARRAY__
#define __ALGSTL_ARRAY__

//动态数组，基本同stl中vector

#include "algs_type.h"
#include "algstl_memory.h"
#include "algstl_iterator.h"

namespace algstl
{

template<typename _T, typename _Alloc=Allocator<_T>>
class Array
{
public:
    typedef _T ValueType;
    typedef _Alloc Allocator;
    typedef _T* Iterator;
    typedef typename algstl::ReverseIterator<Iterator> ReverseIterator;
    typedef Uint SizeType;

    Array()
    {
        start_ = nullptr;
        end_ = nullptr;
        cap_ = nullptr;
    }

    Iterator begin()
    {
        return start_;
    }

    Iterator end()
    {
        return end_;
    }

    ~Array()
    {
        //TODO
    }

    SizeType size() const
    {
        return end_ - start_;
    }

    Array<ValueType> &operator=(const Array<ValueType> &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        return *this;
    }

    Array<ValueType> &operator+(const ValueType &rhs)
    {
        if (end_ == cap_)
        {
            //需要重新分配内存
            SizeType newsize = size() * incr_fact;
            ValueType *tmp = alloc_.allocate(newsize);

            //拷贝数据
            uninitialized_copy(start_, end_, tmp);

            //释放旧的内存
            auto cur = start_;
            while (cur != end_)
            {
                //析构
                alloc_.deconstruct(cur);
            }
            cur = start_;
            alloc_.deallocate(start_, cap_ - start_);

            //指针指向新的地址
            start_ = tmp;
            end_ = start_ + size();
            cap_ = start_ + newsize;
        }

        alloc_.construct(end_++, rhs);
        return *this;
    }

private:
    ValueType *start_;
    ValueType *end_;
    ValueType *cap_;
    static constexpr Double incr_fact = 1.5;
    Allocator alloc_;
};

}

#endif
