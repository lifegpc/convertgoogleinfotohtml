#include"build.hpp"
#include<stdio.h>
#include"help.hpp"
#include<string.h>
#include"main.hpp"
#include"string.hpp"
//convert [-el|-dl] input output
int main(int argc,char *argv[])
{
    if(argc==1)noinfohelp();
    if(argc==2&&(strcmp(argv[1],"--help")==0||strcmp(argv[1],"/?")==0))help();
    if(argc==3)
    {
        for(int i=1;i<3;i++)
        {
            if(ischoice(argv[i],false))
            {
                printf("There is no input file name or output file name.\n");
                return -1;
            }
        }
        input=argv[1];
        output=argv[2];
        #ifdef DEBUG
        printf("input:%s\noutput:%s\n",input,output);
        #endif
    }
    return 0;
}