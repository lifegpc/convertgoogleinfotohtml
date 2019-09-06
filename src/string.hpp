#ifndef __CONVERT__STRING__
#define __CONVERT__STRING__
//判断是否为选项（完全匹配）
bool ischoice(char* input);
//判断是否为选项，strict是否进行完全匹配
bool ischoice(char* input,bool strict);
//获取选项索引，不存在为-1
int getchoice(char* input);
#endif