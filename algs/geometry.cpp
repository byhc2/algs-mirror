#include "geometry.h"

namespace algs
{

Point2D::Point2D(): x_(0.0), y_(0.0), theta_(0.0), r_(0.0) {}

Point2D::Point2D(Double x, Double y): x_(x), y_(y)
{
}

Point2D::Point2D(Point2D::Theta t, Double r): theta_(t.t_), r_(r)
{
}

}
