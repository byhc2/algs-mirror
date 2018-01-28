#ifndef __ALGSTL_EXCEPTION__
#define __ALGSTL_EXCEPTION__

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
    {}

    virtual const Char *what()
    {}
};
}

#endif
