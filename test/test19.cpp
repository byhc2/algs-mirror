#include <iostream>
#include <string>
#include "algstl_array.h"

using namespace std;

int main(int argc, char *argv[])
{
    algstl::Array<Int> a1;

    a1 = a1 + 3;
    a1 = a1 + 4;

    for (auto it = a1.begin(); it != a1.end(); ++it)
    {
        std::cout << "Hello " << *it << endl;
    }

    return 0;
}
