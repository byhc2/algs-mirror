#ifndef __UTILALGS_GEOMETRY__
#define __UTILALGS_GEOMETRY__

#include "algs_type.h"

namespace algs
{

//对外只读的属性声明
template<typename _Class, typename _MemberType>
class ReadOnly
{
friend _Class;
private:
    _MemberType m_;
    _MemberType &operator=(const _MemberType &arg)
    {
        m_ = arg;
        return m_;
    }
public:
    ReadOnly(const _MemberType &m)
    {
        m_ = m;
    }

    ReadOnly()
    {
        m_ = _MemberType();
    }

    operator const _MemberType&() const
    {
        return m_;
    }
};

//二维平面上的点
class Point2D
{
public:
    //一下两个类是为了区分构造函数的类
    class Theta
    {
    public:
        Theta(): t_(0) {}
        Double t_;
    };

    Point2D();
    Point2D(Double x, Double y);
    Point2D(Theta t, Double r);

    Void setX(Double x)
    {
        x_ = x;
    }

    Void setY(Double y)
    {
        y_ = y;
    }

    ReadOnly<Point2D, Double> x_;
    ReadOnly<Point2D, Double> y_;
    ReadOnly<Point2D, Double> theta_;
    ReadOnly<Point2D, Double> r_;
};

Point2D::Theta operator""_r(Ldouble t)
{
    Point2D::Theta ret;
    ret.t_ = t;
    return ret;
}

}

#endif
