#ifndef __UTILALGS_COUNTER__
#define __UTILALGS_COUNTER__

#include <iostream>
#include "algs_type.h"
#include "algsstring.h"

namespace algs
{
class Counter
{
    friend std::ostream &operator<<(std::ostream &os, const Counter &rhs);

    public:
    Counter(const String &id = "anonymous") : id_(id), count_(0)
    {}
    Counter(const Counter &rhs) : id_(rhs.id_), count_(rhs.count_)
    {}
    Counter &increment();
    Int tally();
    algs::String toString();
    Counter &operator++();
    Counter operator++(Int);
    Counter &operator=(const Counter &rhs);

    private:
    String id_;
    Int count_;
};

}

#endif
