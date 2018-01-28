#include <iostream>
#include <string>
#include "algsstring.h"

using namespace algs;
using namespace std;

int main(int argc, char *argv[])
{
    String a;
    cout << a.cStr() << endl;

    String b("Hello world");
    cout << b.cStr() << endl;

    String c(a);
    cout << c.cStr() << endl;

    String d(b);
    cout << d.cStr() << endl;

    String e = "Hello world";
    cout << e.size() << endl;

    cout << "========================" << endl;
    auto x = e + e;
    cout << x.cStr() << endl;
    cout << (e + e).cStr() << endl;
    cout << ("Hello " + e).cStr() << endl;
    cout << ("Hello " + e).size() << endl;
    cout << (e + "Hello ").cStr() << "x" << endl;
    cout << ("Hello " + e + " Hello").cStr() << endl;
    cout << (e + "Hello " + e).cStr() << endl;

    cout << e << endl;

    String aaa = "H222";
    String bbb = aaa;
    aaa += "aaa";
    cout << aaa << endl;
    cout << bbb << endl;
    bbb += "xxx";
    cout << bbb << endl;

    return 0;
}
