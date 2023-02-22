#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 10
typedef struct node{
    int data;
    int deg;
    struct node*child, *lsib, *rsib; 
}Node;

typedef struct bh{
    Node* head;
}Bheap;

Node* creatnode(int n){
    Node* new=malloc(sizeof(Node));
    new->data=n;
    new->deg=0;
    new->lsib=new;
    new->rsib=new;
    new->child=NULL;
    return new;
}
Bheap* creatheap(){
    Bheap* new=malloc(sizeof(Bheap));
    new->head=NULL;
    return new;
};

void merge(Bheap* heap){
//heap.head is already point to the min root 
    Node* cur=heap->head;
    Node* next=cur->sib;
    Node* flag[MAX];
    int table[MAX];
    for(int i=0;i<MAX;i++)
    {
        table[i]=0;
        flag[i]=NULL;
    }
    int num=0;

    while(cur->sib!=heap->head){
        table[cur->deg]++;
        cur=cur->sib;
    }

    int counter=0;
    for(int i=0;i<MAX;i++){
        
        cur=heap->head;

        if(table[i]>1)
        {
            //record the position
            do{
                if(cur->deg==i) flag[counter++]=cur;
                cur=cur->sib;
            }while(cur!=heap->head);
            //
        }
    }



    /*
            do
            {
                
                if(flag[cur->deg]==NULL)
                {//deg of tree is not yet repeated
                    flag[cur->deg]=cur;
                }else
                {//deg repeated: merge and deg++
                    Node* temp=flag[cur->deg];
                    if(temp->data<=cur->data)
                    {//let temp be the root: connect, and deg++, then edit flag[]
                    
                        Node* prev_cur=cur;
                        while(prev_cur->sib!=cur) prev_cur=prev_cur->sib;

                        if(temp->child!=NULL)
                        {
                            Node* prev_temp_child=temp->child;
                            while(prev_temp_child->sib!=temp->child) prev_temp_child=prev_temp_child->sib;

                            prev_cur->sib=cur->sib;//isolate cur

                            prev_temp_child->sib=cur;//connect cur to temp's child
                            cur->sib=temp->child;
                            temp->child=cur;
                            
                        }else
                        {
                            prev_cur->sib=cur->sib;//isolate cur
                            temp->child=cur;//connect cur to temp's child
                        }
                        flag[++temp->deg]=temp;
                        flag[cur->deg]=NULL;
                        table[temp->deg]++;
                        table[cur->deg]-=2;
                                        
                    }else
                    {//let cur be the root
                    
                        Node* prev_temp=temp;
                        while(prev_temp->sib!=temp) prev_temp=prev_temp->sib;
                        if(cur->child!=NULL)
                        {
                            Node* prev_cur_child=cur->child;
                            while(prev_cur_child->sib!=cur->child) prev_cur_child=prev_cur_child->sib;

                            prev_temp->sib=temp->sib;//isolate temp

                            prev_cur_child->sib=temp;//connect temp to cur's child
                            temp->sib=cur->child;
                            cur->child=temp;
                        }else
                        {
                            prev_temp->sib=temp->sib;//isolate temp
                            cur->child=temp;//connect temp to cur's child
                        }
                        flag[++cur->deg]=cur;
                        flag[temp->deg]=NULL;
                        
                        table[cur->deg]++;
                        table[temp->deg]-=2;
                    }
                }
                cur=next;
                next=next->sib;
            }    while(cur->sib!=heap->head);
    //Q: how to end (one round of traverse through cir list does not seems to be enough)?
    //Q: how to set the end condition like, "if there is no repeated deg, end the traverse of circular linked list" ?
    */

};
Node* bheap_union(Bheap* a, Bheap* b){
    Node* new=NULL;
    if(a->head->data<= b->head->data)
    {//let "a" be the root
        new=a->head;
    }else{
        new=b->head;
    }
    Node* prev_a=a->head;
    Node* cur_a=a->head;
    Node* prev_b=b->head;
    Node* cur_b=b->head;
    while(prev_a->sib!=cur_a) prev_a=prev_a->sib;
    while(prev_b->sib!=cur_b) prev_b=prev_b->sib;
    prev_a->sib=cur_b;
    prev_b->sib=cur_a;

    return new;
};
void insert_lazy(Bheap* heap, int n){
    Node* new=creatnode(n);
    if(heap->head==NULL){
        heap->head=new;
        return;
    }
    Node *prev=heap->head->lsib, *cur=heap->head;
    new->lsib=prev;
    new->rsib=cur;
    prev->rsib=new;
    cur->lsib=new;

    if(heap->head->data>new->data)
        heap->head=new;
};
int deletemin(Bheap*heap){
    if(heap->head==NULL)return 0;
    int out=heap->head->deg;
    
    if(heap->head->child==NULL)
    {//root without child
     
        if(heap->head->rsib==heap->head){
            //root without child and sib
            heap->head=NULL;
            return out;
        }else{//root without child, but has sib
            
            Node* cur=heap->head;
            Node* prev=heap->head->lsib;
            
            prev->rsib=cur->rsib;
            heap->head->rsib=heap->head;
            heap->head->lsib=heap->head;
            
            heap->head=prev;
            
            Node* orig=heap->head;
            cur=heap->head;
            //find new min root
            while(cur->sib!=orig){
                
                if(heap->head->data>cur->data)
                    heap->head=cur;
                cur=cur->sib;
            }
            merge(heap);


        }
    }//if(heap->head->child==NULL) 
    
    else{//root with children

        //union and then merge
        //union: bring the children of deleted node into heap level
        //merge: carry if any degree is repeated
        //find new min root
        Node* cur=heap->head;
        Node* prev=heap->head;
        while(prev->sib!=cur) prev=prev->sib;//get prev

        //isolate min binominal tree 
        prev->sib=heap->head->sib;
        heap->head->sib=heap->head;        
        
        //find min
        heap->head=prev;
        do
        {
            if(heap->head->data>prev->data)
                heap->head=prev;
            prev=prev->sib;
        }while(prev->sib!=heap->head);

        //union the child
        cur=cur->child;
        Node* orig=cur;
        Node* next=cur->sib;

        do{
            Bheap* temp=creatheap();
            temp->head=cur;
            heap->head=bheap_union(heap,temp);
            cur=cur->sib;
            merge(heap);

        }while(cur!=orig);

        //carry if repeated
    }
    

return out;

};
void printheap(Bheap* heap){
    Node* cur=heap->head;
    do{
        printf("%d ",cur->data);
        cur=cur->rsib;
    }while(cur!=heap->head);
    printf("\n");
}
void printdeg(Bheap* heap){
    Node* cur=heap->head;
    do{
        printf("%d ",cur->deg);
        cur=cur->rsib;
    }while(cur!=heap->head);
    printf("\n");
}
int main(){
    Bheap* h=creatheap();
    for(int i=0;i<5;i++)
        insert_lazy(h,i+1);
    
    printheap(h);
    printdeg(h);
    //deletemin(h);

    deletemin(h);
    printheap(h);
    printdeg(h);

    return 0;
}