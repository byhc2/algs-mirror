#include <iostream>
#include "gcd.h"
#include "algstl_array.h"

using namespace std;
using namespace algs;
using namespace algstl;

#define N 10

int main(int argc, char *argv[])
{
    Array<Array<Bool>> a(Array<Bool>(false, N), N);

    for (auto i = 2; i < N; ++i)
    {
        for (auto j = 2; j < N; ++j)
        {
            if (i == j)
            {
                continue;
            }
            else if (gcd(i, j) == 1)
            {
                a[i][j] = true;
            }
            else
            {
                a[i][j] = false;
            }
        }
    }

    cout << a.toString() << endl;

    return 0;
}
