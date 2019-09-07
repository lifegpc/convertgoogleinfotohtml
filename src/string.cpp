#include<string.h>

bool ischoice(char* input)
{
    if(input[0]=='-')
    {
        if(strcmp(input,"-el")==0||strcmp(input,"-dl")==0)return true;
        else if(strcmp(input,"-s")==0)return true;
        else if(strcmp(input,"-cy")==0|strcmp(input,"-cn")==0)return true;
        else return false;
    }
    else return false;
}

bool ischoice(char* input,bool strict)
{
    if(strict==true)return ischoice(input);
    else
    {
        if(input[0]=='-')return true; else return false;
    }
}

int getchoice(char* input)
{
    if(strcmp(input,"-el")==0||strcmp(input,"-dl")==0)return 1;
    else if(strcmp(input,"-s")==0)return 2;
    else if(strcmp(input,"-cy")==0|strcmp(input,"-cn")==0)return 3;
    else return -1;
}
