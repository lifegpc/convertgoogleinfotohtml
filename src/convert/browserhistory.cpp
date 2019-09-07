#include"../build.hpp"
#include<stdio.h>
#include<json-c/json.h>
#include<string.h>
#ifdef Windows
#include<direct.h>
#endif
#ifdef Linux
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#endif
#include"../main.hpp"

int isbrowserhistoryelement(lh_entry *in);
struct browserhistory* getbrowserhistory(json_object* obj);

struct browserhistory
{
    const char* favicon_url;
    const char* page_transition;
    const char* title;
    const char* url;
    const char* client_id;
    long time_usec;
    //函数返回状态
    int status;
};

int browserhistory_prase(array_list *list,config* c)
{
    json_object *obj;
    #ifdef Windows
    if(access(c->output,0))
    {
        int rre=mkdir(c->output);
        if(rre)return -2;
    }
    #endif
    #ifdef Linux
    if(opendir(c->output)==NULL)
    {
        int rre=mkdir(c->output,S_IRWXU);
        if(rre)return -2;
    }
    #endif
    else
    {
        bool overwrite=false;
        if(!c->overwriten&&!c->overwritey)
        {
            printf("The output directory is already exist , do you want to overwrite it?(y/n)\nNote:It will delete this directory at first.\n");
            char inn=getc(stdin);
            if(inn=='y'||inn=='Y')overwrite=true;
        }
        if(!c->overwriten&&(c->overwritey||overwrite))
        {
            int le=strlen(c->output)+100;
            char *a=new char[le];
            a[0]='\0';
            #ifdef Windows
            strcat(a,"rmdir /s /q \"");
            #endif
            #ifdef Linux
            strcat(a,"rm -r \"");
            #endif
            strcat(a,c->output);
            strcat(a,"\"");
            system(a);
        }
        else return -2;
        #ifdef Windows
        if(access(c->output,0))
        {
            int rre=mkdir(c->output);
            if(rre)return -2;
        }
        #endif
        #ifdef Linux
        if(opendir(c->output)==NULL)
        {
            int rre=mkdir(c->output,S_IRWXU);
            if(rre)return -2;
        }
        #endif
    }
    for(int i=1;i<=1;i++)
    {
        obj=(json_object*)array_list_get_idx(list,i);
        browserhistory* re=getbrowserhistory(obj);
        if(re->status==-1)return -1;
        if(re->status==0)
        {
            //
        }
    }
    return 0;
}
//-1 未知的JSON文件
browserhistory* getbrowserhistory(json_object* obj)
{
    browserhistory* re=new browserhistory();
    json_object* tem;
    lh_table *ta=json_object_get_object(obj);
    if(ta->count!=6)
    {
        re->status=-1;
        return re;
    }
    lh_entry *te=ta->head;
    int i=1;
    int x=0;
    do
    {
        int r=isbrowserhistoryelement(te);
        if(!r)
        {
            re->status=-1;
            return re;
        }
        else
        {
            if(r<=5)
            {
                tem=json_object_object_get(obj,(const char*)te->k);
                if(json_object_get_type(tem)==json_type_string)
                {
                    if(r==1)re->favicon_url=json_object_get_string(tem);
                    if(r==2)re->page_transition=json_object_get_string(tem);
                    if(r==3)re->title=json_object_get_string(tem);
                    if(r==4)re->url=json_object_get_string(tem);
                    if(r==5)re->client_id=json_object_get_string(tem);
                    x++;
                }
                else
                {
                    re->status=-1;
                    return re;
                }
            }
            else
            {
                tem=json_object_object_get(obj,(const char*)te->k);
                if(json_object_get_type(tem)==json_type_int)
                {
                    re->time_usec=json_object_get_int(tem);
                    x++;
                }
                else
                {
                    re->status=-1;
                    return re;
                }
            }
        }
        if(i<ta->count)te=te->next;
        i++;
    } while (i<=ta->count);
    if(x==6)re->status=0;else re->status=-1;
    return re;
}
//判断是否为BrowserHistory元素
int isbrowserhistoryelement(lh_entry *in)
{
    char* tem=(char*)in->k;
    if(strcmp(tem,"favicon_url")==0)return 1;
    else if(strcmp(tem,"page_transition")==0)return 2;
    else if(strcmp(tem,"title")==0)return 3;
    else if(strcmp(tem,"url")==0)return 4;
    else if(strcmp(tem,"client_id")==0)return 5;
    else if(strcmp(tem,"time_usec")==0)return 6;
    else return 0;
}