#include <iostream>
#include "algstl_list.h"

using namespace std;
using namespace algstl;

int main(int argc, char *argv[])
{
    List<int> lst2;

    for (auto i = 0; i < 10; ++i)
    {
        lst2.pushBack(i);
    }

    cout << lst2.size() << endl;
    lst2.insert(lst2.begin(), lst2.end(), lst2.end());
    cout << lst2.size() << endl;
    return 0;
}
