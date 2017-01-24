#ifndef __ALGSTL_MEMORY_H__
#define __ALGSTL_MEMORY_H__

#include <new>

namespace algstl
{

template <typename Tp>
class allocator
{

public:
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;
    typedef Tp*        pointer;
    typedef const Tp*  const_pointer;
    typedef Tp&        reference;
    typedef const Tp&  const_reference;
    typedef Tp         value_type;

    //这里需要单独声明一个struct
    //使容器层在使用这个allocator的时候
    //可以通过rebind来声明与容器相关的一种allocator
    //比如list容器，数据本身是存放在list_node中的
    //所以在知道了数据本身的allocator之后
    //可以通过rebind来得到list_node的allocator
    template <typename Tp1> struct rebind
    {
        typedef allocator<Tp1> other;
    };

    allocator() = default;
    allocator(const allocator &) {}
    template <typename Tp1> allocator(const allocator<Tp1> &) {}
    ~allocator() {}

    pointer address(reference x) const
    {
        return &x;
    }

    const_pointer address(const_reference x) const
    {
        return &x;
    }

    Tp *allocate(size_type n)
    {
        if (n == 0)
        {
            return 0;
        }

        void *p = malloc(n * sizeof(Tp));
        if (p)
        {
            return p;
        }
        throw bad_alloc();
    }

    void deallocate(pointer p, size_type n)
    {
        //因为分配的时候调用的是malloc
        //操作系统已经记录了n的信息
        //所以这里不用再使用n
        free(p);
    }

    void construct(pointer p, const Tp &val)
    {
        //new (p) Tp(val);
        new (p) (val); //FIXME 试试这样行不行
    }
};

}

#endif
