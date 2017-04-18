#ifndef __ALGS_STDSTRING__
#define __ALGS_STDSTRING__

#include <cassert>
#include <cstring>
#include "algs_type.h"
#include "algstl_memory.h"

namespace algs
{

template<typename _Alloc=algstl::Allocator<Char>>
class StringBase
{
#if 0
friend String operator+(const Char *lhs, const String &rhs);
friend String operator+(const String &lhs, const Char *rhs);
friend String operator+(const String &lhs, const String &rhs);
#endif

public:
    //实际存储字符串的缓冲区类
    //维护引用计数等
    template<typename _BufAlloc>
    struct StringBuf
    {
        typedef Uint SizeType;
        typedef _BufAlloc Allocator;
        Char *buf_;
        Char *mstart_;
        Char *mend_;
        Char *mcapacity_;
        Int ref_count_;

        inline SizeType size() const
        {
            return mend_ - mstart_;
        }

        inline Int incr()
        {
            return ++ref_count_;
        }

        inline Int decr()
        {
            return --ref_count_;
        }

        inline SizeType capacity() const
        {
            return mcapacity_ - mstart_;
        }

        ~StringBuf()
        {
            if (buf_)
            {
                buf_allocator.deallocate(buf_, capacity());
            }
        }

        StringBuf(SizeType n=1)
        {
            n += 8; //本来8字节圆整只需要加7，但是考虑到c_str方法一定要多留出一个字节的空间放结束符，所以这里多分配点
            n &= 0xfffffff8; //8字节圆整对齐
            buf_ = buf_allocator.allocate(n);
            mstart_ = buf_;
            mend_ = mstart_;
            mcapacity_ = buf_ + n;
        }

        void append(const Char *buf, Uint n)
        {
            assert(size() + n < capacity());
            assert(buf_);
            mend_ = static_cast<Char *>(mempcpy(mend_, buf, n));
        }

        private:
        Allocator buf_allocator;
    };

    typedef StringBuf<_Alloc> BufferType;
    typedef typename BufferType::SizeType SizeType;

    StringBase(): sbuf_(nullptr)
    {
        sbuf_ = new BufferType(1);
        assert(sbuf_); //暂时如此
        sbuf_->append("\0", 1);
        sbuf_->incr();
    }

    StringBase(const StringBase &rhs)
    {
        sbuf_ = rhs.sbuf_;
        sbuf_->incr(); //增加引用计数
    }

    StringBase(const Char *rhs)
    {
        SizeType n = strlen(rhs);
        sbuf_ = new BufferType(n);
        assert(sbuf_);
        sbuf_->append(rhs, n);
        sbuf_->incr();
    }

    StringBase(const Char *rhs, SizeType n)
    {
        sbuf_ = new BufferType(n);
        assert(!sbuf_);
        sbuf_->append(rhs, n);
    }

    StringBase(SizeType n)
    {
        sbuf_ = new BufferType(n);
        assert(!sbuf_);
    }

    StringBase &operator=(const StringBase &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        if (!sbuf_.decr())
        {
            delete sbuf_;
        }

        sbuf_ = rhs.sbuf_;
        sbuf_->incr();
    }

    StringBase &operator=(const Char *rhs)
    {
        if (!sbuf_.decr())
        {
            delete sbuf_;
        }

        SizeType n = strlen(rhs);
        sbuf_ = new BufferType(n);
        assert(sbuf_);
        sbuf_->append(rhs, n);
        sbuf_->incr();
    }

    ~StringBase()
    {
        if (!sbuf_->decr())
        {
            delete sbuf_;
        }
    }

    const Char *c_str() const
    {
        sbuf_->mend_ = '\0';
        return sbuf_->mstart_;
    }

    const SizeType size() const
    {
        return sbuf_->size();
    }

    void append(const Char *rhs, SizeType n)
    {
        sbuf_->append(rhs, n);
    }

private:
    BufferType *sbuf_;
};
typedef StringBase<> String;

#if 0
String operator+(const Char *lhs, const String &rhs);
String operator+(const String &lhs, const Char *rhs);
String operator+(const String &lhs, const String &rhs);
#endif

}

#endif
