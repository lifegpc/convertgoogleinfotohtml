/*help.cpp
This file contains the method to provide support.*/
#include"build.hpp"
#include<stdio.h>

void noinfohelp()
{
    printf("Command:\n\tconvert [-el|-dl] input output\nDescription:\n\tConvert google user's data from json to html.\nPlease use \"convert --help\" or \"convert /?\" to get more information.\n");
}

void help()
{
    printf("convert [-el|-dl] input output\n-el:Use json-c.\n-dl:Not use json-c.\nNote:If not specified and the file size is larger than 32M , it will not use json-c.\ninput: The input file.\noutput:The output file.\n");
}