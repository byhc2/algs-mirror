#include <iostream>
#include "algs_type.h"
#include "algstl_array.h"

using namespace std;
using namespace algstl;

int main(int argc, char *argv[])
{
    Array<Array<Int>> a(
    {
        {6, 1, 8},
        {7, 5, 3},
        {2, 9, 4},
    });

    for (decltype(a.size()) i = 0; i < a.size(); ++i)
    {
        for (decltype(a.size()) j = 0; j < a[i].size(); ++j)
        {
            cout << a[j][i] << "  ";
        }
        cout << endl;
    }

    return 0;
}
