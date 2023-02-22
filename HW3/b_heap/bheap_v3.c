#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#define MAX 10
typedef struct{
    int data;
    int deg;
    struct Element *child,*sib; 
}Element;

typedef struct{
    struct Element* root;
    struct Element* prev_sib;
    bool table[MAX];
}Bheap;

Bheap* initialize(){
   Bheap* new=malloc(sizeof(Bheap));
   new->root=NULL;
   for(int i=0;i<MAX;i++)
    new->table[i]=false;
   return new; 
}
void printheap(Bheap*heap){
    printf("printheap\n");
    Element*cur=heap->root;//point to the min root
    Element*orig=cur;
    
    for(int i=0;i<MAX;i++)
        printf("%d ",heap->table[i]);
    
    printf("\n");

    int i=10;
    do{
        printf("%d ",cur->data);
        printf("\t%d\n",cur);
        cur=cur->sib;

    }while(i-->0);
    
    printf("\n");

    
}
void printdeg(Bheap*heap){
    printf("printdeg\n");

    Element*cur=heap->root;//point to the min root
    Element*orig=cur;

    do{
        printf("%d ",cur->deg);
        cur=cur->sib;
    }while(cur!=orig);

    printf("\n");
    
}

Element* meld(Element* a,Element* b){//management of binominal tree itself
    printf("meld1\n");
    if(a==NULL)return b;
    if(b==NULL)return a;
    

    if(a->data > b->data){//let a always be the smallest
      //  printf("before swap: %d \n",b);
        Element* temp=a;
        a=b;
        b=temp;//swap
    }
    

    Element* sib0=a->child;
    if(a->child==NULL){
    printf("meld2\n");
        a->child=b;
        b->sib=b;
    }
    else{
        printf("meld3\n");

        Element* a_child=a->child;
        Element* sib0=a_child->sib;
        a_child->sib=b;
        b->sib=sib0;
        a->child=b;


    }
    ++a->deg;
   return a;
};

void bheap_union(Bheap* heap, Element* a,Element* b){//management of heap table
    printf("bheap_union\n");
    if( heap->root==NULL){//empty heap situation
        heap->root=a;
        heap->table[a->deg]=true;
        return;
    }

    int old_deg=a->deg;
    Element* temp=meld(a,b);
    a=NULL;b=NULL;

    if(heap->table[temp->deg]==false){//end condition of recursion
        if(temp->deg>heap->root){

        }else{

        }

        
        heap->table[temp->deg]=true;
    }

    else{//repeated degree 1.find the existed one 2. union them again
        Element* cur=heap->root;
        Element* orig=cur;
        do{

            if(cur->deg==temp->deg&&cur!=temp)break;
            else cur=cur->sib;

        }while(cur!=orig);
        bheap_union(heap,temp,cur);
    }
    heap->table[old_deg]=false;
    
};

void insert(Bheap*heap,int n){ 
    Element* new=malloc(sizeof(Element));
    new->data=n;
    new->deg=0;
    new->child=NULL;
    new->sib=new;//circular linked list struct

    if(heap->table[0]==false){
        if(heap->root==NULL)//empty heap
        {
            heap->root=new;
            heap->prev_sib=new;
        }   
        else
        {
            Element* cur=heap->root;
            Element* next=cur->sib;
            Element* prev=heap->prev_sib;
            
            new->sib=cur->sib;
            cur->sib=new;
        }
        heap->table[0]=true;
            
    }else{
        bheap_union(heap,new,NULL);
    }
      printheap(heap);
  
   // printdeg();
};

int deletemin(Bheap* heap){
//scan the heap arr once: O(MAX)
    printf("delete\n");
    if(heap->root==NULL)return 0;
    Element* cur=heap->root;
    int min=cur->data;
    Element* child=cur->child;
    Element* orig=child;//set end point for circular linked list

    //remove connection of min root 
    Element* prev,*next;
    next=cur->sib;
    prev=cur;
    if(cur!=cur->sib)
        while(prev->sib!=cur) prev=prev->sib;
    prev->sib=next;
    cur=NULL;
    //find the min again
    heap->root=next;
    Element* newmin=heap->root;
    int find=newmin->data;
    Element* ancher=newmin;
    newmin=newmin->sib;
    while(newmin!=ancher){
        if(find>newmin->data)
        {
            find=newmin->data;
            heap->root=newmin;
        }
    }

    child=child->sib;
    while(child!=orig){
        bheap_union(heap,child,NULL);
        child=child->sib;
    }

    return min;
};

int main(){
   /*
   */
    srand(time(NULL));
    int x=rand()%100;
    Bheap* heap=initialize();   
    for(int i =0;i<15;i++){
        printf("%d ",i+1);
        if(x!=0)
        insert(heap,i+1);

        x=rand()%100;

    }
    Element* head=heap->root;
    printheap(heap);
  
    printf("%d\n",head->data);
  
  
  
    return 0;
}