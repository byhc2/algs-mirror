#include <iostream>
#include "algsstring.h"
#include "algstl_stack.h"

//习题1.3.1 略
//习题1.3.2

using namespace std;
using namespace algs;
using namespace algstl;

int main(int argc, char *argv[])
{
    Stack<String> st;

    String x;
    while (cin >> x)
    {
        if (x == "-")
        {
            cout << st.pop() << " ";
        }
        else
        {
            st.push(x);
        }
    }

    cout << "(" << st.size() << " left on stack)" << endl;
    return 0;
}

//习题1.3.3
//今有一序列按序入栈，则其出栈规则如何？
//答曰，若某元素先出栈，则于此元素之前入栈者，必倒序出栈
//b 2先出栈，则1必于0前出
//f 3先出栈，则2必于1前出
//g 3先出栈，则2必于0前出
