#include <iostream>
#include "algstl_deque.h"

using namespace algstl;
using namespace std;

int main(int argc, char *argv[])
{
    Deque<Int> dq;

    dq.pushBack(1);
    dq.pushBack(2);
    dq.pushBack(3);
    dq.pushBack(4);
    dq.pushBack(5);
    dq.pushBack(1);
    dq.pushBack(2);
    dq.pushBack(3);
    dq.pushBack(4);
    dq.pushBack(5);
    dq.pushBack(1);
    dq.pushBack(2);
    dq.pushBack(3);
    dq.pushBack(4);
    dq.pushBack(5);
    dq.pushBack(1);
    dq.pushBack(2);
    dq.pushBack(3);
    dq.pushBack(4);
    dq.pushBack(5);
    dq.pushBack(1);
    dq.pushBack(2);
    dq.pushBack(3);
    dq.pushBack(4);
    dq.pushBack(5);

    for (auto it = dq.begin(); it != dq.end(); ++it)
    {
        cout << *it << endl;
    }

    return 0;
}
