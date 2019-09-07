#include<json-c/json.h>
#ifndef __CONVERT__CONVERT__BROWSERHISTORY__
#define __CONVERT__CONVERT__BROWSERHISTORY__
//解析Browser History
//-1 未知的JSON文件 -2 创建输出文件夹失败
int browserhistory_prase(array_list *list,char* output,int count);
#endif