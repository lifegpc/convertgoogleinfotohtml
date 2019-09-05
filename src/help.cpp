/*help.cpp
This file contains the method to provide support.*/
#include"build.h"
#include<stdio.h>

void noinfohelp()
{
    printf("Command:\n\tconvert input output\nDescription:\n\tConvert google user's data from json to html.\nPlease use \"convert --help\" or \"convert /?\" to get more information.\n");
}

void help()
{
    printf("convert input output\ninput: The input file.\noutput:The output file.\n");
}