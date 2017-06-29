#include <iostream>
#include "algs_type.h"

int main(int argc, char *argv[])
{
    //1.5
    Double x, y;

    std::cin >> x >> y;

    if (0 < x && x < 1 && 0 < y && y < 1)
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    return 0;
}
