#ifndef __ALGS_STDSTRING__
#define __ALGS_STDSTRING__

#include "algs_type.h"

namespace algs
{

template<typename _Alloc=Allocator<Char>>
class String
{
friend String operator+(const Char *lhs, const String &rhs);
friend String operator+(const String &lhs, const Char *rhs);
friend String operator+(const String &lhs, const String &rhs);

public:
    //实际存储字符串的缓冲区类
    //维护引用计数等
    template<typename _Alloc>
    struct StringBuf
    {
    public:
        typedef Uint SizeType;
        typedef _Alloc Allocator;
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

        StringBuf():
            buf_(nullptr),
            mstart_(nullptr),
            mend_(nullptr),
            mcapacity_(nullptr),
            ref_count_(0) {}

        StringBuf(SizeType n): StringBuf()
        {
            buf_ = buf_allocator.allocator(n);
            mstart_ = buf_;
            mcapacity_ = buf_ + n;
        }

        void setBuf(const Char *buf, Uint n)
        {
            assert(n < capacity());
            assert(buf_ != nullptr);
            memcpy(buf_, buf, n);
        }

    private:
        Allocator buf_allocator;
    };

    String(): sbuf_(nullptr)
    {
        sbuf_ = new StringBuf;
        assert(sbuf_); //暂时如此
        sbuf_->incr();
    }

    String(const String &rhs)
    {
        sbuf_ = rhs.sbuf_;
        sbuf_->incr(); //增加引用计数
    }

    ~String()
    {
    }

private:
    StringBuf *sbuf_;
};

#if 0
class String
{
friend String operator+(const Char *lhs, const String &rhs);
friend String operator+(const String &lhs, const Char *rhs);
friend String operator+(const String &lhs, const String &rhs);
public:
    struct StringBuf
    {
        typedef Uint SizeType;
        //真正存储字符串的内存指针，每个字符串，以\0结尾
        Char *buf_ = nullptr;
        Int ref_count_;
        SizeType size_;
    };

    typedef StringBuf::SizeType SizeType;

    ~String();
    String();
    String(const String &s);
    String(String &&s);
    String(const Char *s);
    String(const Char *s, SizeType n);

    String &operator=(const String &s);

    constexpr static Char empty_[] = ""; //用作空字符串

    inline const SizeType size() const
    {
        return buf_->size_;
    }

    inline const Char *c_str() const
    {
        if (buf_)
        {
            return buf_->buf_;
        }
        else
        {
            return empty_;
        }
    }

private:
    void set_buf(StringBuf *b)
    {
        if (buf_)
        {
            if (!--buf_->ref_count_)
            {
                free(buf_->buf_);
                delete buf_;
            }
        }

        buf_ = b;
        ++buf_->ref_count_;
    }

    StringBuf *buf_ = nullptr;
};
#endif

String operator+(const Char *lhs, const String &rhs);
String operator+(const String &lhs, const Char *rhs);
String operator+(const String &lhs, const String &rhs);

}

#endif
