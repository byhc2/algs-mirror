#include <getopt.h>
//#include <libintl.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include "algsrandom.h"

using namespace std;
using namespace algs;

const char *program_name = "rg";

void usage(int status)
{
    if (status)
    {
        fprintf(stderr, "%s --help 获取帮助信息\n", program_name);
    }
    else
    {
        fprintf(stdout, "用法：%s [选项] <数量>\n", program_name);
        fprintf(stdout, "  -m<value>,--min=<value> 随机序列最小值\n");
        fprintf(stdout, "  -M<value>,--max=<value> 随机序列最大值\n");
        fprintf(stdout, "  -t<value>,--type=<value> 类型，i整型，d浮点\n");
        fprintf(stdout, "  -h,--help 输出帮助信息\n");
    }
    return;
}

static struct option long_options[] = {
    {"min", required_argument, 0, 'm'},  {"max", required_argument, 0, 'M'},
    {"type", required_argument, 0, 't'}, {"group", optional_argument, 0, 'g'},
    {"help", no_argument, 0, 'h'},       {0, 0, 0, 0},
};
const char optstr[] = "m:M:t:hg::";

enum GenType
{
    UNDEFINED_TYPE,
    INT_TYPE,
    FLOAT_TYPE,
};
struct Config
{
    Config() : has_min_(0), has_max_(0), type_(UNDEFINED_TYPE), group_(1)
    {}
    int has_min_;
    int has_max_;
    union Value
    {
        int i_;
        double d_;
    };
    Value min_;
    Value max_;
    GenType type_;
    size_t count_;
    size_t group_;
} config;

int parseOpt(int argc, char *argv[])
{
    int c;
    int optidx;
    string typearg;
    while ((c = getopt_long(argc, argv, optstr, long_options, &optidx)) != -1)
    {
        switch (c)
        {
        case 'm':
            config.has_min_ = 1;
            switch (config.type_)
            {
            case INT_TYPE:
                config.min_.i_ = atoi(optarg);
                break;
            case FLOAT_TYPE:
                config.min_.d_ = atof(optarg);
                break;
            default:
                break;
            };
            break;
        case 'M':
            config.has_max_ = 1;
            switch (config.type_)
            {
            case INT_TYPE:
                config.max_.i_ = atoi(optarg);
                break;
            case FLOAT_TYPE:
                config.max_.d_ = atof(optarg);
                break;
            default:
                break;
            };
            break;
        case 'g':
            config.group_ = atoi(optarg);
            config.group_ = config.group_ ? config.group_ : 1;
            break;
        case 't':
            typearg = string(optarg);
            if (config.type_ != UNDEFINED_TYPE)
            {
                break;
            }
            if (typearg == "i")
            {
                config.type_ = INT_TYPE;
                optind       = 1;
            }
            else if (typearg == "d")
            {
                config.type_ = FLOAT_TYPE;
                optind       = 1;
            }
            if (config.type_ == UNDEFINED_TYPE)
            {
                cerr << "类型参数" + typearg + "未定义" << endl;
                usage(0);
                return -1;
            }
            break;
        case 'h':
            usage(0);
            return 0;
        default:
            usage(1);
            return -1;
            break;
        };
    }

    if (config.type_ == UNDEFINED_TYPE)
    {
        cerr << "缺少-t类型参数" << endl;
        usage(0);
        return -1;
    }
    else if (config.type_ == INT_TYPE && config.min_.i_ >= config.max_.i_)
    {
        cerr << "序列下界(" << config.min_.i_ << ")必须小于上界("
             << config.max_.i_ << ")" << endl;
        return -1;
    }
    else if (config.type_ == FLOAT_TYPE && config.min_.d_ >= config.max_.d_)
    {
        cerr << "序列下界(" << config.min_.d_ << ")必须小于上界("
             << config.max_.d_ << ")" << endl;
        return -1;
    }

    if (optind == argc)
    {
        config.count_ = 1;
    }
    else
    {
        config.count_ = atoi(argv[optind]);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (parseOpt(argc, argv))
    {
        return 0;
    }

    AlgsRandom::initialize();
    for (size_t i = 0; i < config.count_; ++i)
    {
        for (size_t j = 0; j < config.group_; ++j)
        {
            if (config.type_ == INT_TYPE)
            {
                cout << AlgsRandom::uniform(config.min_.i_, config.max_.i_)
                     << "\t";
            }
            else if (config.type_ == FLOAT_TYPE)
            {
                cout << AlgsRandom::uniform(config.min_.d_, config.max_.d_)
                     << "\t";
            }
        }
        cout << endl;
    }

    return 0;
}
