#include <iostream>
#include "algstl_stack.h"
#include "algsstring.h"

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
        st.push(x);
    }
}
