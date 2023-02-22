#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#define MAX 10
//circular linked list structure
typedef struct element{
    int data;
    int deg;
    struct element *child,*sib; 
}Element;

typedef struct heap{
    Element* root;//always point to the min 
}Bheap;

Element* creatnode(int n){
    Element* new=malloc(sizeof(Element));
    new->data=n;
    new->deg=0;
    new->child=NULL;
    new->sib=new;//circular
    return new;
};
Bheap* creatheap(){
    Bheap* new=malloc(sizeof(Bheap));
    new->root=0;
    
    return new;
};

Element* meld(Bheap*a,Bheap*b);
Element* bheap_union(Bheap*heap,Bheap*another);
void insert(Bheap*heap,int n);
int deletemin(Bheap* heap);

void printheap(Bheap*heap){
	Element* cur=heap->root;
    Element*orig=cur;
	do{
		printf("%d ",cur->data);
		cur=cur->sib;
	}while(cur!=orig);
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

int main(){
    Bheap* heap=creatheap();
    for(int i=0;i<10;i++)
    insert(heap,1+i);

    return 0;
}

Element* meld(Bheap*a,Bheap*b){
    //just make the two sib in acendent order, and point the head to the min tree
    //a: usually a tree with multiple degree(Bheap) 
    //b: usually a tree with one deg(Binominal tree)
    //1. compare data of bheap a and b
    //2. point to the smaller one
    //3. merge the two bheap in O(1) (let the head->child point to the largest deg child)
    //4. return the head of the meld bheap of a and b 
    if(a->root==NULL)return b->root;
    if(b->root==NULL)return a->root;

    Element* new=malloc(sizeof(Element));
    if(a->root->data<=b->root->data)
        new=a->root;
    else
        new=b->root;
    
    Element* cur_a=a->root;
    Element* cur_b=b->root;
    Element* pre_a=cur_a;
    Element* next_a=cur_a->sib;
    Element* ending_a=a->root;
    Element* smallest_deg,* largest_deg;
    Element * temp=cur_a;
    smallest_deg=cur_a;
    largest_deg=cur_a;

    while(pre_a->sib!=cur_a)pre_a=pre_a->sib;//get previous node(of cur)
    
    do{
        if(smallest_deg->deg>temp->deg)
            smallest_deg=temp;
        
        if(largest_deg->deg<temp->deg)
            largest_deg=temp;
        
        temp=temp->sib;
    }while(temp==cur_a);
    
    //below: to insert b into a in ascendent order
     if(b->root->deg>=largest_deg->deg)
     {
         largest_deg->sib=b->root;
         b->root->sib=smallest_deg;
     }else if(b->root->deg<= smallest_deg->deg)
     {
         largest_deg->sib=b->root;
         b->root->sib=smallest_deg;
     }else{

        do{
            if(cur_a->deg<=cur_b->deg)
            {//deg of cur a is smaller, move forward
                pre_a=cur_a;
                cur_a=next_a;
            }
            else if(cur_a->deg>cur_b->deg)
            {//deg of cur a is larger, insert b before cur a
                pre_a->sib=b->root;
                b->root->sib=cur_a;
                b->root=NULL;
                break;
            }

            //what is the deg of b is larger than all b-degree of a?
            //a is point to min data, not min degree, what is deg of b is smaller?
            next_a=next_a->sib;

        }while(cur_a!=ending_a);

     }

    /*
    */

    if(b->root!=NULL){
        Element* temp=a->root;
        while(temp->deg<temp->sib->deg){
            
            temp=temp->sib;//get the end of circular list
        }
        b->root->sib=temp->sib;
        temp->sib=b->root;

    }
    return new;

};
Element* bheap_union(Bheap*heap,Bheap*another){
    //1. meld
    //2. check degree (check if there is repeated degree)
    //  a. if yes, make the two with same degree one bheap
    //  b. if no,  nothing happen
    //3. return final Bheap

    Element* new=meld(heap,another);
    //heap->root=NULL;//can't not use heap=NULL, because this variable is still needed outside the fucnt
    //another->root=NULL;
    //debug

    bool table[MAX];//for checking degree: true for existed deg 
    for(int i=0;i<MAX;i++){
        table[i]=false;
    }

    Element* cur=new;
    Element* next=cur->sib;
    Element* prev=NULL;
    Element* prev_prev=cur;//in order to merge two binominal tree with same degree
    
     do{
        if(table[cur->deg]==false){
            table[cur->deg]=true;
            prev=cur;
        }else{//carry
            if(prev->data<=cur->data)
            {//let prev be the head
                table[prev->deg]=false;
                ++prev->deg;
                table[prev->deg]=true;
                
                new=prev;
                
                //isolate cur
                prev->sib=next;
                cur->sib=cur;

                //merge prev with cur
                if(prev->child==NULL)
                {
                    prev->child=cur;                   
                }
                else
                {
                    cur->sib=prev->child;
                    prev->child->sib->sib=cur;
                    prev->child=cur;
                    prev->sib=next;
                }

            }else
            {//let cur be the head
                table[cur->deg]=false;
                ++cur->deg;
                table[cur->deg]=true;
                
                new=cur;
                //find prev_prev
                while(prev_prev->sib!=prev){
                    prev_prev=prev_prev->sib;
                }

                //isolate prev
                prev_prev->sib=cur;
                prev->sib=prev;

                //merge cur with prev
                if(cur->child==NULL){
                    cur->child=prev;
                }
                else
                {
                    prev->sib=cur->child;
                    cur->child->sib->sib=prev;
                    cur->child=prev;
                    cur->sib=next;
                }
            }
            
        }
        cur=next;
        next=next->sib;
    }while (cur!=new );
    
             
    return new;
};
void insert(Bheap*heap,int n){
    Element* new=creatnode(n);
    Bheap* temp=creatheap();
    temp->root=new;
    heap->root=bheap_union(heap,temp);
    printheap(heap);
    printdeg(heap);
    
};
int deletemin(Bheap* heap);
