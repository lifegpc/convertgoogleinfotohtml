#include<stdio.h>
#include"build.hpp"
#include<json-c/json.h>
#include"main.hpp"
#ifndef __CONVERT__JSON__
#define __CONVERT__JSON__
#if sysbit==64
//-1 内存不足 -2 无法读取输入文件 -3 输入文件解析失败 -4 未知的JSON文件 -5 创建输出文件夹失败
//-6 创建输出文件失败
int prasefile(config* c);
#endif
#if sysbit==32
//-1 内存不足 -2 无法读取输入文件 -3 输入文件解析失败 -4 未知的JSON文件 -5 创建输出文件夹失败
//-6 创建输出文件失败 
int prasefile(config* c);
#endif
//自建解析
//-1 内存不足 -2 无法读取输入文件 -3 输入文件解析失败 -4 未知的JSON文件
int myprasefile(config* c);
#endif