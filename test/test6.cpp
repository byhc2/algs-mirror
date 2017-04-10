#include <iostream>
#include "algstl_list.h"

using namespace std;

int main(int argc, char *argv[])
{
    algstl::List<int> *lst1 = new algstl::List<int>();

    lst1->pushBack(2);
    lst1->pushBack(3);
    lst1->pushBack(5);

    for (algstl::List<int>::Iterator it = lst1->begin(); it != lst1->end(); ++it)
    {
        cout << *it << endl;
    }

    return 0;
}
