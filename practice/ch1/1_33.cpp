#include <iostream>
#include <initializer_list>
#include "algs_type.h"
#include "algstl_array.h"

using namespace std;
using namespace algstl;

class Matrix
{
public:
    static Double dot(const Array<Double> &x, const Array<Double> &y)
    {
        Double prod = 0.0;
        assert(x.size() == y.size());

        for (auto i = 0; i < x.size(); ++i)
        {
            prod += x[i] * y[i];
        }

        return prod;
    }

    static Array<Array<Double>> mult(const Array<Array<Double>> &a,
            const Array<Array<Double>> &b)
    {
        assert(a.size() > 0 && b.size() > 0);
        assert(a[0].size() == b.size());

        Array<Array<Double>> prod(Array<Double>(0, b[0].size()), a.size());

        cout << prod.size() << endl;
        cout << prod[0].size() << endl;

        for (auto i = 0; i < a.size(); ++i)
        {
            for (auto j = 0; j < a[i].size(); ++j)
            {
                for (auto k = 0; k < b[0].size(); ++k)
                {
                    prod[i][k] += a[i][j] * b[j][k];
                }
            }
        }

        return prod;
    }

    static Array<Array<Double>> transpose(const Array<Array<Double>> &a)
    {
        Array<Array<Double>> result(Array<Double>(0, a.size()), a[0].size());

        for (auto i = 0; i < a.size(); ++i)
        {
            for (auto j = 0; j < a[i].size(); ++j)
            {
                result[j][i] = a[i][j];
            }
        }

        return result;
    }

    static Array<Double> mult(const Array<Array<Double>> &a,
            const Array<Double> &b)
    {
        assert(a.size() > 0 && a[0].size() == b.size());
        Array<Double> prod(0, a.size());

        for (auto i = 0; i < a.size(); ++i)
        {
            for (auto j = 0; j < a[i].size(); ++j)
            {
                prod[i] += a[i][j] * b[j];
            }
        }
        return  prod;
    }

    static Array<Double> mult(const Array<Double> &a,
            const Array<Array<Double>> &b)
    {
        assert(a.size() > 0 && b.size() == a.size());
        Array<Double> prod(0, b[0].size());

        for (auto i = 0; i < a.size(); ++i)
        {
            for (auto j = 0; j < b[i].size(); ++j)
            {
                prod[j] += a[i] * b[i][j];
            }
        }
        return  prod;
    }
};

int main(int argc, char *argv[])
{
    Array<Double> x = {1, 2, 3};
    Array<Array<Double>> y = {{1, 2, 3}, {4, 5, 6}};
    Array<Array<Double>> z = {{1, 2}, {2, 3}, {3, 4}};

    cout << Matrix::dot(x, x) << endl;
    cout << Matrix::mult(y, z).toString() << endl;
    cout << Matrix::transpose(y).toString() << endl;
    cout << Matrix::mult(y, {1, 2, 3}).toString() << endl;
    cout << Matrix::mult({1, 2, 3}, z).toString() << endl;

    return 0;
}

//1.34
//不需要保存，只使用三个变量
//需要保存
//不需要保存，只需要使用一个大小为k的数组
//不需要保存，只使用两个变量
//不需要保存，只使用两个变量
//需要保存
//需要保存
//需要保存
