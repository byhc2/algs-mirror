#ifndef __ALGS_STDSTRING__
#define __ALGS_STDSTRING__

namespace algs
{

class String
{
public:
    String();
    String(const String &s);
    String(String &&s);
    String(const Char *s);
    String(const Char *s, Uint n);

    String &operator=(const String &s);
private:
    Char *buf;
};

String operator+(const Char *lhs, const String &rhs);
String operator+(const String &lhs, const Char *rhs);

}

#endif
