#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *lchild, *rchild;
    struct node *parent;
} Node;
typedef struct heap{
    Node* head;
}Heap;
typedef struct root{
    Heap *min, *max;

}Root;

Heap* init_heap(){
    Heap* new_heap=malloc(sizeof(Heap));
    new_heap->head=NULL;
    return new_heap;
}
Node* init_node(int n){
    Node* new_node=malloc(sizeof(Node));
    new_node->data=n;
    new_node->lchild=NULL;
    new_node->rchild=NULL;
    new_node->parent=NULL;
    return new_node;
}
void swap(Node*a,Node*b){
    Node temp=*a;
    *a=*b;
    *b=temp;
};

void insert(Heap* minheap,int n){
    Node* new_node=init_node(n);
    if(minheap->head==NULL)
    {
        minheap->head=new_node;
        return;
    }   
    Node *cur=minheap->head;

    while(cur!=NULL){
        





    }   




}


