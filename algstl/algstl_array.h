#ifndef __ALGSTL_ARRAY__
#define __ALGSTL_ARRAY__

//动态数组，基本同stl中vector

#include <iostream>
#include <cassert>
#include <initializer_list>
#include <algorithm>
#include "algs_type.h"
#include "algstl_memory.h"
#include "algstl_iterator.h"
#include "algstl_algobase.h"
#include "algsstring.h"
#include "__tostring.h"

namespace algstl
{

template<typename _T, typename _Alloc=Allocator<_T>>
class Array
{
public:
    typedef _T ValueType;
    typedef _T& Reference;
    typedef const _T& ConstReference;
    typedef _Alloc Allocator;
    typedef _T* Iterator;
    typedef const _T* ConstIterator;
    typedef _T* Pointer;
    typedef typename algstl::ReverseIterator<Iterator> ReverseIterator;
    typedef typename algstl::ReverseIterator<ConstIterator> ConstReverseIterator;
    typedef Uint SizeType;

    static constexpr SizeType npos = -1;

    Array()
    {
        start_ = nullptr;
        end_ = nullptr;
        cap_ = nullptr;
    }

    explicit Array(SizeType n): Array()
    {
        resize(n);
    }

    //初始化长度为n的数组，每个值都由v构造
    Array(const ValueType &v, SizeType n): Array()
    {
        resize(n);
        auto it = start_;
        while (it != end_)
        {
            alloc_.construct(it, v);
            ++it;
        }
    }

    //复制构造函数
    Array(const Array &rhs): Array()
    {
        auto s = rhs.size();
        start_ = alloc_.allocate(s);
        uninitialized_copy(rhs.begin(), rhs.end(), start_);
        end_ = start_ + s;
        cap_ = end_;
    }

    //因为编译器会固定把{xx, xx}这样的列表
    //解释为initializer_list
    //所以这里没办法只能使用
    Array(const std::initializer_list<ValueType> &lst): Array()
    {
        //预分配空间
        resize(lst.size());
        uninitialized_copy(lst.begin(), lst.end(), start_);
    }

    void resize(SizeType n)
    {
        if (start_ + n < end_)
        {
            //空间足够大，需要析构n到end_之间的元素
            _destroy(start_ + n, end_);
            end_ = start_ + n;
        }
        else if (start_ + n < cap_)
        {
            //空间足够大，不需要析构
            end_ = start_ + n;
        }
        else
        {
            decltype(start_) tmp = alloc_.allocate(n);
            assert(tmp);
            uninitialized_copy_n(start_, end_, tmp, n);
            //析构销毁之前的内存
            _destroy(start_, end_);
            alloc_.deallocate(start_, size());
            start_ = tmp;
            cap_ = start_ + n;
            end_ = cap_;
        }
    }

    algs::String toString() const
    {
        algs::String tmp = algs::toString(size()) + " [";
        SizeType width = tmp.size();
        for (auto it = begin(); it != end(); ++it)
        {
            auto ex = algs::toString(*it);
            tmp += ex;
            if (width > 80) //看看是否可以动态获取到屏幕宽度 TODO
            {
                tmp += "\n";
                width = 0;
            }
            else
            {
                tmp += "    ";
                width += ex.size() + sizeof("    ");
            }
        }

        tmp += "]";

        return tmp;
    }

    Reference operator[](SizeType i)
    {
        assert(i < size());
        return *(start_ + i);
    }

    ConstReference operator[](SizeType i) const
    {
        assert(i < size());
        return *(start_ + i);
    }

    //右值构造函数
    explicit Array(const Array &&rhs)
    {
        start_ = rhs.start_;
        end_ = rhs.end_;
        cap_ = rhs.cap_;
        rhs.start_ = nullptr;
        rhs.end_ = nullptr;
        rhs.cap_ = nullptr;
    }

    template<typename _Comp>
    Void sort(_Comp f);

    Iterator begin()
    {
        return start_;
    }

    Iterator end()
    {
        return end_;
    }

    ReverseIterator rbegin()
    {
        return ReverseIterator(end());
    }

    ReverseIterator rend()
    {
        return ReverseIterator(begin());
    }

    ConstReverseIterator rbegin() const
    {
        return ConstReverseIterator(end());
    }

    ConstReverseIterator rend() const
    {
        return ConstReverseIterator(begin());
    }

    ConstIterator begin() const
    {
        return start_;
    }

    ConstIterator end() const
    {
        return end_;
    }

    ~Array()
    {
        _destroy(start_, end_);
        alloc_.deallocate(start_, size());
        start_ = nullptr;
        end_ = nullptr;
        cap_ = nullptr;
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

        //先释放自己
        auto cur = start_;
        while (cur != end_)
        {
            alloc_.deconstruct(cur);
        }
        alloc_.deallocate(start_, size());

        //复制对方
        start_ = alloc_.allocate(rhs.size());
        uninitialized_copy(rhs.begin(), rhs.end(), start_);
        end_ = start_ + rhs.size();
        cap_ = end_;

        return *this;
    }

#if 0
    Array<ValueType> &operator+(const ValueType &rhs)
    {
        if (end_ == cap_)
        {
            SizeType oldsize = size();
            //需要重新分配内存
            SizeType newsize = (size() ? size() : 1) * incr_fact;
            ValueType *tmp = alloc_.allocate(newsize);

            //拷贝数据
            uninitialized_copy(start_, end_, tmp);

            //释放旧的内存
            auto cur = start_;
            while (cur != end_)
            {
                //析构
                alloc_.deconstruct(cur);
                ++cur;
            }
            cur = start_;
            alloc_.deallocate(start_, cap_ - start_);

            //指针指向新的地址
            start_ = tmp;
            end_ = start_ + oldsize;
            cap_ = start_ + newsize;
        }

        alloc_.construct(end_++, rhs);
        return *this;
    }
#endif

    Array<ValueType> &operator+=(const ValueType &rhs)
    {
        if (end_ == cap_)
        {
            SizeType oldsize = size();
            //需要重新分配内存
            SizeType newsize = (size() ? size() : 1) * incr_fact;
            ValueType *tmp = alloc_.allocate(newsize);

            //拷贝数据
            uninitialized_copy(start_, end_, tmp);

            //释放旧的内存
            auto cur = start_;
            while (cur != end_)
            {
                //析构
                alloc_.deconstruct(cur);
                ++cur;
            }
            cur = start_;
            alloc_.deallocate(start_, cap_ - start_);

            //指针指向新的地址
            start_ = tmp;
            end_ = start_ + oldsize;
            cap_ = start_ + newsize;
        }

        alloc_.construct(end_++, rhs);
        return *this;
    }

private:
    ValueType *start_;
    ValueType *end_;
    ValueType *cap_;
    static constexpr Double incr_fact = 2;
    Allocator alloc_;
};

template<typename _T, typename _Alloc>
inline Void swap(Array<_T, _Alloc> &lhs, Array<_T, _Alloc> &rhs)
{
    if (&lhs == &rhs)
    {
        return;
    }

    swap(lhs.start_, rhs.start_);
    swap(lhs.end_, rhs.end_);
    swap(lhs.cap_, rhs.cap_);
}

//先临时写这么一个sort方法
template<typename _T, typename _Alloc> template<typename _Comp>
Void Array<_T, _Alloc>::sort(_Comp f)
{
    if (size() == 0)
    {
        return;
    }

    //这里先使用标准库的快排
    std::sort(begin(), end(), f);
}

}

#endif
