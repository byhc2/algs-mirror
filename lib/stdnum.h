#ifndef __ALGS_NUMBER__
#define __ALGS_NUMBER__

#include "algs_type.h"
#include "stdstring.h"

namespace algs
{

class Num
{
public:
    static Int parseInt(const String &s);
    static Double parseDouble(const String &s);
    static String toString(Int i);
    static String toString(Double i);
};

}

#endif
