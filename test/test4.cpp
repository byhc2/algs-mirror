#include <iostream>
#include <iomanip>
#include "algsrandom.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    cout << setprecision(20) << AlgsRandom::uniform(10.0, 19.7) << endl;

    return 0;
}
