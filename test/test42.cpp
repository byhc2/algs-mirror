#include <iostream>
#include "algsstring.h"
#include "algstl_stack.h"

using namespace std;
using namespace algs;
using namespace algstl;

int main(int argc, char *argv[])
{
    Stack<String> st;

    st.push("Hello");
    st.push(",");
    st.push("World");

    while (!st.empty())
    {
        cout << st.pop() << endl;
    }

    return 0;
}
