#ifndef __ALGSTL_DEQUE__
#define __ALGSTL_DEQUE__

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
template<typename _T, typename _Alloc, Uint bufsize = 512 * sizeof(_T)>
struct DequeIterator
{
    typedef _T ValueType;
    typedef _T *Pointer;
    typedef _T &Reference;
    typedef _Alloc Allocator;
    typedef PtrDiff DiffType;
    DequeIterator() : start_(0), end_(0), cur_(0)
    {}

    //以下二函数俱不检查边界
    void gotoNext()
    {
        ++map_;
        start_ = *map_;
        end_   = start_ + bufcnt;
        cur_   = start_;
    }

    void gotoPrev()
    {
        --map_;
        start_ = *map_;
        end_   = start_ + bufcnt;
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

    Bool operator==(const DequeIterator &rhs)
    {
        return cur_ == rhs.cur_;
    }

    Bool operator!=(const DequeIterator &rhs)
    {
        return cur_ != rhs.cur_;
    }

    Void resetMap(Pointer *n)
    {
        map_   = n;
        start_ = *map_;
        end_   = start_ + bufcnt;
        cur_=0;
    }

    DequeIterator &operator+=(DiffType n)
    {
        //相对于当前缓冲区首的偏移
        auto offset = n + (cur_ - start_);
        if (offset > 0 && offset < bufcnt)
        {
            //当前缓冲区内
            cur_ = offset;
        }
        else
        {
            auto nf = offset > 0 ? offset / bufcnt : -offset / bufcnt - 1;
            resetMap(map_ + offset / bufcnt);
            cur_ = offset > 0 ? offset % bufcnt : bufcnt - (-offset % bufcnt);
        }
        return *this;
    }

    DequeIterator &operator-=(DiffType n)
    {
        return *this += -n;
    }

    algs::String toString()
    {
        std::stringstream ss;
        ss << "map:" << map_ << "|start:" << start_ << "|end:" << end_
           << "|cur:" << cur_;
        return ss.str().c_str();
    }

    Pointer start_;
    Pointer end_;
    Pointer cur_;
    Pointer *map_;
};

template<typename _T, typename _Alloc = Allocator<_T>,
         Uint bufsize = 512 * sizeof(_T)>
class Deque
{
    public:
    typedef _T ValueType;
    typedef _T *Pointer;
    typedef _T &Reference;
    typedef _Alloc Allocator;
    typedef DequeIterator<ValueType, Allocator> Iterator;

    Deque() : map_(0), map_size_(0), first_(), last_()
    {}

    void pushBack(const ValueType &t)
    {
        if (last_.cur_ != last_.end_)
        {
            //最简单的情况，直接构造
            alloc_.construct(last_.cur_, t);
            ++last_.cur_;
            return;
        }
        //扩展二级索引
        extendMap();
        auto oldfirst = first_.cur_-first_.map_;
        first_.resetMap(map_);
        first_.cur_=oldfirst;
        last_.resetMap(map_ + map_size_);
    }

    private:
    Pointer *map_;       //二级索引的指针
    SizeType map_size_;  //二级索引的大小
    Iterator first_;
    Iterator last_;
    Allocator alloc_;
};
};

#endif
