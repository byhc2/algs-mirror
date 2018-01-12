#include <iostream>
#include "accumulator.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    Int x;
    Accumulator acc;

    while (cin >> x)
    {
        acc += x;
    }
    cout << "mean: " << acc.mean() << endl;
    cout << "var:  " << acc.var() << endl;
    return 0;
}
