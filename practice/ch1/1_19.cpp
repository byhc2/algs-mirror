#include <iostream>
#include "algs_type.h"
#include "algstl_array.h"

using namespace algstl;
using namespace std;

Long f1(Int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    return f1(n - 1) + f1(n - 2);
}

Ulong f2(Int n)
{
    static Array<Ulong> preresult(0, 100); //预分配100个空间
    preresult[0] = 0;
    preresult[1] = 1;

    if (n == 0) return 0;
    if (n == 1) return 1;
    if (preresult[n] == 0)
    {
        auto v1 = f2(n - 2);
        auto v2 = f2(n - 1);
        preresult[n] = v1 + v2;
    }

    return preresult[n];
}

int main(int argc, char *argv[])
{
    auto start_time = time(NULL);
    for (auto n = 0; n < 100; ++n)
    {
        cout << f2(n) << endl;
        //每次运行完，打出耗时
        cout << "after calc " << n << " consume " << time(NULL) - start_time << endl;
    }

    return 0;
}
