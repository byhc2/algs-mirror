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
    for (decltype(arr)::SizeType i = 0; i < arr.size() - 1; ++i)
    {
        if (arr[i] != arr[i + 1])
        {
            newarr += arr[i];
        }
    }
    //特殊处理最后一个元素
    if (arr[arr.size() - 1] != newarr[newarr.size() - 1])
    {
        newarr += arr[arr.size() - 1];
    }

    cout << newarr.toString() << endl;
}
