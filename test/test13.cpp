#include <iostream>
#include "algsstats.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    Double table[] = {0.1, 0.2, 0.8, 0.4, 0.5, 0.5};

    cout << AlgsStats::mean(table) << endl;
    cout << AlgsStats::var(table) << endl;
    cout << AlgsStats::stddev(table) << endl;
    cout << AlgsStats::median(table) << endl;

    return 0;
}
