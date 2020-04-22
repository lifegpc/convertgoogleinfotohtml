#include<stdio.h>
#include"build.hpp"
#include<json-c/json.h>
#include"json.hpp"
#include"string.h"
#include"convert/browserhistory.hpp"
#include"main.hpp"
#include"string.hpp"

json_object *json_obj;
lh_table *json_table;

#if sysbit==64
int prasefile(config* c)
#endif
#if sysbit==32
int prasefile(config* c)
#endif
{
    char* buf;
    buf=(char *)malloc(c->filesize+1);
    if(buf==NULL)
    {
        printf("No enough memory.\n");
        return -1;
    }
    #if sysbit==64
    long long re=fread(buf,1,c->filesize,c->in);
    #endif
    #if sysbit==32
    long re=fread(buf,1,c->filesize,c->in);
    #endif
    if(!re)
    {
        printf("Failed to read input file.\n");
        return -2;
    }
    buf[c->filesize]='\0';
    json_obj=json_tokener_parse(buf);
    if(json_obj==NULL)
    {
        printf("Can not parse the input file.\n");
        return -3;
    }
    free(buf);
    fclose(c->in);
    json_type type=json_object_get_type(json_obj);
    if(type==json_type_object)
    {
        json_table=json_object_get_object(json_obj);
        if(json_table->count==1)
        {
            lh_entry *tem;
            tem=json_table->head;
            #ifdef DEBUG
            printf("%s\n",(char *)tem->k);
            #endif
            if(strcmp((const char *)tem->k,"Browser History")==0)
            {
                json_object *obj=NULL;
                obj=json_object_object_get(json_obj,(const char *)tem->k);
                type=json_object_get_type(obj);
                if(type==json_type_array)
                {
                    array_list *list;
                    list=json_object_get_array(obj);
                    #ifdef DEBUG
                    printf("%i\n",list->length);
                    #endif
                    int rr=browserhistory_prase(list,c);
                    if(rr==-1)
                    {
                        printf("Unknown JSON file.\n");
                        return -4;
                    }
                    if(rr==-2)
                    {
                        printf("Can not create the output directory.\n");
                        return -5;
                    }
                    if(rr==-3)
                    {
                        printf("Can not create the output file.");
                        return -6;
                    }
                }
                else
                {
                    printf("Unknown JSON file.\n");
                    return -4;
                }
            }
            else
            {
                printf("Unknown JSON file.\n");
                return -4;
            }
        }
        else
        {
            printf("Unknown JSON file.\n");
            return -4;
        }
    }
    else
    {
        printf("Unknown JSON file.\n");
        return -4;
    }
    return 0;
}

int myprasefile(config* c)
{
    char *buf,*buf2,*sour;
    buf=(char *)malloc(1024);
    buf2=(char *)malloc(10240);
    buf2[0]='\0';
    sour=(char *)malloc(1024);
    sour[0]='\0';
    if(buf==NULL)
    {
        printf("No enough memory.\n");
        return -1;
    }
    long re=fread(buf,1,1024,c->in);
    if(!re)
    {
        printf("Failed to read input file.\n");
        return -2;
    }
    //左大括号
    long ldk=0;
    //左中括号
    long lzk=0;
    bool isstr=false;
    long sl=0;
    //需要继续的内容
    long ct=0;
    long ctz=0;
    bool first=true;
    //内容 1 Browser History
    int st=0;
pa: while(re>0)
    {
        char t=buf[0];
        if(ct>0)
        {
            if(ctz==1)
            {
                for(int i=0;i<=ct-1;i++)
                {
                    buf2[sl+i]=buf[i];
                }
                buf+=ct;
                re-=ct;
                sl+=ct;
                ctz=0;
                ct=0;
            }
            goto pa;
        }
        if(t=='\\'&&isstr)
        {
            if(buf[1]=='u')
            {
                if(re>=6)
                {
                    for(int i=0;i<=5;i++)
                    {
                        buf2[sl+i]=buf[i];
                    }
                    buf+=6;
                    re-=5;
                    sl+=6;
                }
                else
                {
                    ct=6-re;
                    for(int i=0;i<=re-1;i++)
                    {
                        buf2[sl+i]=buf[i];
                    }
                    buf+=re;
                    sl+=re;
                    re=1;
                    ctz=1;
                }
            }
            else
            {
                if(re>=2)
                {
                    buf2[sl++]=t;
                    buf2[sl++]=buf[1];
                    buf+=2;
                    re--;
                }
                else
                {
                    ct=1;
                    ctz=1;
                    buf2[sl++]=t;
                    buf++;
                }
            }
        }
        else if(t=='"')
        {
            isstr=!isstr;
            if(isstr)sl=0;
            else
            {
                buf2[sl]='\0';
                printf("%s\n",buf2);
                if(first&&ldk==1&&lzk==0)
                {
                    first=false;
                    strcpy(sour,buf2);
                    if(strcmp(sour,"Browser History")==0)
                    {
                        st=1;
                    }
                    else
                    {
                        printf("Unknown JSON file.\n");
                        return -4;
                    }
                    
                }
            }
            buf++;
        }
        else if(isstr)
        {
            buf2[sl]=buf[0];
            buf++;
            sl++;
        }
        else if(isuselesschar(t))buf++;
        else if(t=='{')
        {
            ldk++;
            buf++;
            printf("ldk=%li\n",ldk);
        }
        else if(t=='}')
        {
            ldk--;
            buf++;
            printf("ldk=%li\n",ldk);
        }
        else if(t=='[')
        {
            lzk++;
            buf++;
            printf("lzk=%li\n",lzk);
        }
        else if(t==']')
        {
            lzk--;
            buf++;
            printf("lzk=%li\n",lzk);
        }
        else buf++;
        re--;
    }
    buf-=1024;
    re=fread(buf,1,1024,c->in);
    if(re>0)goto pa;
    printf("%li",re);
    return 0;
}
