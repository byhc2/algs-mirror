#include <iostream>
#include "algs_type.h"
#include "algsmath.h"
#include "algsout.h"

using namespace std;
using namespace algs;

int main(int argc, char *argv[])
{
    Int N;
    cin >> N;

    //cout << std::bin << N << endl;

    String bin = "";

    if (N == 0)
    {
        bin = "0";
    }
    else
    {
        while (N)
        {
            bin = (N % 2 ? "1" : "0") + bin;
            N >>= 1;
        }
    }

    cout << bin << endl;

    return 0;
}
