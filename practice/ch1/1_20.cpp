#include <iostream>
#include "algs_type.h"
#include "algstl_array.h"
#include "algsmath.h"

using namespace algstl;
using namespace algs;
using namespace std;

Double f(Int n)
{
    if (n == 1) return 0;
    return f(n - 1) + AlgsMath::log(n);
}

int main(int argc, char *argv[])
{
    cout << f(10) << endl;
    return 0;
}
