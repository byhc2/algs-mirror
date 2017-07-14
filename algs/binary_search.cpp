#include <iostream>
#include <fstream>
#include "algs_type.h"
#include "algstl_array.h"

using namespace std;
//using namespace algs;
using namespace algstl;

//rank与标准库中某个类型重名
Int rank2(Int key, const Array<Int> &a)
{
    Array<Int>::SizeType lo = 0;
    Array<Int>::SizeType hi = a.size() - 1;
    while (lo <= hi)
    {
        auto mid = (lo + hi) / 2;
        if (key < a[mid])
        {
            hi = mid - 1;
        }
        else if (a[mid] < key)
        {
            lo = mid + 1;
        }
        else
        {
            return mid;
        }
    }

    return -1;
}

int main(int argc, char *argv[])
{
    ifstream r(argv[1]);
    ifstream t(argv[2]);
    Int x;
    Array<Int> arr;
    while (r >> x)
    {
        arr += x;
    }

    cin.clear();

    cout << "start sort" << endl;
    arr.sort([](const Int a, const Int b) {return a < b;});
    cout << "finish sort" << endl;

    while (t >> x)
    {
        if (rank2(x, arr) < 0)
        {
            cout << x << endl;
        }
    }
}
