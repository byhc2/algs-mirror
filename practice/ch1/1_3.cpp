#include <iostream>
#include "algs_type.h"

int main(int argc, char *argv[])
{
    //1.3
    Int a, b, c;
    std::cin >> a >> b >> c;
    if ((a == b) && (b == c))
    {
        std::cout << "equal" << std::endl;
    }
    else
    {
        std::cout << "not equal" << std::endl;
    }

    //1.4
    //a, b均错误，c++无此语法
    //c, d正确

    return 0;
}
