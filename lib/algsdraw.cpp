#include <stdexcept>
#include "algsdraw.h"

namespace algs
{

Bool AlgsDraw::inited_ = false;

void AlgsDraw::init()
{
    if (AlgsDraw::inited_)
    {
        return;
    }

    margin_h_ = 10;
    margin_w_ = 10;
    width_ = 800;
    height_ = 600;

    sf_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width_, height_);
    cr_ = cairo_create(sf_);

    cairo_scale(cr_, width_, height_);
    cairo_set_source_rgb(cr_, 1.0, 0.0, 0.0);
    cairo_rectangle(cr_, 0.0, 0.0, 1.0, 1.0);
    cairo_fill(cr_);
    cairo_save(cr_);

    inited_ = true;
}

void AlgsDraw::show()
{
    String str_disp = getenv("DISPLAY");
    if (str_disp.size() == 0)
    {
        display_ = XOpenDisplay(NULL);
    }
    else
    {
        display_ = XOpenDisplay(str_disp.c_str());
    }

    if (display_ == NULL)
    {
        throw std::runtime_error(("Cannot open DISPLAY " + str_disp + ".").c_str());
        return;
    }

    drawable_ = XCreateSimpleWindow(display_, RootWindow(display_, DefaultScreen(display_)), 0, 0,
            width_, height_, 0, BlackPixel(display_, DefaultScreen(display_)), WhitePixel(display_, DefaultScreen(display_)));

    XSelectInput(display_, drawable_, ExposureMask);
    XMapWindow(display_, drawable_);
    XFlush(display_);
    XSync(display_, True);
    Atom wmDeleteMessage = XInternAtom(display_, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display_, drawable_, &wmDeleteMessage, 1);
    XEvent evt;
    bool running = true;
    int height;
    int width;
    //进入事件循环
    while (running)
    {
        XNextEvent(display_, &evt);
        printf("Get %s\n", event2str(evt.type).c_str());
        switch (evt.type)
        {
        case Expose:
            //获取当前窗口的宽和高
            width = evt.xexpose.width;
            height = evt.xexpose.height;
            printf("Real width: %d, height: %d\n", width, height);

            x11_sf_ = cairo_xlib_surface_create(display_, drawable_, DefaultVisual(display_, DefaultScreen(display_)), width, height);
            x11_cr_ = cairo_create(x11_sf_);
            cairo_scale(x11_cr_, double(width) / width_, double(height) / height_);
            cairo_set_source_surface(x11_cr_, sf_, 0, 0);
            cairo_paint(x11_cr_);
            cairo_surface_destroy(x11_sf_);
            cairo_destroy(x11_cr_);
            break;
        case ClientMessage:
            if (evt.xclient.data.l[0] == wmDeleteMessage)
            {
                running = false;
            }
            break;
        }
    }
}

String AlgsDraw::event2str(Int type)
{
#define IF_RETURN(arg) if (type == arg) return #arg
    IF_RETURN(KeyPress);
    IF_RETURN(KeyRelease);
    IF_RETURN(ButtonPress);
    IF_RETURN(ButtonRelease);
    IF_RETURN(MotionNotify);
    IF_RETURN(EnterNotify);
    IF_RETURN(LeaveNotify);
    IF_RETURN(FocusIn);
    IF_RETURN(FocusOut);
    IF_RETURN(KeymapNotify);
    IF_RETURN(Expose);
    IF_RETURN(GraphicsExpose);
    IF_RETURN(NoExpose);
    IF_RETURN(VisibilityNotify);
    IF_RETURN(CreateNotify);
    IF_RETURN(DestroyNotify);
    IF_RETURN(UnmapNotify);
    IF_RETURN(MapNotify);
    IF_RETURN(MapRequest);
    IF_RETURN(ReparentNotify);
    IF_RETURN(ConfigureNotify);
    IF_RETURN(ConfigureRequest);
    IF_RETURN(GravityNotify);
    IF_RETURN(ResizeRequest);
    IF_RETURN(CirculateNotify);
    IF_RETURN(CirculateRequest);
    IF_RETURN(PropertyNotify);
    IF_RETURN(SelectionClear);
    IF_RETURN(SelectionRequest);
    IF_RETURN(SelectionNotify);
    IF_RETURN(ColormapNotify);
    IF_RETURN(ClientMessage);
    IF_RETURN(MappingNotify);
    IF_RETURN(GenericEvent);
#undef IF_RETURN
}

const String AlgsDraw::err_msg(cairo_status_t s)
{
    assert(s < CAIRO_STATUS_LAST_STATUS);
#define ERR_MSG(arg) if (s == arg) return #arg
    ERR_MSG(CAIRO_STATUS_SUCCESS);
    ERR_MSG(CAIRO_STATUS_NO_MEMORY);
    ERR_MSG(CAIRO_STATUS_INVALID_RESTORE);
    ERR_MSG(CAIRO_STATUS_INVALID_POP_GROUP);
    ERR_MSG(CAIRO_STATUS_NO_CURRENT_POINT);
    ERR_MSG(CAIRO_STATUS_INVALID_MATRIX);
    ERR_MSG(CAIRO_STATUS_INVALID_STATUS);
    ERR_MSG(CAIRO_STATUS_NULL_POINTER);
    ERR_MSG(CAIRO_STATUS_INVALID_STRING);
    ERR_MSG(CAIRO_STATUS_INVALID_PATH_DATA);
    ERR_MSG(CAIRO_STATUS_READ_ERROR);
    ERR_MSG(CAIRO_STATUS_WRITE_ERROR);
    ERR_MSG(CAIRO_STATUS_SURFACE_FINISHED);
    ERR_MSG(CAIRO_STATUS_SURFACE_TYPE_MISMATCH);
    ERR_MSG(CAIRO_STATUS_PATTERN_TYPE_MISMATCH);
    ERR_MSG(CAIRO_STATUS_INVALID_CONTENT);
    ERR_MSG(CAIRO_STATUS_INVALID_FORMAT);
    ERR_MSG(CAIRO_STATUS_INVALID_VISUAL);
    ERR_MSG(CAIRO_STATUS_FILE_NOT_FOUND);
    ERR_MSG(CAIRO_STATUS_INVALID_DASH);
    ERR_MSG(CAIRO_STATUS_INVALID_DSC_COMMENT);
    ERR_MSG(CAIRO_STATUS_INVALID_INDEX);
    ERR_MSG(CAIRO_STATUS_CLIP_NOT_REPRESENTABLE);
    ERR_MSG(CAIRO_STATUS_TEMP_FILE_ERROR);
    ERR_MSG(CAIRO_STATUS_INVALID_STRIDE);
    ERR_MSG(CAIRO_STATUS_FONT_TYPE_MISMATCH);
    ERR_MSG(CAIRO_STATUS_USER_FONT_IMMUTABLE);
    ERR_MSG(CAIRO_STATUS_USER_FONT_ERROR);
    ERR_MSG(CAIRO_STATUS_NEGATIVE_COUNT);
    ERR_MSG(CAIRO_STATUS_INVALID_CLUSTERS);
    ERR_MSG(CAIRO_STATUS_INVALID_SLANT);
    ERR_MSG(CAIRO_STATUS_INVALID_WEIGHT);
    ERR_MSG(CAIRO_STATUS_INVALID_SIZE);
    ERR_MSG(CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED);
    ERR_MSG(CAIRO_STATUS_DEVICE_TYPE_MISMATCH);
    ERR_MSG(CAIRO_STATUS_DEVICE_ERROR);
    ERR_MSG(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
    ERR_MSG(CAIRO_STATUS_DEVICE_FINISHED);
    ERR_MSG(CAIRO_STATUS_JBIG2_GLOBAL_MISSING);
#undef ERR_MSG
}

}
