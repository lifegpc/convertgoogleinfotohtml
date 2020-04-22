#ifndef __INTLIST__
#define __INTLIST__
#include<stdio.h>
class intlist
{
private:
    intlist *perv;
    int num;
    intlist *next;
public:
    intlist()
{
    num=0;
    perv=NULL;
    next=NULL;
}
intlist(int n)
{
    num=n;
    perv=NULL;
    next=NULL;
}
intlist(intlist *p,int n)
{
    perv=p;
    num=n;
    next=NULL;
}
intlist(int k,intlist *n)
{
    next=n;
    num=k;
    perv=NULL;
}
intlist(intlist *p,int k,intlist *n)
{
    perv=p;
    num=k;
    next=n;
}
~intlist()
{
    if(perv!=NULL&&next!=NULL)
    {
        perv->next=next;
        next->perv=perv;
    }
    else if(perv!=NULL)
    {
        perv->next=NULL;
    }
    else if(next!=NULL)
    {
        next->perv=NULL;
    }
    perv=NULL;
    next=NULL;
}
void setn(int n)
{
    num=n;
}
void setp(intlist *p)
{
    perv=p;
}
void setn(intlist *n)
{
    next=n;
}
int n()
{
    return num;
}
intlist* getp()
{
    return perv;
}
intlist* getn()
{
    return next;
}
void dp()
{
    if(perv!=NULL)
    {
        delete perv;
    }
}
void dn()
{
    if(next!=NULL)
    {
        delete next;
    }
}
void addn()
{
    num++;
}
};
//创建下一个intlist
intlist* cnintlist(intlist* p);
#endif
