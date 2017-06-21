#include <iostream>
#include "algsrandom.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    AlgsRandom::initialize();
    cout << AlgsRandom::uniform(1000) << endl;

    return 0;
}
