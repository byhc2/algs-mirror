#include <unistd.h>
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

int type;
int imin, imax;

int main(int argc, char *argv[])
{
    if (parseOpt(argc, argv))
    {
        return 0;
    }

    return 0;
}
