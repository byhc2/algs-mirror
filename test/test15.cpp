#include <iostream>
#include "stdstring.h"
#include "stdnum.h"

using namespace algs;
using namespace std;

int main(int argc, char *argv[])
{
    String a("123");

    Int x = Num::parseInt(a);

    cout << x + 1 << endl;

    cout << Num::toString(x + 2) << endl;

    return 0;
}
