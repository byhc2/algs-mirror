#include <iostream>
#include <string>
#include "algstl_array.h"

using namespace std;

int main(int argc, char *argv[])
{
    algstl::Array<Int> a1;
    std::cout << "Hello" << std::endl;

    a1 += 4;
    a1 += 3;
    a1 += 8;
    a1 += 9;

    std::cout << "Hello" << std::endl;
    a1.sort([](const Int &a, const Int &b) {return a > b;});

    for (auto it = a1.begin(); it != a1.end(); ++it)
    {
        std::cout << "Hello " << *it << endl;
    }

    return 0;
}
