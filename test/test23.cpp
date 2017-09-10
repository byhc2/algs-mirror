#include <iostream>
#include "counter.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    Counter c("hahaha");

    cout << c << endl;
    ++c;
    c++;
    cout << c.toString() << endl;

    return 0;
}
