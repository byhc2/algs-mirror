#ifndef __ALGSTL_LIST_H__
#define __ALGSTL_LIST_H__

//双向链表

#include "algstl_memory.h"

namespace algstl
{

template<typename _Tp>
class ListNode
{
public:
    ListNode<_Tp>(const _Tp &&val): data_(val) {}
    ListNode<_Tp>(const _Tp &val): data_(val) {}

    ListNode<_Tp> *next_;
    ListNode<_Tp> *prev_;
    _Tp data_;
};

template<typename _Tp>
class ListIterator
{
public:
    typedef ListNode<_Tp> NodeType;
    ListIterator(NodeType *&p): p_(p) {}
    ListIterator &operator++() //前置自增，返回左值
    {
        p_ = p_->next_;
        return *this;
    }

    ListIterator operator++(int) //后置自增，返回右值
    {
        NodeType *tmp = p_;
        p_ = p_->next;

        return tmp;
    }

    _Tp &operator*()
    {
        return p_->data_;
    }

    NodeType *p_;
};

template<typename _Tp>
bool operator!=(const ListIterator<_Tp> &lhs, const ListIterator<_Tp> &rhs)
{
    return lhs.p_ != rhs.p_;
}

template<typename _Tp, typename _Alloc=Allocator<_Tp>>
class List
{
public:
    typedef _Tp ValueType;
    typedef _Alloc Allocator;
    typedef ListNode<ValueType> NodeType;
    typedef typename Allocator::template Rebind<NodeType>::Other NodeAllocator;
    typedef ListIterator<ValueType> Iterator;

    List()
    {
        head_ = alloc_.allocate(1);
        head_->next_ = head_;
        head_->prev_ = head_;
    }

    ~List()
    {
        auto cur = head_->next_;
        while (cur != head_)
        {
            //摘出当前节点
            NodeType *tmp = cur;
            cur = cur->next_;

            alloc_.deconstruct(tmp);
            alloc_.deallocate(tmp);
        }

        alloc_.deconstruct(head_);
        alloc_.deallocate(head_);
    }

    Iterator begin()
    {
        return head_->next_;
    }

    Iterator end()
    {
        return head_;
    }

    void pushBack(const ValueType &val)
    {
        NodeType *p = alloc_.allocate(1);
        alloc_.construct(p, val);
        NodeType *prev = head_->prev_;

        p->prev_ = prev;
        p->next_ = head_;
        head_->prev_ = p;
        prev->next_ = p;
    }
private:
    NodeType *head_; //指向头节点的指针
    NodeAllocator alloc_;
};

}

#endif
