#include <iostream>
#include <iomanip>
#include "stdrandom.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    cout << setprecision(20) << StdRandom::uniform(10.0, 19.7) << endl;

    return 0;
}
