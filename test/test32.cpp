#include <iostream>
#include "algsstring.h"
#include "algstl_array.h"

using namespace algstl;
using namespace algs;
using namespace std;

int main(int argc, char *argv[])
{
    Array<String> a = {"Hello0", "Hello1", "Hello2", "Hello3"};

    auto it = a.begin();
    while (it != a.end() - 1)
    {
        cout << *a.erase(it) << endl;
    }
    return 0;
}
