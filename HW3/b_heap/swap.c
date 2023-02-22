#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int data;
}Node;

void swap_wrong(Node* a, Node* b){
    
    printf("in swap wrong, before:");
    printf("%d %d\n",a->data,b->data);
    Node* temp=a;
    a=b;
    b=temp;
    
    printf("in swap wrong, after:");
    printf("%d %d\n",a->data,b->data);
};//this change the pointer

void swap_correct(Node* x, Node* y)
{   
    Node tmp = *x;
    *x = *y;
    *y = tmp;
};

int main(){
    Node* a=malloc(sizeof(Node));
    Node* b=malloc(sizeof(Node));
    a->data=1;
    b->data=2;
    
    printf("%d %d\n",a->data,b->data);
    swap_wrong(a,b);
    printf("after swap wrong: %d %d\n",a->data,b->data);
    swap_correct(a,b);
    printf("after swap correct: %d %d\n",a->data,b->data);

    return 0;
}