#ifndef __ALGS_STDSTRING__
#define __ALGS_STDSTRING__

#include "algs_type.h"

namespace algs
{

class String
{
friend String operator+(const Char *lhs, const String &rhs);
friend String operator+(const String &lhs, const Char *rhs);
friend String operator+(const String &lhs, const String &rhs);
public:
    struct StringBuf
    {
        typedef Uint SizeType;
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

String operator+(const Char *lhs, const String &rhs);
String operator+(const String &lhs, const Char *rhs);
String operator+(const String &lhs, const String &rhs);

}

#endif
