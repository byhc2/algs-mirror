#include <iostream>
#include <string>

//习题1.2.7

using namespace std;

string mystery(const string &s)
{
    auto n = s.size();
    if (n <= 1)
    {
        return s;
    }

    auto a = s.substr(0, n / 2);
    auto b = s.substr(n / 2, n);

    return mystery(b) + mystery(a);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << argv[0] << " <str>" << endl;
        return 0;
    }

    string s1 = argv[1];
    cout << mystery(s1) << endl;
    return 0;
}

//2.8 略
