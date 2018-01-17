#include <iostream>
#include <random>

using namespace std;
int main(int argc, char *argv[])
{

#define SIZEOF(arg) cout << "sizeof("#arg"): " << sizeof(arg) << endl
    SIZEOF(int);
    SIZEOF(long);
    SIZEOF(char);
    SIZEOF(bool);
    SIZEOF(double);
    SIZEOF(float);
    SIZEOF(size_t);

    random_device rd;
    decltype(rd()) x;
    SIZEOF(x);

#undef SIZEOF

    return 0;
}
