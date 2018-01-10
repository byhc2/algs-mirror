#include <unistd.h>
#include <cassert>
#include <iostream>
#include "algsdraw.h"
#include "algsnum.h"
#include "algstl_array.h"
#include "geometry.h"

using namespace std;
using namespace algs;
using namespace algstl;

struct Config
{
    Bool has_min_;
    Bool has_max_;
    Double min_;
    Double max_;
    Int count_;
} config;

int main(int argc, char *argv[])
{
    int c;
    config.count_ = -1;
    while ((c = getopt(argc, argv, "n:m:M:")) != -1)
    {
        switch (c)
        {
        case 'n':
            config.count_ = Num::parseInt(optarg);
            break;
        case 'm':
            config.min_ = Num::parseDouble(optarg);
            break;
        case 'M':
            config.max_ = Num::parseDouble(optarg);
            break;
        default:
            cerr << "usage: " << argv[0] << " -m<min> -M<max> -n<num>" << endl;
            return -1;
            break;
        }
    }

    if (config.count_ == -1)
    {
        cerr << "usage: " << argv[0] << " -m<min> -M<max> -n<num" << endl;
        return -1;
    }

    Array<Interval2D> intervals;
    for (auto i = 0; i < config.count_; ++i)
    {
        Double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        auto tmp = Interval2D(Interval1D(x1, y1), Interval1D(x2, y2));
        if (!tmp)
        {
            //空区间，跳过
            continue;
        }
        intervals += tmp;
    }

    AlgsDraw::setXscale(0, 1);
    AlgsDraw::setYscale(0, 1);
    AlgsDraw::setPenRadius(1.0);

    for (decltype(intervals.size()) i = 0; i < intervals.size(); ++i)
    {
        for (decltype(i) j = i + 1; j < intervals.size(); ++j)
        {
            auto &r = intervals[i];
            auto &s = intervals[j];
            if (&r == &s)
            {
                continue;
            }

            auto tmp = r & s;

            if (tmp == r || tmp == s)
            {
                cout << "找到包含区间" << r << ", " << s << endl;
                continue;
            }

            if (tmp)
            {
                cout << "找到相交区间" << r << ", " << s << endl;
                auto cp1 = r.center();
                AlgsDraw::rectangle(cp1.x_, cp1.y_, r.x_.length(),
                                    r.y_.length());
                auto cp2 = s.center();
                AlgsDraw::rectangle(cp2.x_, cp2.y_, s.x_.length(),
                                    s.y_.length());

                auto c = AlgsDraw::getPenColor();
                AlgsDraw::setPenColor(AlgsDraw::Color(1.0, 0, 0));
                auto cp3 = tmp.center();
                AlgsDraw::filledRectangle(cp3.x_, cp3.y_, tmp.x_.length(),
                                          tmp.y_.length());
                AlgsDraw::setPenColor(c);
            }
        }
    }
    AlgsDraw::show();

    return 0;
}

//2.4
//hello
//world
//
//2.5
//跟方法定义有关
