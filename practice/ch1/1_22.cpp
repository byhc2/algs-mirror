#include <iostream>
#include <fstream>
#include "algs_type.h"
#include "algsstring.h"
#include "algstl_array.h"

using namespace std;
using namespace algs;
using namespace algstl;

//rank与标准库中某个类型重名
Int rank2(Int key, const Array<Int> &a, Array<Int>::SizeType lo, Array<Int>::SizeType hi, Int rdepth)
{
    auto mid = (lo + hi) / 2;

    //根据递归深度，打印lo和hi
    cout << String(rdepth, '\t') << lo << "\t" << hi << endl;

    if (lo == hi)
    {
        return -1;
    }
    else if (a[mid] == key)
    {
        return mid;
    }
    else if (a[mid] < key)
    {
        return rank2(key, a, mid + 1, hi, rdepth + 1);
    }
    else
    {
        return rank2(key, a, lo, mid, rdepth + 1);
    }
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

    //cout << arr.toString() << endl;

    while (t >> x)
    {
        if (rank2(x, arr, 0, arr.size(), 0) < 0)
        {
            cout << x << endl;
        }
    }
}
