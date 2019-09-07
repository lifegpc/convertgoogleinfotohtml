#include"build.hpp"
#include<stdio.h>
#include"help.hpp"
#include<string.h>
#include"main.hpp"
#include"string.hpp"
#include"json.hpp"
//convert [-el|-dl] [-s count] [-cy|-cn] input output
//1 获取帮助成功 -1 不正确的参数 -2 打不开输入文件 -3 无法获取输入文件的大小
//-4 内存不足 -5 无法读取输入文件 -6 输入文件解析失败 -7 未知的JSON文件
//-8 创建输出文件夹失败 -9 创建输出文件失败
int main(int argc,char *argv[])
{
    config *c=new config();
    c->usejsonc=true;
    c->disjsonc=false;
    c->enjsonc=false;
    c->fz=32*1024*1024;
    c->count=1000;
    c->overwritey=false;
    c->overwriten=false;
    if(argc==1)
    {
        noinfohelp();
        return 1;
    }
    if(argc==2&&(strcmp(argv[1],"--help")==0||strcmp(argv[1],"/?")==0))
    {
        help();
        return 1;
    }
    if(argc==3)
    {
        for(int i=1;i<3;i++)
        {
            if(ischoice(argv[i],false))
            {
                printf("There is no input file name or output directory name.\n");
                return -1;
            }
        }
        c->input=argv[1];
        c->output=argv[2];
    }
    else
    {
        int index=0;
        int bindex=0;
        int tem;
        for(int i=1;i<argc;i++)
        {
            if(ischoice(argv[i],false))
            {
                if(ischoice(argv[i]))
                {
                    tem=getchoice(argv[i]);
                    if(tem>index)
                    {
                        index=tem;
                        if(tem==1)
                        {
                            if(strcmp(argv[i],"-el")==0)c->enjsonc=true;
                            else c->disjsonc=true;
                        }
                        if(tem==2)
                        {
                            i++;
                            c->count=atoi(argv[i]);
                            if(c->count<=0)
                            {
                                printf("Invalid parameter.\n");
                                return -1;
                            }
                        }
                        if(tem==3)
                        {
                            if(strcmp(argv[i],"-cy")==0)c->overwritey=true;
                            else c->overwriten=true;
                        }
                    }
                    else
                    {
                        printf("Invalid parameter.\n");
                        return -1;
                    }
                }
                else
                {
                    printf("Invalid parameter.\n");
                    return -1;
                }
            }
            else
            {
                if(bindex==0)c->input=argv[i];
                else if(bindex==1)c->output=argv[i];
                else
                {
                    printf("Invalid parameter.\n");
                    return -1;
                }
                bindex++;
            }
        }
        if(bindex!=2)
        {
            printf("Invalid parameter.\n");
            return -1;
        }
    }
    #if sysbit==64
    c->in=fopen64(c->input,"r");
    #endif
    #if sysbit==32
    c->in=fopen(c->input,"r");
    #endif
    if(c->in==NULL)
    {
        printf("Can not open input file.\n");
        return -2;
    }
    #if sysbit==64
    if(fseeko64(c->in,0,SEEK_END)==0)
    {
        c->filesize=ftello64(c->in);
        fseeko64(c->in,0,SEEK_SET);
    }
    #endif
    #if sysbit==32
    if(fseeko(c->in,0,SEEK_END)==0)
    {
        c->filesize=ftello(c->in);
        fseeko(c->in,0,SEEK_SET);
    }
    #endif
    else
    {
        printf("Can not get the size of input file.\n");
        return -3;
    }
    if(c->filesize>c->fz)c->usejsonc=false;else c->usejsonc=true;
    if(c->enjsonc)c->usejsonc=true;
    if(c->disjsonc)c->usejsonc=false;
    #ifdef DEBUG
    printf("usejsonc:%s\ndisjsonc:%s\nenjsonc:%s\ninput:%s\noutput:%s\n",c->enjsonc?"true":"false",c->disjsonc?"true":"false",c->enjsonc?"true":"false",c->input,c->output);
    #if sysbit==64
    printf("filesize:%lli\n",c->filesize);
    #endif
    #if sysbit==32
    printf("filesize:%li\n",c->filesize);
    #endif
    printf("count:%i\noverwritey:%s\noverwriten:%s\n",c->count,c->overwritey?"true":"false",c->overwriten?"true":"false");
    #endif
    if(c->usejsonc)
    {
        int re=prasefile(c);
        if(re==-1)return -4;
        if(re==-2)return -5;
        if(re==-3)return -6;
        if(re==-4)return -7;
        if(re==-5)return -8;
        if(re==-6)return -9;
    }
    return 0;
}