#ifndef __ALGSTL_DEQUE__
#define __ALGSTL_DEQUE__

#include <iostream>
#include <sstream>
#include "algsstring.h"
#include "algstl_iterator.h"
#include "algstl_memory.h"

//双向队列
//此处暂与sgi之deque一致
//虽然，缓冲区可变长
//缓冲区各记其首尾，辅以B树索引之
//遇随机访问，则以序号大小，于B树寻至相应缓冲区
//再寻址于缓冲区内

namespace algstl
{
const Int bufcnt = 512;
//或为我实现之最复杂迭代器
template<typename _T, typename _Alloc, Uint bufsize = bufcnt>
struct DequeIterator
{
    typedef _T ValueType;
    typedef _T *Pointer;
    typedef _T &Reference;
    typedef _Alloc Allocator;
    typedef PtrDiff DifferenceType;
    typedef RandomAccessIteratorTag IteratorCategory;

    DequeIterator() : start_(0), end_(0), cur_(0), arr_(0)
    {}

    ValueType operator*()
    {
        return *cur_;
    }

    //以下二函数俱不检查边界
    void gotoNext()
    {
        ++arr_;
        start_ = *arr_;
        end_   = start_ + bufsize;
        cur_   = start_;
    }

    void gotoPrev()
    {
        --arr_;
        start_ = *arr_;
        end_   = start_ + bufsize;
        cur_   = end_ - 1;
    }

    DequeIterator &operator++()  //前置加
    {
        if (cur_ + 1 != end_)
        {
            ++cur_;
            return *this;
        }
        else
        {
            gotoNext();
            return *this;
        }
    }

    DequeIterator &operator--()
    {
        if (cur_ != start_)
        {
            --cur_;
            return *this;
        }
        else
        {
            gotoPrev();
            return *this;
        }
    }

    Bool operator==(const DequeIterator &rhs) const
    {
        return cur_ == rhs.cur_;
    }

    Bool operator!=(const DequeIterator &rhs) const
    {
        return cur_ != rhs.cur_;
    }

    Void resetArr(Pointer *n)
    {
        arr_   = n;
        start_ = *arr_;
        end_   = start_ + bufsize;
    }

    DequeIterator &operator+=(DifferenceType n)
    {
        //相对于当前缓冲区首的偏移
        auto offset = n + (cur_ - start_);
        if (offset > 0 && offset < bufsize)
        {
            //当前缓冲区内
            cur_ = offset;
        }
        else
        {
            auto nf = offset > 0 ? offset / bufsize : -offset / bufsize - 1;
            resetArr(arr_ + offset / bufsize);
            cur_
                = offset > 0 ? offset % bufsize : bufsize - (-offset % bufsize);
        }
        return *this;
    }

    DequeIterator &operator-=(DifferenceType n)
    {
        return *this += -n;
    }

    algs::String toString()
    {
        std::stringstream ss;
        ss << "arr:" << arr_ << "|start:" << start_ << "|end:" << end_
           << "|cur:" << cur_;
        return ss.str().c_str();
    }

    Pointer start_;
    Pointer end_;
    Pointer cur_;
    Pointer *arr_;
};

template<typename _T, typename _Alloc = Allocator<_T>, Uint bufsize = bufcnt>
class Deque
{
    public:
    typedef _T ValueType;
    typedef _T *Pointer;
    typedef _T &Reference;
    typedef _Alloc Allocator;
    typedef typename Allocator::template Rebind<Pointer>::Other ArrAllocator;
    typedef DequeIterator<ValueType, Allocator> Iterator;
    typedef typename algstl::ReverseIterator<Iterator> ReverseIterator;

    Deque() : arr_(0), arr_total_(0), first_(), last_()
    {
        initArr();
    }

    void initArr(Uint n = 1)
    {
        n          = this->round(n);
        arr_       = arr_alloc_.allocate(8);
        arr_total_ = 8;

        arr_[4] = alloc_.allocate(bufsize);

        first_.arr_   = &arr_[4];
        first_.start_ = arr_[4];
        first_.end_   = first_.start_ + bufsize;
        first_.cur_   = first_.start_;

        last_.arr_   = &arr_[4];
        last_.start_ = arr_[4];
        last_.end_   = last_.start_ + bufsize;
        last_.cur_   = last_.start_;
    }

    Void pushFront(const ValueType &t)
    {
        if (first_.cur_ != first_.start_)
        {
            alloc_.construct(first_.cur_ - 1, t);
            --first_.cur_;
            return;
        }
        extendMap(1);
        *(first_.arr_ - 1) = alloc_.allocate(bufsize);
        first_.resetArr(first_.arr_ - 1);
        first_.cur_ = first_.end_;
        alloc_.construct(first_.cur_ - 1, t);
        --first_.cur_;
    }

    Void pushBack(const ValueType &t)
    {
        if (last_.cur_ != last_.end_)
        {
            //最简情况，直接构造
            alloc_.construct(last_.cur_, t);
            ++last_.cur_;
            return;
        }
        //扩展二级索引
        extendMap(1);
        *(last_.arr_ + 1) = alloc_.allocate(bufsize);
        last_.resetArr(last_.arr_ + 1);
        last_.cur_ = last_.start_;
        alloc_.construct(last_.cur_, t);
        ++last_.cur_;
        return;
    }

    Iterator begin()
    {
        return first_;
    }

    Iterator end()
    {
        return last_;
    }

    ReverseIterator rbegin()
    {
        return ReverseIterator(end());
    }

    ReverseIterator rend()
    {
        return ReverseIterator(begin());
    }

    // whence: 0首，1尾
    // incr: 增量
    Void extendMap(Int whence = 0, Uint incr = 1)
    {
        std::cout << "in " << __FUNCTION__ << std::endl;
        auto old_arr_size = last_.arr_ - first_.arr_;  //已用二级索引大小
        if (arr_total_ > old_arr_size * 2 + incr)
        {
            //仅移动
            auto new_first = arr_ + (arr_total_ - old_arr_size - incr) / 2
                             + (whence ? incr : 0);
            move(first_.arr_, last_.arr_, new_first);
            first_.resetArr(new_first);
            last_.resetArr(new_first + old_arr_size);
        }
        else
        {
            //要分配新内存
            auto new_arr_total = this->round(arr_total_ * 2 + incr);
            auto new_arr       = arr_alloc_.allocate(new_arr_total);
            auto new_first = new_arr + (new_arr_total - old_arr_size - incr) / 2
                             + (whence ? incr : 0);
            move(first_.arr_, last_.arr_, new_first);
            arr_       = new_arr;
            arr_total_ = new_arr_total;
            first_.resetArr(new_first);
            last_.resetArr(new_first + old_arr_size);
        }
    }

    SizeType round(SizeType n)
    {
        return (n + 7) & (SizeType(-1) ^ 0x7);  //八倍圆整
    }

    private:
    Pointer *arr_;        //二级索引的指针
    SizeType arr_total_;  //二级索引大小，含空
    Iterator first_;
    Iterator last_;
    Allocator alloc_;
    ArrAllocator arr_alloc_;
};
};

#endif
