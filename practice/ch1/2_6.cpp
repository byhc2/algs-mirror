#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << argv[0] << " <str1> <str2>" << endl;
        return 0;
    }

    string s1 = argv[1];
    string s2 = argv[2];

    //因String无indexOf
    //此处暂用标准库
    cout << ((s1.size() == s2.size())
        && ((s1 + s1).find(s2) != string::npos)) << endl;

    return 0;
}
