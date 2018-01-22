#ifndef __ALGSTL_LIST__
#define __ALGSTL_LIST__

//双向链表

#include <iostream>
#include <stdexcept>
#include "algstl_iterator.h"
#include "algstl_memory.h"

namespace algstl
{
template<typename _T>
class ListNode
{
    public:
    typedef _T ValueType;

    ListNode<ValueType>(const ValueType &&val)
    {
        swap(val);
    }

    ListNode<ValueType>(const ValueType &val) : data_(val)
    {}

    ListNode<ValueType> *next_;
    ListNode<ValueType> *prev_;
    ValueType data_;
};

template<typename _T>
class ListIterator
{
    public:
    typedef _T ValueType;
    typedef _T &Reference;
    typedef BidirectionalIteratorTag IteratorCategory;
    typedef _T *Pointer;
    typedef Void DifferenceType;  // List没有DifferenceType;
    typedef ListNode<ValueType> NodeType;

    ListIterator(NodeType *p) : p_(p)
    {}

    ListIterator(const ListIterator &rhs)
    {
        if (&rhs == this)
        {
            return;
        }
        p_ = rhs.p_;
    }

    ListIterator &operator=(const ListIterator &rhs)
    {
        if (&rhs == this)
        {
            return *this;
        }
        p_ = rhs.p_;
        return *this;
    }

    ListIterator &operator++()  //前置自增，返回左值
    {
        p_ = p_->next_;
        return *this;
    }

    ListIterator operator++(int)  //后置自增，返回右值
    {
        NodeType *tmp = p_;
        p_            = p_->next_;

        return tmp;
    }

    ListIterator &operator--()  //前置自减，返回左值
    {
        p_ = p_->prev_;
        return *this;
    }

    ListIterator operator--(int)  //后置自减，返回右值
    {
        NodeType *tmp = p_;
        p_            = p_->prev_;

        return tmp;
    }

    Reference operator*()
    {
        return p_->data_;
    }

    Pointer operator->()
    {
        return &(p_->data_);
    }

    NodeType *p_;
};

template<typename _T>
bool operator!=(const ListIterator<_T> &lhs, const ListIterator<_T> &rhs)
{
    return lhs.p_ != rhs.p_;
}

template<typename _T>
class ListConstIterator
{
    public:
    typedef _T ValueType;
    typedef const _T &ConstReference;
    typedef const _T &Reference;
    typedef BidirectionalIteratorTag IteratorCategory;
    typedef const _T *Pointer;
    typedef PtrDiff DifferenceType;
    typedef ListNode<ValueType> NodeType;

    ListConstIterator(const NodeType *p) : p_(p)
    {}

    typedef ListIterator<ValueType> Iterator;
    ListConstIterator(const Iterator &rhs) : p_(rhs.p_)
    {}

    ListConstIterator(const ListConstIterator &rhs)
    {
        if (&rhs == this)
        {
            return;
        }
        p_ = rhs.p_;
    }

    ListConstIterator &operator=(const ListConstIterator &rhs)
    {
        if (&rhs == this)
        {
            return *this;
        }
        p_ = rhs.p_;
        return *this;
    }

    ListConstIterator &operator++()  //前置自增，返回左值
    {
        p_ = p_->next_;
        return *this;
    }

    ListConstIterator operator++(int)  //后置自增，返回右值
    {
        NodeType *tmp = p_;
        p_            = p_->next;

        return tmp;
    }

    ListConstIterator &operator--()  //前置自减，返回左值
    {
        p_ = p_->prev_;
        return *this;
    }

    ListConstIterator operator--(int)  //后置自减，返回右值
    {
        NodeType *tmp = p_;
        p_            = p_->prev_;

        return tmp;
    }

    ConstReference operator*()
    {
        return p_->data_;
    }

    const NodeType *p_;
};

template<typename _T>
bool operator!=(const ListConstIterator<_T> &lhs,
                const ListConstIterator<_T> &rhs)
{
    return lhs.p_ != rhs.p_;
}

#if 0
template<typename _T>
bool operator!=(const ListConstIterator<_T> &lhs, const ListIterator<_T> &rhs)
{
    return lhs.p_ != rhs.p_;
}
#endif

template<typename _T, typename _Alloc = Allocator<_T>>
class List
{
    public:
    typedef _T ValueType;
    typedef _Alloc Allocator;
    typedef ListNode<ValueType> NodeType;
    typedef typename Allocator::template Rebind<NodeType>::Other NodeAllocator;
    typedef ListIterator<ValueType> Iterator;
    typedef ListConstIterator<ValueType> ConstIterator;
    typedef typename algstl::ReverseIterator<Iterator> ReverseIterator;
    typedef typename algstl::ReverseIterator<ConstIterator>
        ConstReverseIterator;
    typedef Uint SizeType;
    typedef typename Iterator::DifferenceType DifferenceType;

    List()
    {
        head_        = alloc_.allocate(1);
        head_->next_ = head_;
        head_->prev_ = head_;
    }

    void clear()
    {
        this->erase(this->begin(), this->end());
    }

    List(const List &rhs) : List()
    {
        insert(rhs.cbegin(), rhs.cend(), end());
    }

    List(ConstIterator first, ConstIterator last) : List()
    {
        while (first != last)
        {
            this->insert(*first, this->end());
            ++first;
        }
    }

    List &operator=(const List &rhs)
    {
        if (&rhs == this)
        {
            return *this;
        }
        auto first1 = begin();
        auto last1  = end();
        auto first2 = rhs.begin();
        auto last2  = rhs.end();

        while (first1 != last1 && first2 != last2)
        {
            *first1 = *first2;
            ++first1;
            ++first2;
        }

        if (first2 == last2)
        {
            erase(first1, last1);
        }
        else
        {
            insert(first2, last2, last1);
        }
        return *this;
    }

    Iterator erase(Iterator pos)
    {
        auto prev = pos;
        auto next = pos;
        --prev;
        ++next;
        _connect(prev, next);

        alloc_.deconstruct(pos.p_);
        alloc_.deallocate(pos.p_);
        return next;
    }

    void _connect(Iterator p, Iterator n)
    {
        auto p0   = p.p_;
        auto n0   = n.p_;
        p0->next_ = n0;
        n0->prev_ = p0;
    }

    Iterator erase(Iterator first, Iterator last)
    {
        auto prev = first;
        auto next = last;
        --prev;
        _connect(prev, next);
        while (first != last)
        {
            auto tmp = first;
            ++tmp;
            //此处或需allocator_traits等概念
            //获知NodeAllocator及Value Allocator
            //但因ListNode实现为内嵌ValueType
            //则销毁p_时其data_一并销毁
            // TODO 暂不考虑AllocatorTraits等
            //详见 http://en.cppreference.com/w/cpp
            //比较复杂
            alloc_.deconstruct(first.p_);
            alloc_.deallocate(first.p_);
            first = tmp;
        }
        return next;
    }

    //[first, last)从x中摘除，加入pos之前
    Void splice(List &x, Iterator first, Iterator last, Iterator pos)
    {
        if (&x == this)
        {
            //禁止自摘除
            throw std::runtime_error("splice on self");
        }

        auto prev = first;
        --prev;
        _connect(prev, last);
        while (first != last)
        {
            this->insert(*first++, pos);
        }
    }

    //返回插入[first, last)后插入元素首迭代器
    ConstIterator insert(ConstIterator first, ConstIterator last, Iterator pos)
    {
        auto tmp = List(first, last);
        this->splice(tmp, tmp.begin(), tmp.end(), pos);
        return first;
    }

    Iterator insert(const ValueType &v, Iterator pos)
    {
        NodeType *p = alloc_.allocate(1);
        alloc_.construct(p, v);

        auto pos0 = pos.p_;

        pos0->prev_->next_ = p;
        p->next_           = pos0;
        p->prev_           = pos0->prev_;
        pos0->prev_        = p;
        return p;
    }

    Iterator insert(Iterator it, Iterator pos)
    {
        NodeType *p       = it->p_;
        pos->prev_->next_ = p;
        p->next_          = pos;
        p->prev_          = pos->prev_;
        pos->prev_        = p;
        return p;
    }

    ~List()
    {
        auto cur = head_->next_;
        while (cur != head_)
        {
            //摘出当前节点
            NodeType *tmp = cur;
            cur           = cur->next_;

            alloc_.deconstruct(tmp);
            alloc_.deallocate(tmp, 1);
        }

        alloc_.deconstruct(head_);
        alloc_.deallocate(head_);
    }

    ConstIterator cbegin() const
    {
        return ConstIterator(head_->next_);
    }

    ConstIterator cend() const
    {
        return ConstIterator(head_);
    }

#if 0  //不需兼容此情况
    ConstIterator begin() const
    {
        return ConstIterator(head_->next_);
    }

    ConstIterator end() const
    {
        return ConstIterator(head_);
    }
#endif

    Iterator begin()
    {
        return Iterator(head_->next_);
    }

    Iterator end()
    {
        return Iterator(head_);
    }

    ReverseIterator rbegin()
    {
        return ReverseIterator(end());
    }

    ReverseIterator rend()
    {
        return ReverseIterator(begin());
    }

    ConstReverseIterator crbegin() const
    {
        return ConstReverseIterator(cend());
    }

    ConstReverseIterator crend() const
    {
        return ConstReverseIterator(cbegin());
    }

    void pushBack(const ValueType &val)
    {
        NodeType *p = alloc_.allocate(1);
        alloc_.construct(p, val);
        NodeType *prev = head_->prev_;

        p->prev_     = prev;
        p->next_     = head_;
        head_->prev_ = p;
        prev->next_  = p;
    }

    Bool empty() const
    {
        return head_->next_ == head_;
    }

    SizeType size() const
    {
        return SizeType(algstl::distance(cbegin(), cend()));
    }

    SizeType maxSize() const
    {
        return SizeType(-1);
    }

    typename Iterator::Reference front()
    {
        return *begin();
    }

    typename ConstIterator::ConstReference front() const
    {
        return *cbegin();
    }

    typename Iterator::Reference back()
    {
        auto tmp = end();
        --tmp;
        return *tmp;
    }

    typename ConstIterator::ConstReference back() const
    {
        auto tmp = cend();
        --tmp;
        return *tmp;
    }

    private:
    NodeType *head_;  //头节点指针
    NodeAllocator alloc_;
};
}

#endif
