#include <iostream>
#include "algstl_deque.h"

using namespace algstl;
using namespace std;

int main(int argc, char *argv[])
{
    Deque<Int> dq;

    for (auto i = 0; i < 100; ++i)
    {
        if (i % 2)
        {
            dq.pushBack(i);
        }
        else
        {
            dq.pushFront(i);
        }
    }

    cout << dq.size() << endl;

    for (auto r : dq)
    {
        cout << r << "  ";
    }
    cout << endl;

    dq.erase(dq.begin());
    cout << dq.size() << endl;

    dq.erase(dq.begin(), dq.end());
    cout << dq.size() << endl;

    for (auto it = dq.begin(); it != dq.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;

    return 0;
}
