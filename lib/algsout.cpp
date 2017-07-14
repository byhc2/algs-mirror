#include <iostream>
#include <cstdarg>
#include "algsout.h"

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

void AlgsStdOut::println(const Char c)
{
    std::cout << c << std::endl;
}

void AlgsStdOut::println()
{
    std::cout << std::endl;
}

#if 0
template<typename... _Args>
void AlgsStdOut::printf(String f, const _Args &... args)
{
    return; //TODO 未实现
}
#endif

//先暂时这样实现
void AlgsStdOut::printf(const String &f, ...)
{
    va_list args;
    va_start(args, f);
    vprintf(f.c_str(), args);
    va_end(args);
}

template<typename _InputIterator>
void AlgsOut::write(_InputIterator begin, _InputIterator end, const String &name)
{
    return; //TODO 未实现
}

}
