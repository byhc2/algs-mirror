#include <iostream>
#include <string>
#include "algstl_array.h"

using namespace std;

int main(int argc, char *argv[])
{
    algstl::Array<Int> a({1, 2, 3});

    cout << a.size() << endl;

    return 0;
}
