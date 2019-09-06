#include"build.h"
#include<stdio.h>
#include"help.h"
#include<string.h>
#include"main.hpp"

int main(int argc,char *argv[])
{
    if(argc==1)noinfohelp();
    if(argc==2&&(strcmp(argv[1],"--help")==0||strcmp(argv[1],"/?")==0))help();
    return 0;
}