#include <iostream>
#include "algstl_stack.h"

//习题1.3.10

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
        if (s == "+" || s == "-" || s == "*" || s == "/" || s == "sqrt")
        {
            opst.push(s);
        }
        else if (s == "(")
        {
            continue;
        }
        else if (s == ")")
        {
            auto op = opst.pop();
            if (op == "sqrt")
            {
                auto num0 = numst.pop();
                numst.push(num0 + " " + op);
            }
            else
            {
                auto num2 = numst.pop();
                auto num1 = numst.pop();
                numst.push(num1 + " " + num2 + " " + op);
            }
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
