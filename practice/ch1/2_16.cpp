// 2.13 略
// 2.14 略
// 2.15 略

// 2.16 2.17均在以下代码中
#include <iostream>
#include <stdexcept>
#include "algs_type.h"
#include "algsmath.h"
#include "algsstring.h"
#include "gcd.h"

using namespace std;
using namespace algs;

class Rational
{
    friend Rational operator+(const Rational &lhs, const Rational &rhs);
    friend Rational operator-(const Rational &lhs, const Rational &rhs);
    friend Rational operator*(const Rational &lhs, const Rational &rhs);
    friend Rational operator/(const Rational &lhs, const Rational &rhs);
    friend ostream &operator<<(ostream &os, const Rational &rhs);
    friend Bool operator==(const Rational &lhs, const Rational &rhs);

    public:
    Rational(Long numerator, Long denominator);
    Rational() : Rational(0, 1){};
    Rational(Long v) : Rational(v, 1){};
    algs::String toString() const;
    Bool operator==(Double rhs) const;
#if 0
    Bool operator==(Long rhs);
    Bool operator==(Int rhs);
#endif

    private:
    Long num_;
    Long denom_;
};

Rational::Rational(Long numerator, Long denominator)
    : num_(numerator), denom_(denominator)
{
    if (denom_ == 0)
    {
        throw std::domain_error("denominator is 0");
    }

    //将负号统一移到分子上
    if (denom_ < 0)
    {
        denom_ = -denom_;
        num_   = -num_;
    }

    auto g = AlgsMath::abs(gcd(num_, denom_));
    num_ /= g;
    denom_ /= g;
}

Rational operator+(const Rational &lhs, const Rational &rhs)
{
    Long g = gcd(lhs.denom_, rhs.denom_);

    auto f1 = rhs.denom_ / g;  // f1必然大于0
    auto f2 = lhs.denom_ / g;  // f2必然大于0

    auto n1 = lhs.num_ * f1;
    auto n2 = rhs.num_ * f2;

    //分子溢出
    if ((lhs.num_ > 0 && n1 < 0) || (lhs.num_ < 0 && n1 > 0))
    {
        throw std::overflow_error("numerator overflow");
    }
    if ((rhs.num_ > 0 && n2 < 0) || (rhs.num_ < 0 && n2 > 0))
    {
        throw std::overflow_error("numerator overflow");
    }

    auto n = n1 + n2;
    if ((n1 > 0 && n2 > 0 && n < 0) || (n1 < 0 && n2 < 0 && n > 0))
    {
        throw std::overflow_error("numerator overflow");
    }

    auto d = f1 * f2;
    //构造函数保证了分母大于0
    //故此仅判断d小于0
    if (d < 0)
    {
        throw std::overflow_error("denominator overflow");
    }

    return Rational(n, d);
}

Rational operator-(const Rational &lhs, const Rational &rhs)
{
    auto g = gcd(lhs.denom_, rhs.denom_);

    auto f1 = rhs.denom_ / g;
    auto f2 = lhs.denom_ / g;

    auto n1 = lhs.num_ * f1;
    auto n2 = rhs.num_ * f2;

    if ((lhs.num_ > 0 && n1 < 0) || (lhs.num_ < 0 && n1 > 0))
    {
        throw std::overflow_error("numerator overflow");
    }
    if ((rhs.num_ > 0 && n2 < 0) || (rhs.num_ < 0 && n2 > 0))
    {
        throw std::overflow_error("numerator overflow");
    }
    auto n = n1 - n2;
    if ((n1 < 0 && n2 > 0 && n > 0) || (n1 > 0 && n2 < 0 && n < 0))
    {
        throw std::overflow_error("numerator overflow");
    }

    auto d = f1 * f2;
    if (d < 0)
    {
        throw std::overflow_error("denominator overflow");
    }

    return Rational(n, d);
}

Rational operator*(const Rational &lhs, const Rational &rhs)
{
    //两因数均已化简
    //符号单独取出，便于判定溢出
    Int sign = 1;
    if ((lhs.num_ < 0 && rhs.num_ > 0) || (lhs.num_ > 0 && rhs.num_ < 0))
    {
        sign = -1;
    }
    //此处两因数之分子互换
    //构造时继续化简，避免乘法中途溢出
    auto r1 = Rational(AlgsMath::abs(lhs.num_), rhs.denom_);
    auto r2 = Rational(AlgsMath::abs(rhs.num_), lhs.denom_);
    auto n  = r1.num_ * r2.num_;
    auto d  = r2.denom_ * r2.denom_;
    if (n < 0)
    {
        throw std::overflow_error("numerator overflow");
    }
    if (d < 0)
    {
        throw std::overflow_error("denominator overflow");
    }
    return Rational(sign * r1.num_ * r2.num_, r1.denom_ * r2.denom_);
}

Rational operator/(const Rational &lhs, const Rational &rhs)
{
    //防止除0
    if (rhs == 0)
    {
        throw std::domain_error("divisor is 0");
    }
    return lhs * Rational(rhs.denom_, rhs.num_);
}

#if 0
Bool Rational::operator==(Int rhs)
{
    return num_ / denom_ == rhs;
}

Bool Rational::operator==(Long rhs)
{
    return num_ / denom_ == rhs;
}
#endif

Bool Rational::operator==(Double rhs) const
{
    return num_ / static_cast<Double>(denom_) == rhs;
}

Bool operator==(const Rational &lhs, const Rational &rhs)
{
    return (lhs.num_ == rhs.num_) && (lhs.denom_ == rhs.denom_);
}

Bool operator!=(const Rational &lhs, const Rational &rhs)
{
    return !(lhs == rhs);
}

ostream &operator<<(ostream &os, const Rational &rhs)
{
    if (rhs.denom_ == 1)
    {
        os << rhs.num_;
    }
    else
    {
        os << rhs.num_ << "/" << rhs.denom_;
    }
    return os;
}

int main(int argc, char *argv[])
{
    Long x1, x2, x3, x4;

    while (cin >> x1 >> x2 >> x3 >> x4)
    {
        if (x2 == 0)
        {
            x2 = 1;
        }
        if (x4 == 0)
        {
            x4 = 1;
        }
        auto r1 = Rational(x1, x2);
        auto r2 = Rational(x3, x4);

        cout << r1 << " + " << r2 << " = " << r1 + r2 << endl;
        cout << r1 << " - " << r2 << " = " << r1 - r2 << endl;
        cout << r1 << " * " << r2 << " = " << r1 * r2 << endl;
        if (r2 != 0)
        {
            cout << r1 << " / " << r2 << " = " << r1 / r2 << endl;
        }
    }
    return 0;
}

// 2.19 略
