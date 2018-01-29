#ifndef __ALGSTL_EXCEPTION__
#define __ALGSTL_EXCEPTION__

#include "algsstring.h"

namespace algstl
{
class AlgstlException
{
    public:
    AlgstlException()
    {}

    virtual ~AlgstlException()
    {}

    AlgstlException(const AlgstlException &e)
    {}

    AlgstlException &operator=(const AlgstlException &e)
    {
        return *this;
    }

    virtual const Char *what() = 0;
};
}

#endif
