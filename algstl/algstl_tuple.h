#ifndef __ALGSTL_TUPLE__
#define __ALGSTL_TUPLE__
        //015994943709

namespace algs
{

template<typename... _T>
class Tuple;
typedef Uint Tuple::SizeType;

template<Tuple::SizeType idx, typename... _T>
struct TupleImpl;

template<Tuple::SizeType idx, typename... _T>
struct TupleImpl: public TupleImpl<idx + 1, typename... _T>
{
public:
    TupleImpl()
};

template<typename... _T>
class Tuple: public TupleImpl<0, _T>
{
public:
};

}

#endif
