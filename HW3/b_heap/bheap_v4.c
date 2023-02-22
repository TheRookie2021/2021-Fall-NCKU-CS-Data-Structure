#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#define MAX 10
typedef struct element{
    int data;
    int deg;
    struct element *child,*sib; 
}Element;

typedef struct heap{
    Element* root;
}Bheap;



Bheap* initialize(){
   Bheap* new=malloc(sizeof(Bheap));
   new->root=NULL;
   return new; 
}
void printheap(Bheap*heap){
	Element* cur=heap->root;
	while(cur!=NULL){
		printf("%d ",cur->data);
		cur=cur->sib;
	}
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
Element* creatnode(int n){
    Element* new=malloc(sizeof(Element));
    new->data=n;
    new->deg=0;
    new->child=NULL;
    new->sib=NULL;
    return new;
};
Bheap* creatheap(){
    Bheap* new=malloc(sizeof(Bheap));
    new->root=0;
    for(int i=0;i<MAX;i++)
    return new;
};

void circularlink(Bheap* heap, Element* node){
    if(heap->root==NULL){
       heap->root=node;
    }else{
        Element* cur=heap->root;
        node->sib=cur->sib;
        cur->sib=node;
        if(cur->data>node->data){
            heap->root=node;
        }
    }
    
};
Element* meld(Bheap* a,Bheap* b){//management of binominal tree itself
    if(a->root==NULL)return b->root;
    if(b->root==NULL)return a->root;

    Element* head;
    Element* ha=a->root;
    Element* hb=b->root;
    Element* tail;

//link in acendent order of deg
    if(ha->deg <= hb->deg){
        head=a->root;
        ha=ha->sib;
    }else{
        head=b->root;
        hb=hb->sib;
    }
    tail=head;
    //linked list of heap struct in ascenedent order 
    while(ha!=NULL && hb!=NULL){
        if(ha->deg<=hb->deg){
            tail->sib=ha;
            ha=ha->sib;
        }else{
            tail->sib=hb;
            hb=hb->sib;
        }
        tail=tail->sib;
    }
    //if one of ha,ha ==NULL, there is only one option left
    tail->sib=(ha!=NULL)? ha:hb;


    return head;
};

 Element* bheap_union(Bheap* heap, Bheap* another){//management of heap table
    Element* new=meld(heap,another);
    heap->root=NULL;
    another->root=NULL;

    if(new==NULL)return NULL;

    Element* prev=NULL;
    Element* cur=new;
    Element* next=new->sib;
    
    while(next!=NULL){
        
        //no repeated deg : move without doing anything
        if(cur->deg!=next->deg ||
           (next->sib!=NULL &&next->sib->deg==cur->deg) ){
               prev=cur;
               cur=next;

        }else{
        //same deg between cur and next
            if(cur->data<next->data){//let cur be parent
                Element*child=cur->child;
                cur->sib=next->sib;
                next->sib=child;
                cur->child=next;
                cur->deg++;
                
                
            }else{//let next be parent
                if(prev==NULL)
                    new=next;
                else
                    prev->sib=next;

                Element*child=next->child;
                cur->sib=next->child;
                next->child=cur;
                next->deg++;
                
                cur=next;
            }
        }
        next=cur->sib;
    }
    return new;
};

void insert(Bheap*heap,int n){ 
    Element* new=creatnode(n);
    Bheap* temp=creatheap();
    temp->root=new;
    heap->root=bheap_union(heap,temp);
};

int deletemin(Bheap* heap){
    if(heap->root==NULL)return 0;
    Element* min=heap->root;
    Element* prev=NULL;
    Element* cur=min;
    Element* next=min->sib;

    while(next!=NULL)
    {
        if(next->data < min->data)
        { //

        }

    }
    return 0;
};

int main(){
    Bheap *heap=creatheap();
    srand(time(NULL));
    int x=rand();
    for(int i=0;i<100;i++){
        x=rand();
        printf("%d ",x);
        if(x>0)
        insert(heap,i+1);

    }

    printheap(heap);

   // printf("\n%d",deletemin(heap));

    return 0;
}