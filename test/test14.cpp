#include <iostream>
#include "stdstring.h"

using namespace algs;
using namespace std;

int main(int argc, char *argv[])
{
    String a;
    String b("Hello world");
    String c(a);
    String d(b);
    String e = "Hello world";

    cout << a.c_str() << endl;
    cout << b.c_str() << endl;
    cout << c.c_str() << endl;
    cout << d.c_str() << endl;
    cout << e.c_str() << endl;

    return 0;
}
