#include <iostream>
#include "stdstats.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    Double table[] = {0.1, 0.2, 0.8, 0.4, 0.5, 0.5};

    cout << StdStats::mean(table) << endl;
    cout << StdStats::var(table) << endl;
    cout << StdStats::stddev(table) << endl;
    cout << StdStats::median(table) << endl;

    return 0;
}
