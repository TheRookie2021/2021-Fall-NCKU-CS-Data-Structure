#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 10
typedef struct node{
    int data;
    int deg;
    bool childcut;//true iff one of its child is cut off (removed); 標記是否失去了一個孩子
    struct node* parent;
    struct node*child, *lsib,*rsib; 
}Node;

typedef struct bh{
    Node* min;
}Fheap;


Node* creatnode(int n){
    Node* new=malloc(sizeof(Node));
    new->data=n;
    new->deg=0;
    new->rsib=new;
    new->lsib=new;
    new->parent=NULL;
    new->childcut=false;
    new->child=NULL;
    return new;
}
Fheap* creatheap(){
    Fheap* new=malloc(sizeof(Fheap));
    new->min=NULL;
    return new;
};


