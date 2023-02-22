#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 100
typedef struct node{
    int key;
    int data;
    int deg;
    bool childcut;//true iff one of its child is cut off (removed); 標記是否失去了一個孩子

    struct node *child,*sib; 
}Node;

Node* heap[MAX];// 省去宣告 Node**的麻煩
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

Node* meld(Node* a,Node* b){//management of binominal tree itself
    //used only when a and b are in same deg
    if(a==NULL)return b;
    if(b==NULL)return a;
    a->sib=a;
    b->sib=b;
    int deg=a->deg;
    if(a->key > b->key){//let a always be the smallest
        Node* temp=a;
        a=b;
        b=temp;//swap
    }
    Node* sib0=a->child;
    if(a->child==NULL){
        a->child=b;
        b->sib=b;
    }
    else{
        //order of the deg: directly linked child deg= a->deg-1
        while(sib0->deg!=0)sib0=sib0->sib;
        Node* a_child=a->child;
        a_child->sib=b;
        b->sib=sib0;
        a->child=b;

    }
    a->deg++;
   return a;
};

void bheap_union(Node* a,Node* b){//management of heap table
    if(a==NULL){
        a=b;
        return;
    }
    int old_deg=(a)->deg;
    //after meld the two binominal trees, change place of root in heap
    Node* temp=meld(a,b);
    int new_deg=temp->deg;

    if(heap[new_deg]==NULL)
    {
        heap[new_deg]=temp;
        heap[old_deg]=NULL;
    }
    else
    {
        bheap_union(heap[new_deg],temp);
        heap[old_deg]=NULL;
    }
};

void insert(int key, int data){ 
    Node* new=malloc(sizeof(Node));
    new->key=key;
    new->data=data;
    new->deg=0;
    new->child=NULL;
    new->sib=new;//circular linked list struct

    if(heap[0]==NULL){
        heap[0]=new;
    }else{
        bheap_union(heap[0],new);
    }
};

Node deletemin(){
//scan the heap arr once: O(MAX)

 //printf("delete\n");
    Node out;
    int min=0;
    int cur;
    for(int i=0;i<MAX;i++)
    {
        if(heap[i]!=NULL){
            min=heap[i]->key;
            out=*(heap[i]);
            cur=i;
            break;
        }
    }
    //find the position of tree with the min key
    for(int i=cur; i<MAX;i++ ){
        if(heap[i]!=NULL){
            if(min==0) min=heap[i]->key;
            else if(min>heap[i]->key){
                min=heap[i]->key;
                out=*(heap[i]);
                cur=i;//position of min
            }
        }
    }
    //printf("%d ",cur);


    //cur is the position of tree with the min key
    if(heap[cur]->child!=NULL){
        Node*cur_sib=NULL,*next_sib=NULL;
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
return out;
};


Node deletenode(int key, int value){

};

void decrease(int key, int value, int amount){
    //find the node with the key
    //



}

int main(){
    initialize();
   /*
   */
    int x;
    for(int i=0;i<20;i++){
        x=rand()%20+1;
        insert(x,i+1);
        printf("%d ",x);

    }
    printf("\n");
    Node temp;
    for(int i=0;i<20;i++){
        temp=deletemin();
        printf("%d %d\n",temp.key,temp.data);
        //printheap();  
        //printdeg();    
    }

    return 0;
}