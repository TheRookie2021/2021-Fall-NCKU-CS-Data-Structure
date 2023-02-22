
#include<stdio.h>
#include<stdlib.h>
typedef struct 
{
    int key;
    int shortest_path;
    struct element* lchild;
    struct element* rchild;

}element;
typedef struct{
    struct element* head;
}Leftist;

void Insert(Leftist root, int num){
    element * newnode=malloc(sizeof(element));
    newnode->key=num;
    element* temp=root.head;
    if(temp==NULL) temp=newnode;
    else temp->lchild=newnode;

}

int main(){
    Leftist a;
    
    printf("%d\n", a.head);
    Insert(a,1);
    Insert(a,3);
    Insert(a,9);
    printf("%d\n", a.head);
    element* temp=a.head;
    printf("%d\n", temp->key);
    temp=temp->lchild;
    printf("%d\n", temp->key);
    temp=temp->lchild;
    printf("%d\n", temp->key);
    /*
    Insert(head,2);

    */
   
  

    return 0;
}