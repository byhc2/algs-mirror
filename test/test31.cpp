#include <iostream>
#include "algstl_array.h"

using namespace algstl;
using namespace algs;
using namespace std;

int main(int argc, char *argv[])
{
    Array<Int> a = {1, 2, 3, 4};

    auto it = a.begin() + 2;
    a.erase(it);

    for (auto r : a)
    {
        cout << "==> " << r << endl;
    }
    return 0;
}
