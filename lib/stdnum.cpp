#include <cstdlib>
#include "stdnum.h"

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

String Num::toString(Double d)
{
    //分离出符号位，指数位和位数位
    unsigned long ud = static_cast<unsigned long>(d);
    int sign = ud & 0x8fffffffffffffff >> 63;
    int exp =  ud & 0x7ff0000000000000 >> 52;
    int frac = ud & 0x000fffffffffffff;

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

    if (exp == 0)
    {
        //非规约数
        exp = 1 - exp; //真实的指数
        //将尾数的前导0加到指数上
        while (frac & 
    }
    else
    {
        //规约数
    }
}

String Num::toString(Int i)
{
    const Char cbuf[] = "0123456789";
    const Int BUFSIZE = 16;
    Char buf[BUFSIZE] = {0};

    Int index = 15;
    bool neg = false;
    if (i < 0)
    {
        neg = true;
        i = -i;
    }

    while (i > 0)
    {
        assert(index > 0);
        buf[index--] = cbuf[i % 10];
        i /= 10;
    }

    assert(index >= 0);

    if (neg)
    {
        buf[index] = '-';
    }

    index = 0;
    while (buf[index] == 0)
    {
        ++index;
    }

    return String(buf + index, BUFSIZE - index);
}

}
