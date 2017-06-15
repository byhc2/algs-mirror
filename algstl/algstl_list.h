#ifndef __ALGSTL_LIST_H__
#define __ALGSTL_LIST_H__

//双向链表

#include "algstl_memory.h"
#include "algstl_iterator.h"

namespace algstl
{

template<typename _T>
class ListNode
{
public:
    typedef _T ValueType;

    ListNode<ValueType>(const ValueType &&val): data_(val) {}
    ListNode<ValueType>(const ValueType &val): data_(val) {}

    ListNode<ValueType> *next_;
    ListNode<ValueType> *prev_;
    ValueType data_;
};

//List类型，不具有DifferenceType，所以这里继承的三个参数为Void
template<typename _T>
class ListIterator: public Iterator<BidirectionalIteratorTag, _T, Void, _T*, _T&>
{
public:
    typedef _T  ValueType;
    typedef _T& Reference;
    typedef ListNode<ValueType> NodeType;

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

    Reference operator*()
    {
        return p_->data_;
    }

    NodeType *p_;
};

template<typename _T>
bool operator!=(const ListIterator<_T> &lhs, const ListIterator<_T> &rhs)
{
    return lhs.p_ != rhs.p_;
}

template<typename _T, typename _Alloc=Allocator<_T>>
class List
{
public:
    typedef _T ValueType;
    typedef _Alloc Allocator;
    typedef ListNode<ValueType> NodeType;
    typedef typename Allocator::template Rebind<NodeType>::Other NodeAllocator;
    typedef ListIterator<ValueType> Iterator;
    //typedef Iterator<BidirectionalIteratorTag, _T, Void, _T*, _T&> Iterator;

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
