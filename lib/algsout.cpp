#include "algsout.h"
#include <iostream>

namespace algs
{

void AlgsStdOut::print(const String &s)
{
    std::cout << s;
}

void AlgsStdOut::println(const String &s)
{
    std::cout << s << std::endl;
}

void AlgsStdOut::println()
{
    std::cout << std::endl;
}

template<typename... _Args>
void AlgsStdOut::printf(String f, const _Args &... args)
{
    return; //TODO 未实现
}

template<typename _InputIterator>
void AlgsOut::write(_InputIterator begin, _InputIterator end, const String &name)
{
    return; //TODO 未实现
}

}
