#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100
typedef struct{
    char str[MAX];
}element;
element* creathash(int size)
{
    element* hash=malloc(sizeof(element)*size);
    for(int i=0;i<size;i++)
    {
        hash[i].str[0]='1';
        hash[i].str[1]='b';

        hash[i].str[2]='\0';

    }
    return hash;
}   

int main()
{
    element* hash=creathash(10);
    for(int i=0;i<10;i++)
        printf("%s ",hash[i].str);

    return 0;
}



