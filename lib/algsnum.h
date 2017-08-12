#ifndef __ALGS_NUMBER__
#define __ALGS_NUMBER__

#include "algs_type.h"
#include "algsstring.h"

namespace algs
{

class Num
{
public:
    static Int parseInt(const String &s);
    static Double parseDouble(const String &s);

    //如果具有小数部分，小数部分将具有precision位有效数字
    //浮点数将进行舍入，舍入以后，尾数0会被清除掉
    //如3.14000，会输出为3.14
    //如果整数部分位数超过ipart_precision，将使用科学计数法
    static String toString(Double i, const Int precision=8, const Int ipart_precision=8);

    template<typename _T>
    static String toString(_T i)
    {
        const Char cbuf[] = "0123456789";
        const Int BUFSIZE = 16;
        Char buf[BUFSIZE] = {0};

        if (i == 0)
        {
            return "0"; //特殊情况处理
        }

        Int index = 15;
        bool neg = false;
        if (i < 0) //TODO 无符号数的处理
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

};

}

#endif
