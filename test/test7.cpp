#include <iostream>
#include <string>
#include "algstl_list.h"

using namespace std;

int main(int argc, char *argv[])
{
    algstl::List<string> *lst1 = new algstl::List<string>();

    lst1->pushBack("hello");
    lst1->pushBack(" ");
    lst1->pushBack("world");

    for (algstl::List<string>::Iterator it = lst1->begin(); it != lst1->end(); ++it)
    {
        cout << *it << endl;
    }

    for (auto it = lst1->rbegin(); it != lst1->rend(); ++it)
    {
        cout << *it << endl;
    }

    return 0;
}
