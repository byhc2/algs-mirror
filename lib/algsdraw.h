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

        Color(Double r, Double g, Double b):
            r_(r), g_(g), b_(b), a_(1.0) {}

        double r_;
        double g_;
        double b_;
        double a_;
    };

    static Void line(Double x0, Double y0, Double x1, Double y1);
    static Void point(Double x, Double y);
    static Void text(Double x, Double y, const String &s);
    static Void circle(Double x, Double y, Double r);
    static Void filledCircle(Double x, Double y, Double r);

    static Void setXscale(Double x0, Double x1);
    static Void setYscale(Double y0, Double y1);
    static Void setPenRadius(Double r);
    static Void setPenColor(const Color &c);
    static Void setFont(const String &f);
    static Void setCanvasSize(Int w=800, Int h=600);
    static Void clear(const Color &c=Color(1.0, 1.0, 1.0));
    static Void show();
    static Void init();
private:
    static Void drawInit();
    static Void drawFinish();

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
    static Double max_x_; //x轴左端点
    static Double min_x_; //x轴右端点
    static Double max_y_; //y轴上端点
    static Double min_y_; //y轴下端点
    static Double pen_radius_;
    static Color pen_color_;
    static String font_;

private:
    static String event2str(Int type);
    static const String err_msg(cairo_status_t s);
    static Double c2sX(Double x);
    static Double c2sY(Double y);
    static Double l2s(Double l);
};

}

#endif
