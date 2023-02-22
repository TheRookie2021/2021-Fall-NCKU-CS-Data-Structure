#include<stdio.h>
#include<stdlib.h>
#define MAX 10
typedef struct{
    int data;
    int deg;
    struct Element *child,*sib; 
}Element;

Element* heap[MAX];// 省去宣告 Element**的麻煩
void initialize(){
    for(int i=0;i<MAX;i++){
        heap[i]=NULL;
    }
}
void printheap(){

    for(int i=0;i<MAX;i++)
        if(heap[i]==NULL)
            printf("0 ");
        else printf("1 ");
    printf("\n");
    
}
void printdeg(){
   
    for(int i=0;i<MAX;i++)
        if(heap[i]==NULL)
            printf("-1 ");
        else printf("%d ",heap[i]->deg);
    printf("\n");
    
}
//1. 傳值得copy -> function 回傳pointer
//2. 傳值得ref -> void function 

Element* meld(Element* a,Element* b){//management of binominal tree itself
    //used only when a and b are in same deg
    if(a==NULL)return b;
    if(b==NULL)return a;
    a->sib=a;
    b->sib=b;
    int deg=a->deg;
    if(a->data > b->data){//let a always be the smallest
        Element* temp=a;
        a=b;
        b=temp;//swap
    }
    Element* sib0=a->child;
    if(a->child==NULL){
        a->child=b;
        b->sib=b;
    }
    else{
        //order of the deg: directly linked child deg= a->deg-1
        while(sib0->deg!=0)sib0=sib0->sib;
        Element* a_child=a->child;
        a_child->sib=b;
        b->sib=sib0;
        a->child=b;

    }
    a->deg++;
   return a;
};

void bheap_union(Element* a,Element* b){//management of heap table
    if(a==NULL){
        a=b;
        return;
    }
    int old_deg=(a)->deg;
    //after meld the two binominal trees, change place of root in heap
    Element* temp=meld(a,b);
    int new_deg=temp->deg;

    if(heap[new_deg]==NULL){
        heap[new_deg]=temp;
        heap[old_deg]=NULL;
    }
    else{
        bheap_union(heap[new_deg],temp);
        heap[old_deg]=NULL;
    }
};

void insert(int n){ 
    Element* new=malloc(sizeof(Element));
    new->data=n;
    new->deg=0;
    new->child=NULL;
    new->sib=new;//circular linked list struct

    if(heap[0]==NULL){
        heap[0]=new;
    }else{
        bheap_union(heap[0],new);
    }
    //printheap();
   // printdeg();
};

int deletemin(){
//scan the heap arr once: O(MAX)

 printf("delete\n");
    int min=0;
    int cur;
    for(int i=0;i<MAX;i++)
    {
        if(heap[i]!=NULL){
            min=heap[i]->data;
            cur=i;
            break;
        }
    }
    //find the position of tree with the min data
    for(int i=cur; i<MAX;i++ ){
        if(heap[i]!=NULL){
            if(min==0) min=heap[i]->data;
            else if(min>heap[i]->data){
                min=heap[i]->data;
                cur=i;//position of min
            }
        }
    }
    //printf("%d ",cur);


    //cur is the position of tree with the min data
    if(heap[cur]->child!=NULL){
        Element*cur_sib=NULL,*next_sib=NULL;
        cur_sib=heap[cur]->child;
        next_sib=cur_sib->sib;
        
        int deg=heap[cur]->deg-1;
        heap[cur]=0;

        //printdeg();
        while(deg>-1){
                //printf("%d %d\n", cur_sib->deg, next_sib->deg);
                int temp=cur_sib->deg;
                if(heap[temp]==NULL)
                    heap[temp]=cur_sib;
                else
                    bheap_union(heap[temp],cur_sib);
    
                //printheap();
                cur_sib=next_sib;
                next_sib=next_sib->sib;
          
            deg--;
        }
 //printheap();

    }else heap[cur]=NULL;
/*

*/
return min;
};

int main(){
   /*
   */
  initialize();
  for(int i=0;i<20;i++)
       insert(i+1);
   
   
  
/*
    Element* cur=heap[4];
    cur=cur->child;
    for(int i=0;i<10;i++){

    printf("%d ",cur->deg);
    cur=cur->sib;
    }
*/
    for(int i=0;i<10;i++){

printf("%d\n",deletemin());
    printheap();  
    //printdeg();
     }

    return 0;
}