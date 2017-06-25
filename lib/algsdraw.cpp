#include <stdexcept>
#include <iostream>
#include "algsdraw.h"

namespace algs
{

Bool AlgsDraw::inited_ = false;
Int AlgsDraw::width_;
Int AlgsDraw::height_;
Int AlgsDraw::margin_h_;
Int AlgsDraw::margin_w_;
cairo_surface_t *AlgsDraw::sf_;
cairo_surface_t *AlgsDraw::x11_sf_;
cairo_t *AlgsDraw::cr_;
cairo_t *AlgsDraw::x11_cr_;
Drawable AlgsDraw::drawable_;
Display *AlgsDraw::display_;
Double AlgsDraw::max_x_; //x轴左端点
Double AlgsDraw::min_x_; //x轴右端点
Double AlgsDraw::max_y_; //y轴上端点
Double AlgsDraw::min_y_; //y轴下端点
Double AlgsDraw::pen_radius_;
AlgsDraw::Color AlgsDraw::pen_color_;
String AlgsDraw::font_;

Void AlgsDraw::init()
{
    if (AlgsDraw::inited_)
    {
        return;
    }

    margin_h_ = 10;
    margin_w_ = 10;
    width_ = 800;
    height_ = 600;

    //设置坐标范围
    min_x_ = -10;
    max_x_ = 10;
    min_y_ = -10;
    max_y_ = 10;

    pen_radius_ = 1.0;

    sf_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width_ + 2 * margin_w_, height_ + 2 * margin_h_);
    cr_ = cairo_create(sf_);

    cairo_set_source_rgb(cr_, 1.0, 1.0, 1.0);
    cairo_rectangle(cr_, margin_w_, margin_h_, width_, height_);
    cairo_fill(cr_);
    cairo_destroy(cr_);

    inited_ = true;
}

Void AlgsDraw::drawInit()
{
    cr_ = cairo_create(sf_);
    cairo_set_source_rgb(cr_, pen_color_.r_, pen_color_.g_, pen_color_.b_);
    cairo_set_line_width(cr_, pen_radius_);
}

Void AlgsDraw::drawFinish()
{
    cairo_destroy(cr_);
}

Void AlgsDraw::setPenColor(const Color &c)
{
    init();
    pen_color_ = c;
}

Void AlgsDraw::setFont(const String &f)
{
    init();
    font_ = f;
}

Void AlgsDraw::setCanvasSize(Int w, Int h)
{
    init();
    //改变画布大小
    //原来的画布会以左上角对齐的形式
    //复制到新的画布来
    width_ = w;
    height_ = h;
    cairo_surface_t *new_sf = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width_ + 2 * margin_w_, height_ + 2 * margin_h_);
    cairo_t *new_cr = cairo_create(new_sf);
    cairo_set_source_surface(new_cr, sf_, 0, 0);
    cairo_paint(new_cr);
    cairo_surface_destroy(sf_);
    cairo_destroy(new_cr);
    sf_ = new_sf;
}

Void AlgsDraw::clear(const Color &c)
{
    init();
    drawInit();
    cairo_set_source_rgb(cr_, c.r_, c.g_, c.b_);
    cairo_rectangle(cr_, margin_w_, margin_h_, width_, height_);
    cairo_fill(cr_);
    drawFinish();
}

Void AlgsDraw::line(Double x0, Double y0, Double x1, Double y1)
{
    std::cout << "in " << __FUNCTION__ << std::endl;

    init();
    drawInit();

    //计算出图像坐标
    auto real_x0 = (x0 - min_x_) * width_ / (max_x_ - min_x_) + margin_w_;
    auto real_x1 = (x1 - min_x_) * width_ / (max_x_ - min_x_) + margin_w_;
    auto real_y0 = -(y0 - max_y_) * height_ / (max_y_ - min_y_) + margin_h_;
    auto real_y1 = -(y1 - max_y_) * height_ / (max_y_ - min_y_) + margin_h_;

    cairo_move_to(cr_, real_x0, real_y0);
    cairo_line_to(cr_, real_x1, real_y1);
    cairo_stroke(cr_);
    drawFinish();
}

Void AlgsDraw::point(Double x, Double y)
{
    init();
    drawInit();

    cairo_move_to(cr_, x, y);
    cairo_line_to(cr_, x, y);
    cairo_stroke(cr_);

    drawFinish();
}

Void AlgsDraw::setXscale(Double x0, Double x1)
{
    init();
    min_x_ = x0;
    max_x_ = x1;
}

Void AlgsDraw::setYscale(Double y0, Double y1)
{
    init();
    min_y_ = y0;
    max_y_ = y1;
}

Void AlgsDraw::setPenRadius(double r)
{
    init();
    pen_radius_ = r;
}

Void AlgsDraw::show()
{
    init();
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

    //远程的x客户端在本地运行的时候，似乎不会触发resize事件
    XSelectInput(display_, drawable_, ExposureMask | ResizeRedirectMask | SubstructureRedirectMask);
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
            cairo_scale(x11_cr_, double(width) / (width_ + 2 * margin_w_), double(height) / (height_ + 2 * margin_h_));
            cairo_set_source_surface(x11_cr_, sf_, 0, 0);
            cairo_paint(x11_cr_);
            cairo_surface_destroy(x11_sf_);
            cairo_destroy(x11_cr_);
            break;
        case ConfigureNotify:
            //获取当前窗口的宽和高
            width = evt.xresizerequest.width;
            height = evt.xresizerequest.height;
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
            if (evt.xclient.data.l[0] == static_cast<Int>(wmDeleteMessage))
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
    return "";
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
    return "";
}

}
