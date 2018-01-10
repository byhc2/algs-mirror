#ifndef __UTILALGS_GEOMETRY__
#define __UTILALGS_GEOMETRY__

#include <iostream>
#include <sstream>
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
    //如果传入的x大于等于y，则构造出空区间
    Interval1D(Double x, Double y) : lo_(x), hi_(y)
    {}

    Interval1D() : lo_(0), hi_(0)
    {}

    Interval1D(const Interval1D &rhs)
    {
        lo_ = rhs.lo_;
        hi_ = rhs.hi_;
    }

    //判断区间非空时使用
    operator bool() const
    {
        return lo_ < hi_;
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

    Bool operator==(const Interval1D &rhs) const
    {
        return (lo_ == rhs.lo_) && (hi_ == rhs.hi_);
    }

    Double center() const
    {
        if (*this)
        {
            return (lo_ + hi_) / 2.0;
        }
        else
        {
            std::stringstream ss;
            ss << *this;
            throw std::runtime_error("空区间" + ss.str());
        }
    }

    Double length() const
    {
        if (*this)
        {
            return hi_ - lo_;
        }
        else
        {
            //空区间
            return 0;
        }
    }

    //如果p位于包含端点的x_和y_区间内，返回1
    Bool contains(Double p) const
    {
        return (lo_ <= p) && (p <= hi_);
    }

    Interval1D intersect(const Interval1D &rhs) const
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

        if (!*this || !rhs)
        {
            //有一个区间为空，则返回空
            return Interval1D(1, 0);
        }
        else if (i1->hi_ <= i2->lo_)
        {
            return Interval1D(1, 0);  //返回空区间
        }
        else if (i1->hi_ < i2->hi_)
        {
            // i1 i2相交
            return Interval1D(i2->lo_, i1->hi_);
        }
        else
        {
            // i1包含i2
            return Interval1D(i2->lo_, i2->hi_);
        }
    }

    Double lo_;
    Double hi_;
};

inline Interval1D operator&(const Interval1D &lhs, const Interval1D &rhs)
{
    return lhs.intersect(rhs);
}

std::ostream &operator<<(std::ostream &os, const Interval1D &rhs)
{
    os << "(" << rhs.lo_ << ", " << rhs.hi_ << ")";
    return os;
}

class Interval2D
{
    public:
    Interval2D(const Interval1D &x, const Interval1D &y) : x_(x), y_(y)
    {}

    Interval2D(const Interval2D &rhs)
    {
        x_ = rhs.x_;
        y_ = rhs.y_;
    }

    operator bool()
    {
        return x_ && y_;
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

    Bool operator==(const Interval2D &rhs) const
    {
        return (x_ == rhs.x_) && (y_ == rhs.y_);
    }

    Point2D center() const
    {
        return Point2D(x_.center(), y_.center());
    }

    Double area() const
    {
        if (x_ && y_)
        {
            return x_.length() * y_.length();
        }
        else
        {
            //空区间
            return 0;
        }
    }

    Bool contains(const Point2D &rhs) const
    {
        return x_.contains(rhs.x_) && y_.contains(rhs.y_);
    }

    Bool contains(Double x, Double y) const
    {
        return y_.contains(x) && y_.contains(y);
    }

    Interval2D intersect(const Interval2D &rhs) const
    {
        return Interval2D(x_.intersect(rhs.x_), y_.intersect(rhs.y_));
    }

    Interval1D x_;
    Interval1D y_;
};

inline Interval2D operator&(const Interval2D &lhs, const Interval2D &rhs)
{
    return lhs.intersect(rhs);
}

std::ostream &operator<<(std::ostream &os, const Interval2D &rhs)
{
    os << "(" << rhs.x_ << ", " << rhs.y_ << ")";
    return os;
}
}

#endif
