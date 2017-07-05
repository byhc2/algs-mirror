#include <iostream>
#include "algs_type.h"
#include "algstl_array.h"

using namespace std;
using namespace algstl;

int main(int argc, char *argv[])
{
    Array<Int> a;

    for (auto i = 0; i < 10; ++i)
    {
        a[i] = 9; //assert失败，此时size()是0
    }

    return 0;
}
