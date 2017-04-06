#ifndef __ALGSTL_LIST_H__
#define __ALGSTL_LIST_H__

//双向链表

#include "algstl_memory.h"

namespace Algstl
{

template<typename Tp>
class _ListNode
{
public:
    _ListNode *next;
    _ListNode *prev;
    Tp data;
};

template<typename Tp>
class ListIterator
{
public:
    ListIterator(const _ListNode<Tp> *p): _p(p) {}
    ListIterator &operator++() //前置自增，返回左值
    {
        _p = _p->next;
        return _p;
    }

    ListIterator operator++(int) //后置自增，返回右值
    {
        _ListNode<Tp> *tmp = _p;
        _p = _p->next;

        return tmp;
    }

    Tp &operator*()
    {
        return _p->data;
    }

    _ListNode<Tp> *_p;
};

template<typename Tp>
bool operator!=(const ListIterator<Tp> &lhs, const ListIterator<Tp> &rhs)
{
    return lhs._p != rhs._p;
}

template<typename Tp, typename Alloc=Allocator<Tp>>
class List
{
public:
    typedef Tp value_type;
    typedef Alloc _Allocator;
    typedef _ListNode<Tp> _NodeType;
    typedef typename _Allocator::template rebind<_NodeType>::other _NodeAllocator;
    typedef ListIterator<_NodeType> Iterator;

    List()
    {
        head = alloc.allocate(1);
        head->next = head;
        head->prev = head;
    }

    Iterator begin()
    {
        return head->next;
    }

    Iterator end()
    {
        return head; //返回head自己
    }

    void push_back(const value_type &val)
    {
        _NodeType *p = alloc.allocate(1);
        p->data = val;
        _NodeType *prev = head->prev;

        p->prev = prev;
        p->next = head;
        head->prev = p;
        prev->next = p;
    }
private:
    _NodeType *head; //指向头节点的指针
    _NodeAllocator alloc;
};

}

#endif
