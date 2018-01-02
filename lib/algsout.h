#ifndef __ALGS_OUT__
#define __ALGS_OUT__

#include "algsstring.h"

//重要，以下头文件暂时用来占位，输入输出，先使用c++标准库

namespace algs
{

class AlgsStdOut
{
public:
    static Void print(const String &s);
    static Void println(const String &s);
    static Void println(const Char c);
    static Void println();
#if 0
    template<typename... _Args>
    static void printf(String f, const _Args &... args);
#endif
    static Void printf(const String &f, ...);
};

class AlgsOut
{
public:
    template<typename _InputIterator>
    Void write(_InputIterator begin, _InputIterator end, const String &name="");
};

}

#endif
