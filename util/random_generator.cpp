#include <libintl.h>
#include <unistd.h>
#include <cstdio>
#include "algsrandom.h"

void usage(int status)
{
    if (status)
    {
        fprintf(stderr, _("%s --help 获取帮助信息\n"), program_name);
    }
    else
    {
        fprintf(stdout, _("用法：%s [选项] <数量>\n"));
        fprintf(stdout, _("  -m<value>,--min=<value> 随机序列的最小值\n"));
        fprintf(stdout, _("  -M<value>,--max=<value> 随机序列的最大值\n"));
        fprintf(stdout, _("  -t<value>,--type=<value> 类型，i 整型，d 浮点\n"));
        fprintf(stdout, _("  -h,--help 输出帮助信息\n"));
    }
    return;
}

static struct option long_options[] = {
    {"min", required_argument, 0, 'm'},
    {"max", required_argument, 0, 'M'},
    {"type", required_argument, 0, 't'},
    {"help", required_argument, 0, 'h'},
    {0, 0, 0, 0},
};
const char optstr[] = "m:M:t:h";

enum GenType
{
    UNDEFINED_TYPE,
    INT_TYPE,
    FLOAT_TYPE,
};
struct Config
{
    Config() : has_min(0), has_max(0), type(UNDEFINED_TYPE)
    {}
    int has_min;
    int has_max;
    union min
    {
        int i;
        double d;
    };
    union max
    {
        int i;
        double d;
    };
    GenType type;
} config;

int parseOpt(int argc, char *argv[])
{
    int c;
    int optidx;
    while ((c = getopt_long(argc, argv, optstr, option, &optidx)) != -1)
    {
        switch (c)
        {
        case 'm':
            config.has_min = 1;
            switch (config.type)
            {
            case INT_TYPE:
                config.min.i = atoi(optarg);
                break;
            case FLOAT_TYPE:
                config.min.d = atof(optarg);
                break;
            default:
                break;
            };
            break;
        case 'M':
            config.has_max = 1;
            switch (config.type)
            {
            case INT_TYPE:
                config.max.i = atoi(optarg);
                break;
            case FLOAT_TYPE:
                config.max.d = atof(optarg);
                break;
            default:
                break;
            };
            break;
        case 't':
            if(string(optarg)=="i")
            {
                config.type=INT_TYPE;
            }
            else if(string(optarg)=="d")
            {
                config.type=FLOAT_TYPE;
            }
            if(config.type==UNDEFINED_TYPE)
            {
            }
            break;
        };
    }
}

int main(int argc, char *argv[])
{
    if (parseOpt(argc, argv))
    {
        return 0;
    }

    return 0;
}
