#include <iostream>
#include "algs_type.h"
#include "algsstring.h"
#include "algsout.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    String name;
    Int num1, num2;

    while (cin >> name >> num1 >> num2)
    {
        AlgsStdOut::printf("%-10s\t%5d\t%5d\t%.3f\n",
                name.cStr(), num1, num2,
                static_cast<Double>(num1) / num2);
    }

    return 0;
}
