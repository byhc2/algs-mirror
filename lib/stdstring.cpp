#include <cassert>
#include <cstring>
#include <cstdlib>
#include "stdstring.h"

namespace algs
{

String::String(const String &s)
{
    assert(buf_ == nullptr);
    buf_ = s.buf_;
}

String::String(String &&s)
{
    assert(buf_ == nullptr);
    buf_ = s.buf_;
}

String::String(const Char *s)
{
    assert(buf_ == nullptr);
    buf_ = new String::StringBuf;
    buf_->size_ = strlen(s);
    buf_->buf_ = static_cast<Char *>(malloc(buf_->size_));
    memcpy(buf_->buf_, s, buf_->size_);
    buf_->ref_count_ = 1;
}

String::String(const Char *s, SizeType n)
{
    assert(buf_ == nullptr);
    buf_ = new String::StringBuf;
    buf_->size_ = n + 1;
    buf_->buf_ = static_cast<Char *>(malloc(buf_->size_));
    memcpy(buf_->buf_, s, n);
    buf_->ref_count_ = 1;
    buf_->buf_[n] = '\0';
}

String &String::operator=(const String &s)
{
    if (this == &s)
    {
        return *this;
    }

    if (buf_)
    {
        --buf_->ref_count_;
        if (!buf_->ref_count_)
        {
            free(buf_->buf_);
        }
    }

    delete buf_;

    buf_->buf_ = s.buf_->buf_;
    buf_->size_ = s.buf_->size_;
    ++s.buf_->ref_count_;

    return *this;
}

}
