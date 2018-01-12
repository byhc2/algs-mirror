#ifndef __UTILALGS_MISC__
#define __UTILALGS_MISC__

#include <iostream>
#include "algs_type.h"
#include "algsnum.h"
#include "algsstring.h"

namespace algs
{
class Date
{
    public:
    Date(Int year, Int month, Int day) : year_(year), month_(month), day_(day)
    {}

    Int day()
    {
        return day_;
    }
    Int year()
    {
        return year_;
    }
    Int month()
    {
        return month_;
    }

    algs::String toString(bool desc = false)
    {
        if (!desc)
        {
            return algs::Num::toString(year_) + "-"
                   + algs::Num::toString(month_) + "-"
                   + algs::Num::toString(day_);
        }

        algs::String ret = algs::Num::toString(year_) + "年"
                           + algs::Num::toString(month_) + "月"
                           + algs::Num::toString(day_) + "日";
        //此处涉及练习2.12，因星期几这个问题比较虚妄
        //涉及格里高利历和凯撒历的切换，且我不认同这种历法的合理性
        //故此处不再继续
    }

    private:
    Int year_;
    Int month_;
    Int day_;
};

class Transaction
{
    // TODO 暂不实现
};
}

#endif
