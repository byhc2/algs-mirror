#include <iostream>
#include <fstream>
#include "algs_type.h"
#include "algstl_array.h"
#include "algsstring.h"

using namespace std;
using namespace algs;
using namespace algstl;

//暂时不太懂删除重复元素和二分查找有什么关系
//这里做一个普通的删除重复元素的问题来处理

int main(int argc, char *argv[])
{
    ifstream r(argv[1]);
    ifstream t(argv[2]);

    String flag = argv[3];

    Int x;
    Array<Int> arr;
    while (r >> x)
    {
        arr += x;
    }

    cin.clear();

    arr.sort([](const Int a, const Int b) {return a < b;});

    if (arr.size() == 0)
    {
        return 0; //至少有一个元素
    }

    decltype(arr) newarr;
    decltype(arr)::SizeType pos = 0;
    for (decltype(arr)::SizeType i = 0; i < arr.size() - 1; ++i)
    {
        if (arr[i] != arr[i + 1])
        {
            newarr[pos++] = arr[i];
        }
    }

    cout << newarr.toString() << endl;
}
