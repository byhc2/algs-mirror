#include <iostream>
#include "algs_type.h"

int main(int argc, char *argv[])
{
    //1.1
    std::cout << (0 + 15) / 2 << std::endl; //a
    std::cout << 2.0e-6 * 100000000.1 << std::endl; //b
    //c题编译器会提示&&运算符两边加括号
    std::cout << (true && false || true && true) << std::endl; //c

    //1.2
    std::cout << (1 + 2.236) / 2 << std::endl; //a
    std::cout << 1 + 2 + 3 + 4.0 << std::endl; //b
    std::cout << (4.1 >= 4) << std::endl; //c
    //d题为最后是整数类型加上const char *，结果还是const char *
    //指向字符3后面的3位，所以这里会输出字符6
    std::cout << 1 + 2 + "3456" << std::endl; //d

    return 0;
}
