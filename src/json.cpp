#include<stdio.h>
#include"build.hpp"
#include<json-c/json.h>
#include"json.hpp"

json_object *json_obj;

#if sysbit==64
int prasefile(FILE* in,long long filesize)
#endif
#if sysbit==32
int prasefile(FILE* in,long filesize)
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
        printf("Failed to read input file.");
        return -2;
    }
    buf[filesize]='\0';
    json_obj=json_tokener_parse(buf);
    if(json_obj==NULL)
    {
        printf("The input file is not a JSON file.");
        return -3;
    }
    free(buf);
    return 0;
}