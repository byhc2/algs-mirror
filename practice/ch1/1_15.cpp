#include <iostream>
#include "algs_type.h"
#include "algstl_array.h"

using namespace std;

Array<Int> histgram(const Array<Int> &a)
{
    Array<Int> hist;
    for (auto r: a)
    {
        hist[r] += 1;
    }
}

int main(int argc, char *argv[])
{
}
