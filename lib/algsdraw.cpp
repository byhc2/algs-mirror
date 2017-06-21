#include "algsdraw.h"

namespace algs
{

static bool AlgsDraw::inited = false;

void AlgsDraw::init()
{
    if (AlgsDraw::inited)
    {
        return;
    }

    margin_h_ = 10;
    margin_w_ = 10;
    width_ = 800;
    height_ = 600;

    sf_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, m_width, m_height);
    cr_ = cairo_create(sf_);

    cairo_scale (cr_, width_, height_);
    cairo_set_source_rgb(cr_, 1.0, 0.0, 0.0);
    cairo_rectangle(cr_, 0.0, 0.0, 1.0, 1.0);
    cairo_fill(cr_);
    cairo_save(cr_);

    inited = true;
}

}
