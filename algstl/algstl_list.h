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

class ListIerator
{
public:
    ListIerator(const _ListNode *p): _p(p) {}
    ListIerator &operator++() //前置自增，返回左值
    {
        _p = _p->next;
        return this;
    }

    ListIerator operator++(int) //后置自增，返回右值
    {
        _ListNode *tmp = _p;
        _p = _p->next;

        return *this;
    }

    _ListNode *_p;
}

template<typename Tp, typename Alloc=ALGSTL_DEFAULT_ALLOCATOR(Tp)>
class List
{
public:
    typedef Alloc _Allocator;
    typedef typename _ListNode<Tp> NodeType;
    typedef _Allocator::rebind<NodeType>::other NodeAllocator;

    List()
    {
        head = _NodeAllocator.allocate(1);
        head->next = head;
        head->prev = head;
    }

    ListIterator begin()
    {
        return head->next;
    }

    void push_back(const value_type &val)
    {
        _ListNode *p = NodeAllocator.allocate(1);
        p->data = val;
        _ListNode *prev = head->prev;

        p->prev = prev;
        p->next = head;
        head->prev = p;
        prev->next = p;
    }
private:
    _NodeType *head; //指向头节点的指针
};

}

#endif
