#ifndef __COUNTER__
#define __COUNTER__

#include <iostream>
#include "algs_type.h"
#include "algsstring.h"

namespace algs
{

class Counter
{
friend std::ostream &operator<<(std::ostream &os, const Counter &rhs);
public:
    Counter(const String &id="anonymous"): id_(id), count_(0) {}
    Counter &increment();
    Int tally();
    algs::String toString();
    Counter &operator++();
    Counter &operator++(Int);
private:
    String id_;
    Int count_;
};

}

#endif
