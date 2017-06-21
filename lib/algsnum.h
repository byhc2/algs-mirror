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
    static String toString(Int i);

    //如果具有小数部分，小数部分将具有precision位有效数字
    //浮点数将进行舍入，舍入以后，尾数0会被清除掉
    //如3.14000，会输出为3.14
    //如果整数部分位数超过ipart_precision，将使用科学计数法
    static String toString(Double i, const Int precision=8, const Int ipart_precision=8);
};

}

#endif
