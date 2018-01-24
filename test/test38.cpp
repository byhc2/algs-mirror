#include <iostream>
#include <list>
#include "algstl_list.h"

using namespace std;

int main(int argc, char *argv[])
{
    algstl::List<int> *lst1 = new algstl::List<int>();
    list<int> lst2;

    for (auto i = 0; i < 10000; ++i)
    {
        lst1->pushBack(i);
        lst2.push_back(i);
    }

    cout << lst1->empty() << endl;
    cout << lst1->size() << endl;
    lst1->insert(1000, ++lst1->begin());
    lst1->insert(1000, ++lst1->begin());
    lst1->insert(1000, ++lst1->begin());
    lst1->insert(lst1->begin(), lst1->end(), lst1->begin());
    cout << lst1->size() << endl;
    cout << lst2.size() << endl;
    lst2.insert(lst2.begin(), lst2.end(), lst2.begin());
    cout << lst2.size() << endl;

    delete lst1;

    return 0;
}
