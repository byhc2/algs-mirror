#include <iostream>
#include "algsdraw.h"
#include "algsstring.h"
#include "algstl_array.h"

using namespace algs;
using namespace std;
using namespace algstl;

class VisualCounter
{
    public:
    VisualCounter(const algs::String &id = "anonymous");
    VisualCounter &increment();
    algs::String toString();
    VisualCounter &operator++();
    VisualCounter operator++(Int);
    VisualCounter &operator--();
    VisualCounter operator--(Int);
    VisualCounter &operator=(const VisualCounter &rhs);
    Int tally();
    Void show();

    private:
    String id_;
    Int count_;
    algstl::Array<Int> data_;
    Int max_;
    Int min_;
};

VisualCounter::VisualCounter(const String &id)
    : id_(id), count_(0), max_(0), min_(0)
{}

VisualCounter &VisualCounter::increment()
{
    ++count_;
    if (count_ > max_)
    {
        max_ = count_;
    }
    return *this;
}

algs::String VisualCounter::toString()
{
    return id_ + ": " + Num::toString(count_);
}

VisualCounter &VisualCounter::operator--()
{
    --count_;
    if (count_ < min_)
    {
        min_ = count_;
    }
    data_ += count_;
    return *this;
}

VisualCounter VisualCounter::operator--(Int)
{
    auto tmp = *this;
    --count_;
    if (count_ < min_)
    {
        min_ = count_;
    }
    data_ += count_;
    return tmp;
}

VisualCounter &VisualCounter::operator++()
{
    ++count_;
    if (count_ > max_)
    {
        max_ = count_;
    }
    data_ += count_;
    return *this;
}

VisualCounter VisualCounter::operator++(Int)
{
    auto tmp = *this;
    ++count_;
    if (count_ > max_)
    {
        max_ = count_;
    }
    data_ += count_;
    return tmp;
}

Int VisualCounter::tally()
{
    return count_;
}

void VisualCounter::show()
{
    auto xpadding = data_.size() * 0.1;
    auto ypadding = max_ * 0.1;
    AlgsDraw::setXscale(-xpadding, data_.size() + xpadding);
    AlgsDraw::setYscale(min_ - ypadding, max_ + ypadding);

    for (auto i = 1; i < data_.size(); ++i)
    {
        AlgsDraw::line(i - 1, data_[i - 1], i, data_[i]);
    }

    AlgsDraw::show();

    return;
}

VisualCounter &VisualCounter::operator=(const VisualCounter &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    id_    = rhs.id_;
    count_ = rhs.count_;
    data_  = rhs.data_;
    max_   = rhs.max_;

    return *this;
}

int main(int argc, char *argv[])
{
    VisualCounter c;
    Int x;
    while (cin >> x)
    {
        if (x > 0)
        {
            ++c;
        }
        else if (x < 0)
        {
            --c;
        }
    }

    c.show();

    return 0;
}
