#include <iostream>
#include "algs_type.h"
#include "algstl_array.h"

using namespace std;
using namespace algstl;

int main(int argc, char *argv[])
{
    Array<Int> a(10);

    for (auto i = 0; i < 10; ++i)
    {
        a[i] = 9 - i;
    }

    cout << a.toString() << endl;

    for (auto i = 0; i < 10; ++i)
    {
        a[i] = a[a[i]];
    }

    cout << a.toString() << endl;

    for (auto r: a)
    {
        cout << r << endl;
    }

    return 0;
}
