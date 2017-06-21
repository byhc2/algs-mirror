#ifndef __ALGS_DRAW__
#define __ALGS_DRAW__

#include <cairo-xlib.h>
#include <cairo.h>

//X11/Xlib.h中定义了宏 #define Bool int
#ifdef Bool
#undef Bool
#endif
#include "algs_type.h"
#include "algsstring.h"

namespace algs
{

class AlgsDraw
{
public:
    class Color
    {
    public:
        Color(const Color &c)
        {
            r_ = c.r_;
            g_ = c.g_;
            b_ = c.b_;
            a_ = c.a_;
        }

        Color(): r_(0), g_(0), b_(0), a_(1.0) {}

        double r_;
        double g_;
        double b_;
        double a_;
    };

    static Void setXscale(double x0, double x1);
    static Void setYscale(double y0, double y1);
    static Void setPenRadius(double r);
    static Void setPenColor(const Color &c);
    //static void setFont(Font f);
    static Void setCanvasSize(int w=800, int h=600);
    static Void clear(Color &c);
    static Void show();
    static Void init();
private:
    static Bool inited_;
    static Int width_;
    static Int height_;
    static Int margin_h_;
    static Int margin_w_;
    static cairo_surface_t *sf_;
    static cairo_surface_t *x11_sf_;
    static cairo_t *cr_;
    static cairo_t *x11_cr_;
    static Drawable drawable_;
    static Display *display_;

private:
    static String event2str(Int type);
    static const String err_msg(cairo_status_t s);
};

}

#endif
