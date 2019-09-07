#include"build.hpp"
#include<stdio.h>
#include"help.hpp"
#include<string.h>
#include"main.hpp"
#include"string.hpp"
#include"json.hpp"
//convert [-el|-dl] [-s count] input output
//1 获取帮助成功 -1 不正确的参数 -2 打不开输入文件 -3 无法获取输入文件的大小
//-4 内存不足 -5 无法读取输入文件 -6 输入文件解析失败 -7 未知的JSON文件
//-8 创建输出文件夹失败 -9 删除已有输出文件夹失败
int main(int argc,char *argv[])
{
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
        input=argv[1];
        output=argv[2];
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
                            if(strcmp(argv[i],"-el")==0)enjsonc=true;
                            else disjsonc=true;
                        }
                        if(tem==2)
                        {
                            i++;
                            count=atoi(argv[i]);
                            if(count<=0)
                            {
                                printf("Invalid parameter.\n");
                                return -1;
                            }
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
                if(bindex==0)input=argv[i];
                else if(bindex==1)output=argv[i];
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
    in=fopen64(input,"r");
    #endif
    #if sysbit==32
    in=fopen(input,"r");
    #endif
    if(in==NULL)
    {
        printf("Can not open input file.\n");
        return -2;
    }
    #if sysbit==64
    if(fseeko64(in,0,SEEK_END)==0)
    {
        filesize=ftello64(in);
        fseeko64(in,0,SEEK_SET);
    }
    #endif
    #if sysbit==32
    if(fseeko(in,0,SEEK_END)==0)
    {
        filesize=ftello(in);
        fseeko(in,0,SEEK_SET);
    }
    #endif
    else
    {
        printf("Can not get the size of input file.\n");
        return -3;
    }
    if(filesize>fz)usejsonc=false;else usejsonc=true;
    if(enjsonc)usejsonc=true;
    if(disjsonc)usejsonc=false;
    #ifdef DEBUG
    printf("usejsonc:%s\ndisjsonc:%s\nenjsonc:%s\ninput:%s\noutput:%s\n",usejsonc?"true":"false",disjsonc?"true":"false",enjsonc?"true":"false",input,output);
    #if sysbit==64
    printf("filesize:%lli\n",filesize);
    #endif
    #if sysbit==32
    printf("filesize:%li\n",filesize);
    #endif
    printf("count:%i\n",count);
    #endif
    if(usejsonc)
    {
        int re=prasefile(in,output,filesize,count);
        if(re==-1)return -4;
        if(re==-2)return -5;
        if(re==-3)return -6;
        if(re==-4)return -7;
        if(re==-5)return -8;
        if(re==-6)return -9;
    }
    return 0;
}