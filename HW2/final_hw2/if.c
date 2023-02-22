//test structure return function
/*  conclusion : you can pass the whole structure element 
                 without encoding the data within one by one    */
#include<stdio.h>
typedef struct 
{
    int data;
    int key;
    char c;
}element;

element passelement(element a){
    a.data++;
    a.key++;
    a.c="b";
    return a;  
}

int main(){
    element x;
    element test;
    x.data=1;
    x.key=1;
    x.c="a";
    test=passelement(x);
    printf("x:%d %d %c\n",x.data,x.key,x.c);
    printf("test:%d %d %c\n",test.data,test.key,test.c);

    return 0;
}