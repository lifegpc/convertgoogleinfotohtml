/*help.cpp
This file contains the method to provide support.*/
#include"build.hpp"
#include<stdio.h>

void noinfohelp()
{
    printf("Command:\n\tconvert [-el|-dl] [-s count] [-cy|-cn] [-w table_width iconwidth page_transitionwidth titlewidth client_idwidth time_usecwidth] [-h height] input output\nDescription:\n\tConvert google user's data from json to html.\nPlease use \"convert --help\" or \"convert /?\" to get more information.\n");
}

void help()
{
    printf("convert [-el|-dl] [-s count] [-cy|-cn] [-w table_width iconwidth page_transitionwidth titlewidth client_idwidth time_usecwidth] [-h height] input output\n\n-el:Use json-c.\n-dl:Not use json-c.\nNote:If not specified and the file size is larger than 32M , it will not use json-c.\n\n-s count:The maximum count of data in a file.\nNote:The default is 1000.\n\n-cy:If the output directory is already exist , don't ask me and automatically to overwrite it.\n-cn:If the output directory is already exist , don't ask me and stop the convert.\n\n-w The html(html5) elements' width.\ntable_width:The whole table's width.(Default:100%%)\niconwidth:icon's width.(Default:10%%)\npage_transitionwidth:page_transition's width.(Default:10%%)\ntitlewidth:title's width.(Default:50%%)\nclient_idwidth:client_id's width.(Default:15%%)\ntime_usecwidth:time_usec's width.(Default:15%%)\n\n-h The html(html5) elements' height.\nheight:The whole table's height.(Default:auto)\n\ninput: The input file.\noutput:The output directory.\n");
}