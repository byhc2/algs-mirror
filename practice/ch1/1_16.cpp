//311361142246

#include <iostream>
#include "algs_type.h"
#include "algsstring.h"
#include "algsnum.h"

using namespace algs;
using namespace std;

String exR1(Int n)
{
    if (n <= 0) return "";
    return exR1(n - 3) + algs::Num::toString(n)
        + exR1(n - 2) + algs::Num::toString(n);
}

int main(int argc, char *argv[])
{
    cout << "311361142246" << endl;
    cout << exR1(6) << endl;

    //1.17
    //exR2会无限递归，直到栈溢出
    //因为其结束递归条件被放在了递归调用之后
    //因此不会执行到基本递归条件的代码
    return 0;
}
