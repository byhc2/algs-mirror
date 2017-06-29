#ifndef __ALGS_OUT__
#define __ALGS_OUT__

#include "algsstring.h"

//重要，以下头文件暂时用来占位，输入输出，先使用c++标准库

namespace algs
{

class AlgsStdOut
{
public:
    static void print(const String &s);
    static void println(const String &s);
    static void println();
#if 0
    template<typename... _Args>
    static void printf(String f, const _Args &... args);
#endif
    static void printf(const String &f, ...);
};

class AlgsOut
{
public:
    template<typename _InputIterator>
    void write(_InputIterator begin, _InputIterator end, const String &name="");
};

}

#endif
