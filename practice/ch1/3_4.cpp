#include <iostream>
#include "algstl_stack.h"

//习题1.3.4

using namespace std;
using namespace algs;
using namespace algstl;

int main(int argc, char *argv[])
{
    Stack<Char> st;
    Bool valid = true;
    Char c;
    while (cin >> c && valid)
    {
        if (isspace(c))
        {
            continue;
        }
        cout << c << endl;

        switch (c)
        {
        case '[':
        case '{':
        case '(':
            st.push(c);
            break;
        default:
            if ((c == ']' && st.top() == '[') || (c == '}' && st.top() == '{')
                || (c == ')' && st.top() == '('))
            {
                st.pop();
            }
            else
            {
                valid = false;
            }
            break;
        }
    }

    if (st.empty())
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }
    return 0;
}

//习题1.3.5 略
//
//习题1.3.6
//将队列倒序
//
//习题1.3.7
// Stack中top方法
//
//习题1.3.8 略
