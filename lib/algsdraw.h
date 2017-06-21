#ifndef __ALGS_DRAW__
#define __ALGS_DRAW__

#include <cairo-xlib.h>
#include <cairo.h>

namespace algs
{

class AlgsDraw
{
public:
    static void setXscale(double x0, double x1);
    static void setYscale(double y0, double y1);
    static void setPenRadius(double r);
    static void setPenColor(const Color &c);
    //static void setFont(Font f);
    static void setCanvasSize(int w=800, int h=600);
    static void clear(Color &c);
    static void show();
private:
    static bool inited_;
    static int width_;
    static int height_;
    static int margin_h_;
    static int margin_w_;
    static cairo_surface_t *sf_;
    static cairo_surface_t *x11_sf_;
    static cairo_t *cr_;
    static cairo_t *x11_cr_;
};

}

#endif
