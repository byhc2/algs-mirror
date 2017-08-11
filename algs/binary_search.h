#include <iostream>
#include <fstream>
#include "algs_type.h"
#include "algstl_array.h"

namespace algs
{

class BinarySearch
{
public:
    template<typename _T>
    static typename algstl::Array<_T>::SizeType rank(const _T &key, const algstl::Array<_T> &a)
    {
        if (a.size() == 0)
        {
            return -1; //坚决防止数组大小为0的情况
        }
        typename algstl::Array<_T>::SizeType lo = 0;
        typename algstl::Array<_T>::SizeType hi = a.size() - 1;
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

        return algstl::Array<_T>::npos;
    }

    //返回有序数组中，比key小的元素的个数
    template<typename _T>
    static typename algstl::Array<_T>::SizeType countLess(const _T &key, const algstl::Array<_T> &a)
    {
        if (a.size() == 0)
        {
            return 0;
        }
        auto lo = a.begin();
        auto hi = a.end();
        while (lo != hi)
        {
            auto mid = lo + (hi - lo) / 2;
            if (*mid == key)
            {
                if (mid != lo && *(mid - 1) < key)
                {
                    return mid - a.begin();
                }
                hi = mid;
            }
            else if (*mid < key)
            {
                if ((mid + 1 != hi) && *(mid + 1) >= key)
                {
                    return mid + 1 - a.begin();
                }
                lo = mid + 1;
            }
            else //*mid > key
            {
                if (mid != lo && *(mid - 1) <= key)
                {
                    return mid - a.begin();
                }
                hi = mid;
            }
        }


        //尾部处理，此时a中所有元素均大于等于key或均小于等于key
        if (*a.begin() >= key)
        {
            return 0;
        }
        
        if (*a.rbegin() <= key)
        {
            return a.size();
        }
    }
};

}
