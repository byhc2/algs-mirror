#ifndef __ALGSTL_MEMORY_H__
#define __ALGSTL_MEMORY_H__

namespace Algstl
{

template <typename _Tp>
class Allocator
{

public:
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;
    typedef _Tp*        pointer;
    typedef const _Tp*  const_pointer;
    typedef _Tp&        reference;
    typedef const _Tp&  const_reference;
    typedef _Tp         value_type;

    //这里需要单独声明一个struct
    //使容器层在使用这个allocator的时候
    //可以通过rebind来声明与容器相关的一种allocator
    //比如list容器，数据本身是存放在list_node中的
    //所以在知道了数据本身的allocator之后
    //可以通过rebind来得到list_node的allocator
    template <typename _Tp1> struct rebind
    {
        typedef allocator<_Tp1> other;
    };

    allocator() = default;
    allocator(const allocator &) {}
    template <typename _Tp1> allocator(const allocator<_Tp1> &) {}
    ~allocator() {}

    pointer address(reference x) const
    {
        return &x;
    }

    const_pointer address(const_reference x) const
    {
        return &x;
    }

    _Tp *allocate(size_type n)
    {
        if (n == 0)
        {
            return 0;
        }

        void *p = malloc(n * sizeof(_Tp));
        if (p)
        {
            return p;
        }
        throw bad_alloc();
    }

    void deallocate(pointer p, size_type n)
    {
        free(p);
    }
};

}

#endif
