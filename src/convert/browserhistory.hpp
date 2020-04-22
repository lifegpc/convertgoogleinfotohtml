#include<json-c/json.h>
#include"../main.hpp"
#ifndef __CONVERT__CONVERT__BROWSERHISTORY__
#define __CONVERT__CONVERT__BROWSERHISTORY__
//解析Browser History
//-1 未知的JSON文件 -2 创建输出文件夹失败 -3 创建输出文件失败
int browserhistory_prase(array_list *list,config* c);
struct browserhistory
{
    const char* favicon_url;
    const char* page_transition;
    const char* title;
    const char* url;
    const char* client_id;
    long long time_usec;
    //函数返回状态
    int status;
    bool time;
};
#endif