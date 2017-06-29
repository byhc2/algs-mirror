#include <iostream>
#include "algs_type.h"

int main(int argc, char *argv[])
{
    Int f = 0, g = 1;
    for (auto i = 0; i <= 15; ++i)
    {
        std::cout << f << std::endl;
        f = f + g;
        g = f - g;
    }
    return 0;
}
