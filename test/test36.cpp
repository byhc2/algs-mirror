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

    dq.insert(dq.begin(), dq.end(), dq.begin());

    return 0;
}
