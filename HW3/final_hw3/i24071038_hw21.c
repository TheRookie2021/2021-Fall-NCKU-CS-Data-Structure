#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 5
typedef struct{
    int data;
    int deg;
    struct Element *child,*sib; 
}Element;

Element* heap[MAX];// 省去宣告 Element**的麻煩

typedef struct{
    int data;
    int shortest;
    struct Node *lchild,*rchild; 
}Node;

void initialize(Node**head){
    *head=NULL;
}

void minunion(Node**ra,Node**rb){
    if((*ra)->data> (*rb)->data ){
        Node* temp=(*ra);
        *ra=*rb;
        *rb=temp;
    }

    if((*ra)->rchild==NULL) (*ra)->rchild=*rb;
    else minunion( &(*ra)->rchild,rb);

    Node*L,*R;
    L=(*ra)->lchild;
    R=(*ra)->rchild;

    if((*ra)->lchild==NULL){
        (*ra)->lchild=(*ra)->rchild;
        (*ra)->rchild=NULL;
    }
    else if(L->shortest < R->shortest){
        Node* temp=(*ra)->lchild;
        (*ra)->lchild=(*ra)->rchild;
        (*ra)->rchild=temp;
    }

    R=(*ra)->rchild;
    (*ra)->shortest=((*ra)->rchild==NULL)? 1:R->shortest+1;
}
void meld(Node**ra,Node**rb ){

    if(*ra==NULL) *ra=*rb;
    else if(*rb!=NULL)minunion ( ra,rb );
    *rb=NULL;
}

void leftestinsert(Node**head,int data){
    Node* new=malloc(sizeof(Node));
    new->data=data;
    new->lchild=NULL;
    new->rchild=NULL;
    new->shortest=0;

    meld(head,&new);
}

int leftestdelete(Node**head){
    if(*head==NULL) return 0;
    int out=(*head)->data;
    if((*head)->lchild!=NULL){
        Node* temp=(*head)->rchild;
        (*head)=(*head)->lchild;
        meld(head,&temp);
    }
    else return 0;
    //printf("%d ",out);
    return out;
}

void pre(Node* head){
    if(head==NULL)return;
    printf("%d ",head->data);
    pre(head->lchild);
    pre(head->rchild);
}

void in(Node* head){
    if(head==NULL)return;
    in(head->lchild);
    printf("%d ",head->data);
    in(head->rchild);
}

//----------------------------------up-leftest--------------------------------------------------------

//----------------------------------down-bheap--------------------------------------------------------
void heapinitialize(){
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

Element* bheapmeld(Element* a,Element* b){//management of binominal tree itself
    //used only when a and b are in same deg
    if(a==NULL)return b;
    if(b==NULL)return a;
    a->sib=a;
    b->sib=b;
 //printf("bheapmeld\n");
    int deg=a->deg;
    if(a->data > b->data){//let a always be the smallest
        Element* temp=a;
        a=b;
        b=temp;//swap
    }
    
    //printf("%d %d %d\n",a,b,a->child);
    Element* sib0=a->child;
    if(a->child==NULL){
        a->child=b;
        b->sib=b;
    }
    else{
        //order of the deg: directly linked child deg= a->deg-1
        Element* a_child=a->child;
        Element* sib0=a_child->sib;
        a_child->sib=b;
        b->sib=sib0;
        a->child=b;

    }
    a->deg++;
    /*
    */
   return a;
};

void bheap_union(Element* a,Element* b){//management of heap table

//printf("bheap_union\n");
    if(a==NULL){
        a=b;
        return;
    }

   // printf("%d %d %d\n",*a,*b,(*a)->child);
    int old_deg=(a)->deg;
    //after meld the two binominal trees, change place of root in heap
    Element* temp=bheapmeld(a,b);
    int new_deg=temp->deg;

 //printf("%d %d \n",old_deg,new_deg);
    if(heap[new_deg]==NULL){
        heap[new_deg]=temp;
        heap[old_deg]=NULL;
    }
    else{
        bheap_union(heap[new_deg],temp);
        heap[old_deg]=NULL;
    }
    /*
    */
};

void bheapinsert(int n){ 
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
   // printheap();
   // printdeg();
};

int deletemin(){
    
//scan the heap arr once: O(MAX)

 //printf("delete\n");
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
    if(min==0)return 0;
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
Node* leftest_initialize(int n){
    srand(time(NULL));
    Node* head;
    for(int i=0;i++;i<n){
        leftestinsert(&head,rand());
    }
    return head;
}
void initializeRandomNum(int*arr,int num){
    srand(time(NULL));
    int x=0;
    for(int i=0;i<num;i++){
        *(arr+i)=rand();
    }

}
int leftdelet=0,leftinsert=0,bheapdelet=0,bheapin=0;
void ExpLeft(int *arr,int num){
    Node*left=NULL;
    srand(time(NULL));
    int x=0,index=0;
    //creat random list with n[i] elements
    for(int i=0;i<500000;i++){
        x=rand()%2;
        index=rand()%num;
        if(x==0){
            leftestinsert(&left,*(arr+index));
            leftinsert++;
        }else{
            leftestdelete(&left);
            leftdelet++;
        }
    }
};

void Expbheap(int *arr,int num){
    srand(time(NULL));
    int x=0,index=0;
    heapinitialize();
    //creat random list with n[i] elements
    for(int i=0;i<500000;i++){
        x=rand()%2;
        index=rand()%num;
        if(x==0){
            bheapinsert(*(arr+index));
            bheapin++;
        }else{
            deletemin();
            bheapdelet++;
        }
    }
};

int main(){
    int n[7]={100,500,1000,2000,3000,4000,5000};
    int R1[100],R2[500],R3[1000],R4[2000],R5[3000],R6[4000],R7[5000];
    for(int k=0;k<3;k++){
        initializeRandomNum(&R1[0],n[0]);
        initializeRandomNum(&R2[0],n[1]);
        initializeRandomNum(&R3[0],n[2]);
        initializeRandomNum(&R4[0],n[3]);
        initializeRandomNum(&R5[0],n[4]);
        initializeRandomNum(&R6[0],n[5]);
        initializeRandomNum(&R7[0],n[6]);
        clock_t start[7],end[7];

        double recode_left[7];
        double recode_bheap[7];
        
        for(int i=0;i<7;i++){
            recode_left[i]=0;
            recode_bheap[i]=0;
            
        }

        start[0]=clock();
        ExpLeft(&R1[0],n[0]);
        end[0]=clock();

        start[1]=clock();
        ExpLeft(&R2[0],n[1]);
        end[1]=clock();

        start[2]=clock();
        ExpLeft(&R3[0],n[2]);
        end[2]=clock();

        start[3]=clock();
        ExpLeft(&R4[0],n[3]);
        end[3]=clock();

        start[4]=clock();
        ExpLeft(&R5[0],n[4]);
        end[4]=clock();

        start[5]=clock();
        ExpLeft(&R6[0],n[5]);
        end[5]=clock();

        start[6]=clock();
        ExpLeft(&R7[0],n[6]);
        end[6]=clock();

        for(int i=0;i<7;i++){
            recode_left[i]=(double)(end[i]-start[i])/CLOCKS_PER_SEC;
        }
        //-----------------------------
    

        for(int i=0;i<7;i++){
            start[i]=NULL;
            end[i]=NULL;
        }
        start[0]=clock();
        Expbheap(&R1[0],n[0]);
        end[0]=clock();

        start[1]=clock();
        Expbheap(&R2[0],n[1]);
        end[1]=clock();

        start[2]=clock();
        Expbheap(&R3[0],n[2]);
        end[2]=clock();

        start[3]=clock();
        Expbheap(&R4[0],n[3]);
        end[3]=clock();

        start[4]=clock();
        Expbheap(&R5[0],n[4]);
        end[4]=clock();

        start[5]=clock();
        Expbheap(&R6[0],n[5]);
        end[5]=clock();

        start[6]=clock();
        Expbheap(&R7[0],n[6]);
        end[6]=clock();
        for(int i=0;i<7;i++){
            recode_bheap[i]=(double)(end[i]-start[i])/CLOCKS_PER_SEC;
        }

        printf("left\t bheap\n");
        for(int i=0;i<7;i++){
            
            printf("%f %f\n",recode_left[i],recode_bheap[i]);

        }
    }
    
printf("%d %d %d %d\n",leftdelet,leftinsert,bheapdelet,bheapin);

return 0;
}