#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "stdstring.h"

namespace algs
{

#if 0
constexpr Char String::empty_[];

String::~String()
{
    if (!buf_)
    {
        return;
    }

    if (!--buf_->ref_count_)
    {
        free(buf_->buf_);
        delete buf_;
        buf_ = nullptr;
    }
}

String::String(): buf_(nullptr)
{
}

String::String(const String &s)
{
    assert(buf_ == nullptr);
    buf_ = s.buf_;

    if (buf_) //如果用一个默认构造函数构造的变量来初始化，s.buf_就是nullptr
    {
        ++buf_->ref_count_;
    }
}

String::String(String &&s)
{
    assert(buf_ == nullptr);
    buf_ = s.buf_;
    ++buf_->ref_count_;
    s.buf_ = nullptr; //随后s就会被销毁
}

String::String(const Char *s)
{
    assert(buf_ == nullptr);
    buf_ = new String::StringBuf;
    //strlen不包括结尾的\0
    buf_->size_ = strlen(s);
    buf_->buf_ = static_cast<Char *>(malloc(buf_->size_ + 1));
    memcpy(buf_->buf_, s, buf_->size_);
    buf_->buf_[buf_->size_] = '\0';
    buf_->ref_count_ = 1;
}

String::String(const Char *s, SizeType n)
{
    assert(buf_ == nullptr);
    buf_ = new String::StringBuf;
    buf_->size_ = n;
    buf_->buf_ = static_cast<Char *>(malloc(buf_->size_ + 1));
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

String operator+(const Char *lhs, const String &rhs)
{
    //std::cout << "in " << __LINE__ << std::endl;
    auto lhs_size = strlen(lhs);

    String ret;

    auto new_size = lhs_size + rhs.size();
    auto *p = new String::StringBuf;
    p->buf_ = static_cast<Char *>(malloc(new_size + 1));
    memcpy(p->buf_, lhs, lhs_size);
    memcpy(p->buf_ + lhs_size, rhs.buf_->buf_, rhs.size());
    p->buf_[new_size] = '\0';
    p->size_ = new_size;
    p->ref_count_ = 0;

    ret.set_buf(p);

    return ret;
}

String operator+(const String &lhs, const Char *rhs)
{
    //std::cout << "in " << __LINE__ << std::endl;
    auto rhs_size = strlen(rhs);

    String ret;

    auto new_size = rhs_size + lhs.size();
    auto *p = new String::StringBuf;
    p->buf_ = static_cast<Char *>(malloc(new_size + 1));
    memcpy(p->buf_, lhs.buf_->buf_, lhs.size());
    memcpy(p->buf_ + lhs.size(), rhs, rhs_size);
    p->buf_[new_size] = '\0';
    p->size_ = new_size;
    p->ref_count_ = 0;

    ret.set_buf(p);

    return ret;
}

String operator+(const String &lhs, const String &rhs)
{
    //std::cout << "in " << __LINE__ << std::endl;
    String ret;
    auto *p = new String::StringBuf;
    auto new_size = lhs.size() + rhs.size();
    p->buf_ = static_cast<Char *>(malloc(new_size + 1));
    memcpy(p->buf_, lhs.buf_->buf_, lhs.size());
    memcpy(p->buf_ + lhs.size() , rhs.buf_->buf_, rhs.size());

    p->buf_[new_size] = '\0';
    p->size_ = new_size;
    p->ref_count_ = 0;

    ret.set_buf(p);

    return ret;
}
#endif

}
