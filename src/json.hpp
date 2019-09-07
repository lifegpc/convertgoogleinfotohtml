#include<stdio.h>
#include"build.hpp"
#include<json-c/json.h>
#ifndef __CONVERT__JSON__
#define __CONVERT__JSON__
#if sysbit==64
//-1 内存不足 -2 无法读取输入文件 -3 输入文件解析失败 -4 未知的JSON文件 -5 创建输出文件夹失败
int prasefile(FILE* in,char* out,long long filesize,int count);
#endif
#if sysbit==32
//-1 内存不足 -2 无法读取输入文件 -3 输入文件解析失败 -4 未知的JSON文件 -5 创建输出文件夹失败
int prasefile(FILE* in,char* out,long filesize,int count);
#endif
#endif