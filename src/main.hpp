#include<stdio.h>
#include"build.hpp"
#ifndef __CONVERT__MAIN__
#define __CONVERT__MAIN__
struct config
{
    //是否使用json-c
    bool usejsonc;
    //是否强制不使用json-c
    bool disjsonc;
    //是否强制使用json-c
    bool enjsonc;
    //输入文件名
    char* input;
    //输出文件名
    char* output;
    //输入文件
    FILE *in;
    #if sysbit==64
    //文件大小
    long long filesize;
    #endif
    #if sysbit==32
    //文件大小
    long filesize;
    #endif
    //临界大小
    long fz;
    //单个文件最大存储数据条数
    int count;
    //输出文件夹存在时自动覆盖
    bool overwritey;
    //输出文件夹存在时自动退出
    bool overwriten;
};
#endif
