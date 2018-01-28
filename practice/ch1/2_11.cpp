#include <iostream>
#include <stdexcept>
#include "algsnum.h"
#include "algsstring.h"

using namespace std;
using namespace algs;

class SmartDate
{
    public:
    SmartDate(Int year, Int month, Int day)
        : year_(year), month_(month), day_(day)
    {
        if (month_ < 0 || month_ > 12)
        {
            throw std::runtime_error(
                ("invalid month value " + Num::toString(month_)).cStr());
        }

        Bool isleap = (year % 100) ? (year % 4) : (year % 400);

        switch (month)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (day < 1 || day > 31)
            {
                throw std::runtime_error(
                    ("invalid day value " + Num::toString(day)).cStr());
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if (day < 1 || day > 30)
            {
                throw std::runtime_error(
                    ("invalid day value " + Num::toString(day)).cStr());
            }
            break;
        case 2:
            if (day < 1 || day > (isleap ? 29 : 28))
            {
                throw std::runtime_error(
                    ("invalid day value " + Num::toString(day)).cStr());
            }
            break;
        default:
            throw std::runtime_error(
                ("invalid month value " + Num::toString(month)).cStr());
        }
    }

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
        return ret;
    }

    private:
    Int year_;
    Int month_;
    Int day_;
};

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cerr << "用法：" << argv[0] << " <年> <月> <日>" << endl;
        return 0;
    }

    SmartDate sd(Num::parseInt(argv[1]), Num::parseInt(argv[2]),
                 Num::parseInt(argv[3]));
    return 0;
}
