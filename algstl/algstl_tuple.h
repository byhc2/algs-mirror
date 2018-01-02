#ifndef __ALGSTL_TUPLE__
#define __ALGSTL_TUPLE__

namespace algstl
{

//因为不懂元编程，这里只能写一个简陋版本的元组实现
//只支持二元组
template<typename _T, typename _U>
class Tuple
{
public:
    typedef Uint SizeType;

    Tuple(const _T &t, const _U &u): t_(t), u_(u) {}
    Tuple(): t_(_T()), u_(_U()) {}

private:
    _T t_;
    _U u_;
};

}

#endif
