#ifndef __UTILALGS_GEOMETRY__
#define __UTILALGS_GEOMETRY__

#include "algs_type.h"

namespace algs
{

//二维平面上的点
class Point2D
{
public:
    Point2D();
    Point2D(Double x, Double y);

    Void setX(Double x)
    {
        x_ = x;
    }

    Void setY(Double y)
    {
        y_ = y;
    }

    Double x_;
    Double y_;
};

class Interval1D
{
public:
    Interval1D(Double x, Double y):
        lo_(x < y ? x : y), hi_(x < y ? y : x) {}

    Interval1D(): lo_(0), hi_(0) {}

    Interval1D(const Interval1D &rhs)
    {
        lo_ = rhs.lo_;
        hi_ = rhs.hi_;
    }

    Interval1D &operator=(Interval1D &&rhs)
    {
        lo_ = rhs.lo_;
        hi_ = rhs.hi_;

        return *this;
    }

    Interval1D &operator=(const Interval1D &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        lo_ = rhs.lo_;
        hi_ = rhs.hi_;

        return *this;
    }

    Double length() const
    {
        return hi_ - lo_;
    }

    //如果p位于包含端点的x_和y_区间内，返回1
    Bool contains(Double p) const
    {
        return (lo_ <= p) && (p <= hi_);
    }

    Bool intersect(const Interval1D &rhs) const
    {
        const Interval1D *i1, *i2;
        if (lo_ < rhs.lo_)
        {
            i1 = this;
            i2 = &rhs;
        }
        else
        {
            i1 = &rhs;
            i2 = this;
        }

        if (i2->lo_ <= i1->hi_)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Double lo_;
    Double hi_;
};

class Interval2D
{
public:
    Interval2D(const Interval1D &x, const Interval1D &y):
        x_(x), y_(y) {}

    Interval2D(const Interval2D &rhs)
    {
        x_ = rhs.x_;
        y_ = rhs.y_;
    }

    Interval2D &operator=(const Interval2D &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        x_ = rhs.x_;
        y_ = rhs.y_;

        return *this;
    }

    Double area() const
    {
        return x_.length() * y_.length();
    }

    Bool contains(const Point2D &rhs) const
    {
        return x_.contains(rhs.x_) && y_.contains(rhs.y_);
    }

    Bool contains(Double x, Double y) const
    {
        return y_.contains(x) && y_.contains(y);
    }

    Bool intersect(const Interval2D &rhs) const
    {
        return x_.intersect(rhs.x_) && y_.intersect(rhs.y_);
    }

    Interval1D x_;
    Interval1D y_;
};

}

#endif
