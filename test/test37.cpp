#include <iostream>
#include "algstl_list.h"

using namespace std;

int main(int argc, char *argv[])
{
    algstl::List<int> *lst1 = new algstl::List<int>();

    lst1->pushBack(2);
    lst1->pushBack(3);
    lst1->pushBack(5);

    for (algstl::List<int>::ConstIterator it = lst1->cbegin();
         it != lst1->cend(); ++it)
    {
        cout << *it << endl;
    }

    for (algstl::List<int>::Iterator it = lst1->begin(); it != lst1->end();
         ++it)
    {
        cout << *it << endl;
    }

    for (algstl::List<int>::ReverseIterator it = lst1->rbegin();
         it != lst1->rend(); ++it)
    {
        cout << *it << endl;
    }

    for (algstl::List<int>::ConstReverseIterator it = lst1->crbegin();
         it != lst1->crend(); ++it)
    {
        cout << *it << endl;
    }

    cout << "=============================" << endl;
    cout << lst1->empty() << endl;
    cout << lst1->size() << endl;
    lst1->clear();
    cout << lst1->size() << endl;

    delete lst1;

    return 0;
}
