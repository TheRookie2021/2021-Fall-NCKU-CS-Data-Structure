#include <stdio.h>
#include <string.h>
#define MAX 10

int main(){
    char arr[MAX];
    arr[0]='\0';
    /*
    for(int i=0;i<MAX;i++)
    {
       arr[i]='\0';
    }
    */
    for(int i=0;i<MAX;i++)
    {
        printf("%c ",arr[i]);
    }
    return 0;
}