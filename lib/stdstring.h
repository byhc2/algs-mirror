#ifndef __ALGS_STDSTRING__
#define __ALGS_STDSTRING__

#include "algs_type.h"

namespace algs
{

class String
{
public:
    struct StringBuf
    {
        typedef Uint SizeType;
        Char *buf_ = nullptr;
        Int ref_count_;
        SizeType size_;
    };

    typedef StringBuf::SizeType SizeType;

    String() = default;
    String(const String &s);
    String(String &&s);
    String(const Char *s);
    String(const Char *s, SizeType n);

    String &operator=(const String &s);

    const Char *empty_ = ""; //用作空字符串

    inline const Char *c_str()
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
    StringBuf *buf_ = nullptr;
};

#if 0
String operator+(const Char *lhs, const String &rhs);
String operator+(const String &lhs, const Char *rhs);
String operator+(const String &lhs, const String &rhs);
#endif

}

#endif
