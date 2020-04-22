#include"intlist.hpp"
#include<stdio.h>
intlist* cnintlist(intlist* p)
{
    intlist *temp;
    temp=new intlist(p,0);
    p->setn(temp);
    return temp;
}
