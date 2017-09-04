#include <cstdlib>
#include <cmath>
#include <iostream>
#include "algsnum.h"

namespace algs
{

Int Num::parseInt(const String &s)
{
    return atoi(s.c_str());
}

Double Num::parseDouble(const String &s)
{
    return atof(s.c_str());
}

String Num::toString(Double d, const Int precision, const Int ipart_precision)
{
    //分离出符号位，指数位和位数位
    Ulong *ud = (Ulong*)(&d);
    Int sign = (*ud & 0x8000000000000000) >> 63;
    int exp =  (*ud & 0x7ff0000000000000) >> 52;
    int frac = *ud & 0x000fffffffffffff;

    //判断几类特殊数字
    if (exp == 0 && frac == 0)
    {
        if (sign == 0)
        {
            return "0.0";
        }
        else
        {
            return "-0.0";
        }
    }

    if (exp == 0x7ff && frac == 0)
    {
        if (sign == 0)
        {
            return "Inf";
        }
        else
        {
            return "-Inf";
        }
    }

    if (exp == 0x7ff && frac != 0)
    {
        return "NaN";
    }

    //以下为平常浮点数，转换步骤为：
    //1，先计算log10(d)，得到整数部分位数或者小数部分起头的0的位数
    //  具体为：...
    //          -3 <= log10(d) < -2     小数部分2个0
    //          -2 <= log10(d) < -1     小数部分1个0
    //          -1 <= log10(d) <  0     小数部分0个0
    //           0 <= log10(d) <  1     整数部分为1位
    //           1 <= log10(d) <  2     整数部分为2位
    //           2 <= log10(d) <  3     整数部分为3位

    String ret = "";
    if (sign)
    {
        ret += "-";
    }

    //以下代码未实现，先暂时使用snprintf
    String lgstr = String("%.") + Num::toString(precision) + "lg";

    Int mag = static_cast<Int>(floorl(log10(d) + 1));
    char buf[50];
    if (0 <= mag && mag < ipart_precision)
    {
        //正常整数部分
#if 0
        Int int_part = static_cast<Int>(d);
        ret += Num::toString(int_part);
        ret += ".";

        d -= int_part;
        Int frac_part = static_cast<Int>(pow(10, precision) * d);
        ret += Num::toString(frac_part);
#endif
        snprintf(buf, 50, lgstr.c_str(), d);
    }
    else if (ipart_precision < mag)
    {
        //科学计数法
        snprintf(buf, 50, "%e", d);
    }
    else if (-ipart_precision <= mag && mag < 0)
    {
        //小数部分填充0
        snprintf(buf, 50, lgstr.c_str(), d);
    }
    else
    {
        //科学计数法
        snprintf(buf, 50, "%e", d);
    }

    ret = buf;
    return ret;
}

}
