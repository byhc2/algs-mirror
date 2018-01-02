//1.24

//105   24
//24    9
//9     6
//6     3
//3     0
// ==>  3

#include <iostream>
#include "algsnum.h"

using namespace std;
using namespace algs;

Int gcd(Int a, Int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

int main(int argc, char *argv[])
{
    Int a = Num::parseInt(argv[1]);
    Int b = Num::parseInt(argv[2]);

    cout << gcd(a, b) << endl;

    return 0;
}

//1.25
//引理1：若a|b，b = qa
//引理2：若a|b且a|c，则a|(xb + yc)
//证明：若k=gcd(m, n)，则k=gcd(n, m % n)
//
//因为k = gcd(m, n)，所以k|m且k|n
//所以k|(m + n)
//假设 m = qn + r，r = m % n
//则k|((q + 1)n + r)
//因此，k|r（这是显然的:)），因此有k=gcd(n, m % n)
//
//关于这个证明，还可以使用集合的概念，
//令S是m, n的公约数集合，令S'是n和m % n的公约数集合
//可以证明，S中任意元素都是S'中的元素
//同时S'中任意元素也都是S中的元素，即S=S'
//因此，从S中选取最大的那个公约数，就是最大公约数
//
//以上只能证明 gcd(m, n) = gcd(n, m % n)
//下面需要证明，按照这个算法，最后得出的结果是最大公约数
//由上面的证明，假设按照算法有k = gcd(m, n)
//则，该算法的最后一步，应该是k = gcd(k, 0)，这是由该算法的定义和前面的证明得到的
//此时，若存在另一个数j > k，使得j = gcd(m, n)，算法最后一步会有j = gcd(k, 0)
//即j|k，而根据假设，j > k，这是矛盾的，所以，k就是最大公约数
//
//一点想法，其实证明gcd算法得到的公约数是最大公约数是没必要的
//因为首先证明了gcd(m, n) = gcd(n, m % n)
//其次，该算法一定会收敛到某个值，使得gcd(m, n) = gcd(n, m % n) = ... = gcd(k, 0)
//对于gcd(k, 0)，k天然的就是最大公约数，因此，k也一定是gcd(m, n)的最大公约数


//1.26
//该算法可以简化成：
//if (a > b) swap(a, b)
//if (a > c) swap(a, c)
//if (b > c) swap(b, c)
//第一步过后，可以保证a < b
//第二步过后，可以保证a < c
//第三步过后，可以保证b < c
//综上，可以有a < b < c，即升序
