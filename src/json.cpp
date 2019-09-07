#include<stdio.h>
#include"build.hpp"
#include<json-c/json.h>
#include"json.hpp"
#include"string.h"
#include"convert/browserhistory.hpp"

json_object *json_obj;
lh_table *json_table;

#if sysbit==64
int prasefile(FILE* in,char* out,long long filesize,int count)
#endif
#if sysbit==32
int prasefile(FILE* in,char* out,long filesize,int count)
#endif
{
    char* buf;
    buf=(char *)malloc(filesize+1);
    if(buf==NULL)
    {
        printf("No enough memory.\n");
        return -1;
    }
    #if sysbit==64
    long long re=fread(buf,1,filesize,in);
    #endif
    #if sysbit==32
    long re=fread(buf,sizeof(char),filesize,in);
    #endif
    if(!re)
    {
        printf("Failed to read input file.\n");
        return -2;
    }
    buf[filesize]='\0';
    json_obj=json_tokener_parse(buf);
    if(json_obj==NULL)
    {
        printf("Can not parse the input file.\n");
        return -3;
    }
    free(buf);
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
                    int rr=browserhistory_prase(list,out,count);
                    if(rr==-1)
                    {
                        printf("Unknown JSON file.\n");
                        return -4;
                    }
                    if(rr==2)
                    {
                        printf("Can not create the output directory.\n");
                        return -5;
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