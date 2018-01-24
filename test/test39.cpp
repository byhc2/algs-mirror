#include <iostream>
#include <list>

using namespace std;

int main(int argc, char *argv[])
{
    list<int> lst2;

    for (auto i = 0; i < 10000; ++i)
    {
        lst2.push_back(i);
    }

    cout << lst2.size() << endl;
    lst2.insert(lst2.begin(), lst2.begin(), lst2.end());
    cout << lst2.size() << endl;
    return 0;
}
