#include <iostream>
#include "algsrandom.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    AlgsRandom::initialize();

    Double table[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6};

    AlgsRandom::shuffle(table);

    for (auto r: table)
    {
        cout << r << "\t";
    }
    cout << endl;

    return 0;
}
