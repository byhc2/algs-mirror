#include <iostream>
#include "algs_type.h"

using namespace std;

static Int lg(Int n)
{
    //这里假设n是大于0的
    Uint c = 0;
    while (n)
    {
        ++c;
        n >>= 1;
    }

    return c - 1;
}

int main(int argc, char *argv[])
{
    for (auto i = 1; i < 32; ++i)
    {
        cout << i << ": " << lg(i) << endl;
    }

    return 0;
}
