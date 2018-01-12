#include <iostream>
#include "algs_type.h"

namespace algs
{
class Accumulator
{
    friend std::ostream &operator<<(std::ostream &os, const Accumulator &rhs);

    public:
    Accumulator();
    Accumulator(const Accumulator &a);
    Accumulator &operator=(const Accumulator &rhs);
    Accumulator &operator+=(Double a);
    Double mean() const;
    Double var() const;

    private:
    Double v_;  //总和
    Double m_;  //均值
    Double s_;  //标准方差
    Uint c_;    //样本容量
};
}
