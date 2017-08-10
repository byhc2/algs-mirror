#include <iostream>
#include <fstream>
#include "algs_type.h"
#include "algstl_array.h"

namespace algs
{

class BinarySearch
{
    template<typename _T>
    static algstl::Array<_T>::SizeType rank(const _T &key, const algstl::Array<_T> &a)
    {
        if (a.size() == 0)
        {
            return -1; //坚决防止数组大小为0的情况
        }
        Array<_T>::SizeType lo = 0;
        Array<_T>::SizeType hi = a.size() - 1;
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

        return Array<_T>::npos;
    }

    //返回有序数组中，比key小的元素的个数
    template<typename _T>
    static algstl::Array<_T>::SizeType countLess(const _T &key, const algstl::Array<_T> &a)
    {
        if (a.size() == 0)
        {
            return 0;
        }

        Array<_T>::SizeType lo = 0;
        Array<_T>::SizeType hi = a.size() - 1;
    }
};

}
