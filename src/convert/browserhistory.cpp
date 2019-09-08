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
#include<sys/time.h>

int isbrowserhistoryelement(lh_entry *in);
struct browserhistory* getbrowserhistory(json_object* obj);

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
    for(int i=0;i<list->length;i++)
    {
        if(i%c->count==0)
        {
            int fi=i/c->count+1;
            if(fi>1)
            {
                fprintf(c->out,"</table><div style=\"text-align:center\"><a href=\"%i.html\">The next Page</a></div></body></html>",fi);
                fflush(c->out);
                fclose(c->out);
            }
            char *a=new char[strlen(c->output)+100],*b=new char[100];
            a[0]='\0';
            strcat(a,c->output);
            if(c->output[strlen(c->output)-1]!='/'&&c->output[strlen(c->output)-1]!='\\')strcat(a,"/");
            #ifdef Windows
            _itoa(fi,b,10);
            #endif
            #ifdef Liunx
            sprintf(b,"%d",fi);
            #endif
            strcat(a,b);
            strcat(a,".html");
            #if sysbit==64
            c->out=fopen64(a,"w");
            #endif
            #if sysbit==32
            c->out=fopen(a,"w");
            #endif
            if(c->out==NULL)return -3;
            fprintf(c->out,"<!DOCTYPE html><!--Made by convertgoogleinfotohtml.\nAuthor:Lifegpc\nConvert from:Chrome/BrowserHistory.json\nSource:https://github.com/lifegpc/convertgoogleinfotohtml--><html><head><title>BrowserHistory-%i</title><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, minimum-scale=1.0, maximum-scale=1.0, user-scalable=no\"><style>tr,td{word-wrap:break-word;word-break:break-all;}</style></head><body><h1 style=\"text-align:center\">BrowserHistory Page %i</h1>",fi,fi);
            if(fi>1)fprintf(c->out,"<div style=\"text-align:center\"><a href=\"%i.html\">The previous Page</a></div>",fi-1);
            fprintf(c->out,"<table width=\"%s\"><tr height=\"%s\"><td width=\"%s\">Icon</td><td width=\"%s\">Page transition</td><td width=\"%s\">Title</td><td width=\"%s\">Client id</td><td width=\"%s\">Time usec(Timezone:%li)</td></tr>",c->table->width,c->table->height,c->table->icon,c->table->page_transition,c->table->title,c->table->client_id,c->table->time_usec,timezone);
        }
        obj=(json_object*)array_list_get_idx(list,i);
        browserhistory* re=getbrowserhistory(obj);
        if(re->status==-1)return -1;
        if(re->status==0)
        {
            #ifdef DEBUG
            fprintf(c->out,"<!--%i-->",i);
            #endif
            fprintf(c->out,"<tr height=\"%s\">",c->table->height);
            fprintf(c->out,"<td width=\"%s\">",c->table->icon);
            if(re->favicon_url!=NULL)fprintf(c->out,"<img width=\"100%\" height=\"auto\" src=\"%s\" alt=\"Icon\"/>",re->favicon_url);
            else fprintf(c->out,"NULL");
            fprintf(c->out,"</td><td width=\"%s\">",c->table->page_transition);
            if(re->page_transition!=NULL)fprintf(c->out,"%s",re->page_transition);
            else fprintf(c->out,"NULL");
            fprintf(c->out,"</td><td width=\"%s\">",c->table->title);
            if(re->title!=NULL&&strlen(re->title)!=0)
            {
                if(re->url!=NULL)
                {
                    if(c->table->newtab)fprintf(c->out,"<a href=\"%s\" target=\"_blank\">%s</a>",re->url,re->title);
                    else fprintf(c->out,"<a href=\"%s\">%s</a>",re->url,re->title);
                }
                else fprintf(c->out,"%s",re->title);
            }
            else
            {
                if(re->url!=NULL)
                {
                    if(c->table->newtab)fprintf(c->out,"<a href=\"%s\" target=\"_blank\">",re->url);
                    else fprintf(c->out,"<a href=\"%s\">",re->url);
                    fprintf(c->out,"%s</a>",re->url);
                }
                else fprintf(c->out,"NULL");
            }
            fprintf(c->out,"</td><td width=\"%s\">",c->table->client_id);
            if(re->client_id!=NULL)fprintf(c->out,"%s",re->client_id);
            else fprintf(c->out,"NULL");
            fprintf(c->out,"</td><td width=\"%s\">",c->table->time_usec);
            if(re->time)
            {
                #ifdef Windows
                time_t tt=re->time_usec/1000000ll;
                tm *ti=localtime(&tt);
                char* tti=new char[64];
                strftime(tti,64,"%Y-%m-%d %H:%M:%S",ti);
                fprintf(c->out,"%s",tti);
                delete tti,tt,ti;
                #endif
            }
            fprintf(c->out,"</td></tr>");
            fflush(c->out);
        }
        delete re;
    }
    fprintf(c->out,"</table></body></html>");
    fflush(c->out);
    fclose(c->out);
    return 0;
}
//-1 未知的JSON文件
browserhistory* getbrowserhistory(json_object* obj)
{
    browserhistory* re=new browserhistory();
    re->time=false;
    json_object* tem;
    lh_table *ta=json_object_get_object(obj);
    if(ta->count!=6&&ta->count!=5)
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
                    re->time_usec=json_object_get_int64(tem);
                    re->time=true;
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
    if(x==6||x==5)re->status=0;else re->status=-1;
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