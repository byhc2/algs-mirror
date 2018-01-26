#include "algstl_deque.h"
#include <iostream>

using namespace std;
using namespace algs;
using namespace algstl;

int main(int argc, char *argv[])
{
    Deque<Int> dq1, dq2;

    for (auto i = 0; i < 800; ++i)
    {
        dq1.pushBack(i);
        dq2.pushFront(i);
    }

    cout << dq1.size() <<endl;
    cout << dq2.size() <<endl;

    dq2.insert(dq1.begin(), dq1.end(), dq2.begin());
    cout << dq2.size() <<endl;

    return 0;
}
