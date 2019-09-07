/*help.cpp
This file contains the method to provide support.*/
#include"build.hpp"
#include<stdio.h>

void noinfohelp()
{
    printf("Command:\n\tconvert [-el|-dl] [-s count] input output\nDescription:\n\tConvert google user's data from json to html.\nPlease use \"convert --help\" or \"convert /?\" to get more information.\n");
}

void help()
{
    printf("convert [-el|-dl] [-s count] input output\n-el:Use json-c.\n-dl:Not use json-c.\nNote:If not specified and the file size is larger than 32M , it will not use json-c.\n-s count:The maximum count of data in a file.\nNote:The default is 1000.\ninput: The input file.\noutput:The output directory.\n");
}