#include <iostream>
#include "algs_type.h"
#include "algsstring.h"
#include "algsnum.h"

using namespace algs;
using namespace std;

Int mystery1(Int a, Int b)
{
    if (b == 0) return 0;
    if (b % 2 == 0) return mystery1(a + a, b / 2);
    return mystery1(a + a, b / 2) + a;
}

Int mystery2(Int a, Int b)
{
    if (b == 0) return 1;
    if (b % 2 == 0) return mystery2(a * a, b / 2);
    return mystery2(a * a, b / 2) * a;
}

int main(int argc, char *argv[])
{
    cout << mystery1(2, 25) << endl; //50
    cout << mystery1(3, 11) << endl; //33

    //给定正整数a，b，mystery1(a, b) = a * b;
    //给定正整数a，b，mystery2(a, b) = a ^ b;

    cout << mystery2(2, 25) << endl; //50
    cout << mystery2(3, 11) << endl; //33

    return 0;
}
