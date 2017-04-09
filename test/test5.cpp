#include <iostream>
#include "algstl_list.h"

using namespace std;

int main(int argc, char *argv[])
{
    Algstl::List<int> lst1;

    lst1.push_back(2);
    lst1.push_back(3);
    lst1.push_back(5);

    auto it = lst1.begin();
    *it;

    for (Algstl::List<int>::Iterator it = lst1.begin(); it != lst1.end(); ++it)
    {
        cout << *it << endl;
    }

    return 0;
}
