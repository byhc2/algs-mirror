//1.24

//105   24
//24    9
//9     6
//6     3
//3     0
// ==>  3

#include <iostream>
#include "algsnum.h"

using namespace std;
using namespace algs;

Int gcd(Int a, Int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

int main(int argc, char *argv[])
{
    Int a = Num::parseInt(argv[1]);
    Int b = Num::parseInt(argv[2]);

    cout << gcd(a, b) << endl;

    return 0;
}

//1.25
