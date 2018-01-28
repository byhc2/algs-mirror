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

// TODO FIXME
// insert实现暂时不允许自我插入

namespace algstl
{
const Int bufcnt = 512;
//或为我实现之最复杂迭代器
template<typename _T, Uint bufsize = bufcnt>
struct DequeIterator
{
    typedef _T ValueType;
    typedef _T *Pointer;
    typedef _T &Reference;
    typedef PtrDiff DifferenceType;
    typedef RandomAccessIteratorTag IteratorCategory;

    DequeIterator() : start_(0), end_(0), cur_(0), arr_(0)
    {}

    DequeIterator(const DequeIterator &rhs)
        : start_(rhs.start_), end_(rhs.end_), cur_(rhs.cur_), arr_(rhs.arr_)
    {}

    Reference operator*()
    {
        return *cur_;
    }

    DifferenceType operator-(const DequeIterator &rhs) const
    {
        return DifferenceType(bufsize * (arr_ - rhs.arr_ - 1) + (cur_ - start_)
                              + (rhs.end_ - rhs.cur_));
    }

    //以下二函数俱不检查边界
    void _gotoNext()
    {
        ++arr_;
        start_ = *arr_;
        end_   = start_ + bufsize;
        cur_   = start_;
    }

    void _gotoPrev()
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
            _gotoNext();
            return *this;
        }
    }

    DequeIterator operator++(int)
    {
        auto r = *this;
        ++*this;
        return r;
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
            _gotoPrev();
            return *this;
        }
    }

    DequeIterator operator--(int)
    {
        auto r = *this;
        --*this;
        return r;
    }

    Bool operator==(const DequeIterator &rhs) const
    {
        return cur_ == rhs.cur_;
    }

    Bool operator!=(const DequeIterator &rhs) const
    {
        return cur_ != rhs.cur_;
    }

    Void _resetArr(Pointer *n)
    {
        arr_   = n;
        start_ = *arr_;
        end_   = start_ + bufsize;
    }

    DequeIterator operator+(DifferenceType n)
    {
        auto r = *this;
        return r += n;
    }

    DequeIterator operator-(DifferenceType n)
    {
        auto r = *this;
        return r -= n;
    }

    DequeIterator &operator+=(DifferenceType n)
    {
        //相对于当前缓冲区首的偏移
        auto offset = n + (cur_ - start_);
        if (offset >= 0 && offset < bufsize)
        {
            //当前缓冲区内
            cur_ = *arr_ + offset;
        }
        else
        {
            resetArr(
                arr_
                + (offset > 0 ? (offset / bufsize) : -(-offset / bufsize + 1)));
            cur_ = *arr_
                   + (offset > 0 ? offset % bufsize
                                 : bufsize - (-offset % bufsize));
        }
        return *this;
    }

    DequeIterator &operator-=(DifferenceType n)
    {
        return *this += -n;
    }

    algs::String toString() const
    {
        std::stringstream ss;
        ss << "arr:" << arr_ << "|start:" << start_ << "|end:" << end_
           << "|cur:" << cur_ - start_;
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
    typedef DequeIterator<ValueType> Iterator;
    typedef DequeIterator<const ValueType> ConstIterator;
    typedef typename algstl::ReverseIterator<Iterator> ReverseIterator;
    typedef Uint SizeType;
    typedef typename Iterator::DifferenceType DifferenceType;

    Deque() : arr_(0), arr_total_(0), first_(), last_()
    {
        _initArr();
    }

    Deque(const Deque &rhs) : Deque()
    {
        insert(rhs.begin(), rhs.end(), end());
    }

    template<typename _InputIterator>
    Deque(_InputIterator first, _InputIterator last) : Deque()
    {
        while (first != last)
        {
            this->insert(*first++, end());
        }
    }

    Reference front()
    {
        return *begin();
    }

    Reference back()
    {
        auto tmp = end();
        --tmp;
        return *tmp;
    }

    Deque &operator=(const Deque &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        if (size() > rhs.size())
        {
            erase(copy(rhs.begin(), rhs.end(), begin()), end());
        }
        else
        {
            resize(rhs.size());
            copy(rhs.begin(), rhs.end());
        }

        return *this;
    }

    SizeType size() const
    {
        return last_ - first_;
    }

    SizeType maxSize() const
    {
        return SizeType(-1);
    }

    Bool empty() const
    {
        return !size();
    }

    Void _deallocateArr(Pointer *first, Pointer *last)
    {
        while (first != last)
        {
            alloc_.deallocate(*first++, bufsize);
        }
    }

    Iterator erase(Iterator first, Iterator last)
    {
        auto elems_before = first - this->begin();
        auto elems_after  = last - this->end();
        if (elems_before < elems_after)
        {
            auto new_first = algstl::moveBackward(begin(), first, last);
            algstl::destroy(begin(), new_first);
            _deallocateArr(first_.arr_, new_first.arr_);
            algstl::destroy(first_.arr_, new_first.arr_);
            first_ = new_first;
            return last;
        }
        else
        {
            auto new_last = algstl::move(last, end(), first);
            algstl::destroy(new_last, end());
            _deallocateArr(new_last.arr_ + 1, last_.arr_ + 1);
            algstl::destroy(new_last.arr_ + 1, last_.arr_ + 1);
            last_ = new_last;
            return first;
        }
    }

    Iterator erase(Iterator p)
    {
        DifferenceType idx = p - first_;
        if (idx < (this->size() >> 1))
        {
            algstl::copy(p + 1, last_, p);
            popFront();
        }
        else
        {
            algstl::copy(first_, p, p);
            popBack();
        }
        return p;
    }

    void popBack()
    {
        if (last_.cur_ != first_.start_)
        {
            destroy(first_.cur_);
            ++first_.cur_;
            return;
        }
        destroy(first_.cur_);
        first_.gotoNext();
        first_.cur_ = first_.start_;
        return;
    }

    void popFront()
    {
        if (first_.cur_ + 1 != first_.end_)
        {
            destroy(first_.cur_);
            ++first_.cur_;
            return;
        }
        destroy(first_.cur_);
        first_.gotoNext();
        first_.cur_ = first_.start_;
        return;
    }

    void _initArr(Uint n = 1)
    {
        n          = this->_round(n);
        arr_       = arr_alloc_.allocate(8);
        arr_total_ = 8;

        arr_[3] = alloc_.allocate(bufsize);

        first_.arr_   = &arr_[3];
        first_.start_ = arr_[3];
        first_.end_   = first_.start_ + bufsize;
        first_.cur_   = first_.start_;

        last_.arr_   = &arr_[3];
        last_.start_ = arr_[3];
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
        if (first_.arr_ == arr_)
        {
            _extendArr();
        }
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
        if (last_.arr_ == arr_ + arr_total_ - 1)
        {
            //扩展二级索引
            _extendArr(1);
        }
        *(last_.arr_ + 1) = alloc_.allocate(bufsize);
        last_.resetArr(last_.arr_ + 1);
        last_.cur_ = last_.start_;
        alloc_.construct(last_.cur_, t);
        ++last_.cur_;
        return;
    }

    ConstIterator cbegin() const
    {
        return first_;
    }

    ConstIterator cend() const
    {
        return last_;
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

#if 0
    void resize(SizeType n)
    {
        if (n <= this->size())
        {
            this->erase(first_ + n, last_);
            last_ -= n;
        }
        else
        {
            auto _reserve(n - size());
        }
    }
#endif

    //将[first, last)置于pos前
    template<typename _InputIterator>
    Iterator insert(_InputIterator first, _InputIterator last, Iterator pos)
    {
        auto num = algstl::distance(first, last);
        assert(num >= 0);
        if (pos - first_ < last_ - pos)  //向前调整
        {
            auto new_first = _reserve(num);
            auto dest = move(begin(), pos, first_ - num);
            uninitializedCopy(first, last, dest);
            first_ = new_first;
            return first_ + num;
        }
        else  //向后调整
        {
            auto new_last = _reserve(num, 1);
            move(pos, last_, pos + num);
            uninitializedCopy(first, last, pos);
            last_ = new_last;
            return pos;
        }
    }

    // whence: 0首，1尾
    Iterator _reserve(SizeType n, Int whence = 0)
    {
        if (!whence)  //首
        {
            DifferenceType remain = n - (first_.cur_ - first_.start_);
            if (remain <= 0)
            {
                return first_ - n;
            }
            auto arr_incr = n / bufsize + 1;
            if (first_.arr_ - arr_ < arr_incr)
            {
                _extendArr(0, arr_incr);
            }
            while (arr_incr)
            {
                *(first_.arr_ - arr_incr) = alloc_.allocate(bufsize);
                --arr_incr;
            }
            return first_ - n;
        }
        else
        {
            DifferenceType remain = n - (last_.end_ - last_.cur_);
            if (remain <= 0)
            {
                return last_ + n;
            }
            auto arr_incr = remain / bufsize + 1;
            if (arr_total_ - (arr_ - last_.arr_) < arr_incr)
            {
                _extendArr(1, arr_incr);
            }
            while (arr_incr)
            {
                *(last_.arr_ + arr_incr) = alloc_.allocate(bufsize);
                --arr_incr;
            }
            return last_ + n;
        }
    }

    // whence: 0首，1尾
    // incr: 增量
    // 扩二级索引表
    Void _extendArr(Int whence = 0, Uint incr = 1)
    {
        auto arr_size = last_.arr_ - first_.arr_ + 1;  //已用二级索引大小
        if (arr_total_ > arr_size * 2 + incr)
        {
            //仅移动
            auto new_first = arr_ + (arr_total_ - arr_size - incr) / 2
                             + (whence ? incr : 0);
            if (new_first < arr_)
            {
                algstl::move(first_.arr_, last_.arr_, new_first);
            }
            else
            {
                algstl::moveBackward(first_.arr_, last_.arr_ + 1,
                                     new_first + arr_size);
            }
            first_.resetArr(new_first);
            last_.resetArr(new_first + arr_size);
        }
        else
        {
            //要分配新内存
            auto new_arr_total = this->_round(arr_total_ * 2 + incr);
            auto new_arr       = arr_alloc_.allocate(new_arr_total);
            auto new_first     = new_arr + (new_arr_total - arr_size - incr) / 2
                             + (whence ? incr : 0);
            algstl::uninitializedCopy(first_.arr_, last_.arr_ + 1, new_first);
            destroy(first_.arr_, last_.arr_);
            arr_alloc_.deallocate(arr_);
            arr_       = new_arr;
            arr_total_ = new_arr_total;
            first_.resetArr(new_first);
            last_.resetArr(new_first + arr_size - 1);
        }
    }

    SizeType _round(SizeType n)
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
