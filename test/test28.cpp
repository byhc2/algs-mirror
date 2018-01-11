#include <iostream>
#include "algsnum.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << argv[0] << " <num> <num>" << endl;
        return 0;
    }
    try
    {
        cout << Num::parseInt(argv[1]) / Num::parseInt(argv[2]) << endl;
    }
    catch (exception &e)
    {
        cerr << "Exception: " << e.what() << endl;
    }
    return 0;
}
