#include <iostream>
#include "algsmath.h"
#include "algsnum.h"
#include "algstl_stack.h"

//习题1.3.11

using namespace std;
using namespace algs;
using namespace algstl;

int main(int argc, char *argv[])
{
    Stack<Double> st;

    String s;
    while (cin >> s)
    {
        if (s == "+" || s == "-" || s == "*" || s == "/")
        {
            auto num2 = st.pop();
            auto num1 = st.pop();

            Double res;
            if (s == "+")
            {
                res = num1 + num2;
            }
            else if (s == "-")
            {
                res = num1 - num2;
            }
            else if (s == "*")
            {
                res = num1 * num2;
            }
            else if (s == "/")
            {
                res = num1 / num2;
            }

            st.push(res);
        }
        else if (s == "sqrt")
        {
            auto num = st.pop();
            st.push(AlgsMath::sqrt(num));
        }
        else
        {
            st.push(Num::parseDouble(s));
        }
    }

    if (st.size() != 1)
    {
        cout << "illformed expression" << endl;
    }
    else
    {
        cout << st.top() << endl;
    }
    return 0;
}

//习题1.3.12 algstl::Stack实现
//
//习题1.3.13
// b 2先出栈，则1必于0前出
//
//习题1.3.14 略
//
//习题1.3.15 略
//
//习题1.3.16 略
//
//习题1.3.17 略
