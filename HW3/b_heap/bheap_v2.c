#include<stdio.h>
#include<stdlib.h>
#define MAX 10
typedef struct{
    int data;
    int deg;
    struct Element *child,*sib; 
}Element;
typedef struct{
    Element* root;
}Heap;

Heap* heapInint(){
    Heap* new=malloc(sizeof(Heap));
    new->root=NULL;
    return new;
};
Heap* meld(Heap* a,Heap*b){
    Heap* heap=heapInint();
    if(a->root->data<=b->root->data){
        //a will be the min
       heap=a;
        
    }else{
        //b will be the min
        heap=b;
    }
    //merge circular linked list
    Element* cur_a,*next_a,* cur_b,*next_b;
    cur_a=a->root;
    next_a=cur_a->sib;
    cur_b=b->root;
    next_b=cur_b->sib;
    
    cur_a->sib=next_b;
    cur_b->sib=next_a;


    return heap;
};
Heap* heapUnion(Heap* a,Heap*b){
    if(a->root==NULL)return b;
    if(b->root==NULL)return a;
    Heap* heap=meld(a,b);


};
void insert(Heap* heap, int x){
    Element* new=malloc(sizeof(Element));
    new->data=x;
    new->deg=0;
    new->child=NULL;
    new->sib=new;
    Heap* b=heapInint();
    b->root=new;

    heap=heapUnion(heap,b);
    
};
int deletemin();

int main(){
    Heap* bheap=heapInint();



    return 0;
}