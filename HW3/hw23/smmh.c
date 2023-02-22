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
Root* init_root(){
    Root* new_root=malloc(sizeof(Root));
    new_root->max=NULL;
    new_root->min=NULL;
    return new_root;
}
