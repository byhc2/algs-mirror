#include <iostream>
#include "algstl_deque.h"

using namespace algstl;
using namespace std;

int main(int argc, char *argv[])
{
    Deque<Int> dq;

    for (auto i = 0; i < 10; ++i)
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

    for (auto it = dq.begin(); it != dq.end(); ++it)
    {
        cout << *it << endl;
    }

    cout << "==============================" << endl;

    for (auto it = dq.rbegin(); it != dq.rend(); ++it)
    {
        cout << *it << endl;
    }

    return 0;
}
