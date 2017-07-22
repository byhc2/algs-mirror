//311361142246

#include <iostream>
#include "algs_type.h"
#include "algsstring.h"
#include "algsnum.h"

using namespace algs;
using namespace std;

String exR1(Int n)
{
    if (n <= 0) return "";
    return exR1(n - 3) + algs::Num::toString(n)
        + exR1(n - 2) + algs::Num::toString(n);
}

int main(int argc, char *argv[])
{
    cout << "311361142246" << endl;
    cout << exR1(6) << endl;
}
