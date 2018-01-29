#include <iostream>
#include "algstl_stack.h"

//习题1.3.9

using namespace std;
using namespace algs;
using namespace algstl;

int main(int argc, char *argv[])
{
    Stack<String> opst;
    Stack<String> numst;

    String s;
    while (cin >> s)
    {
        if (s == "+" || s == "-" || s == "*" || s == "/")
        {
            opst.push(s);
        }
        else if (s == ")")
        {
            //假设均为双目运算符
            auto op   = opst.pop();
            auto num2 = numst.pop();
            auto num1 = numst.pop();

            numst.push("( " + num1 + " " + op + " " + num2 + " " + s);
        }
        else
        {
            numst.push(s);
        }
    }

    if (numst.size() != 1 || !opst.empty())
    {
        cout << "illformed expression" << endl;
    }
    else
    {
        cout << numst.top() << endl;
    }

    return 0;
}
