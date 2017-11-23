#include <iostream>
#include "algsnum.h"
#include "algsramdom.h"

using namespace std;

//根据命令行参数，输出若干随机数

struct Config
{
    int type_; //整数、浮点数
    Double dlow_;
    Double dhigh_;
    Int ilow_;
    Int ihigh_;
    Uint count_; //多少组随机数
    Uint num_; //每组几个
};

Config config;

int init(int argc, char *argv[])
{
    struct option opts[] = {
        {"int", no_argument, 0, 'i'},
        {"double", no_argument, 0, 'd'},
        {"low", required_argument, 0, 'l'},
        {"high", required_argument, 0, 'h'},
        {"num", optional_argument, 0, 'n'},
        {"count", required_argument, 0, 'c'},
        {0, 0, 0, 0},
    };

    while (1)
    {
        int longindex;
        int c = getopt_long(argc, argv, "idl:h:n::c:",
                opts, &longindex);
        if (c == -1)
        {
            return -1;
        }
        switch (c)
        {
        case 'i':
            config.type_ = 1;
            break;
        case 'd':
            config.type_ = 2;
            break;
        case 'l':
        }
    }
}

int main(int argc, char *argv[])
{
    if (init(argc, argv))
    {
        return -1;
    }

    AlgsRandom::initialize();
    if (config.type_ == 1) //整数
    {
        for (auto i = 0; i < config.count_; ++i)
        {
            for (auto j = 0; j < config.num_; ++j)
            {
                cout << AlgsRandom::uniform(config.ilow_, config.ihigh_)
                    << "\t";
            }
            cout << endl;
        }
    }
    else
    {
        for (auto i = 0; i < config.count_; ++i)
        {
            for (auto j = 0; j < config.num_; ++j)
            {
                cout << AlgsRandom::uniform(config.dlow_, config.dhigh_)
                    << "\t";
            }
            cout << endl;
        }
    }
    return 0;
}
