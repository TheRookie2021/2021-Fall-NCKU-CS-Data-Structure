#include<stdio.h>
#include<stdlib.h>

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


void insert(Node**head,int data){
    Node* new=malloc(sizeof(Node));
    new->data=data;
    new->lchild=NULL;
    new->rchild=NULL;
    new->shortest=0;

    meld(head,&new);
    
}

int leftestdelete(Node**head){
    int out=(*head)->data;
    if((*head)->lchild!=NULL){
        Node* temp=(*head)->rchild;
        (*head)=(*head)->lchild;
        meld(head,&temp);
    }
    else return 0;
    printf("%d ",out);
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

int main(){
    Node *leftestree=NULL;//must set null!!!!
    insert(&leftestree,1);
    insert(&leftestree,2);
    insert(&leftestree,3);
    insert(&leftestree,4);
    insert(&leftestree,5);
    insert(&leftestree,9);
    
    printf("\n");
    pre(leftestree);
    printf("\n");
    in(leftestree);
    printf("\n");

    for(int i=0;i<5;i++)
        leftestdelete(&leftestree);
    
    printf("\n");
    pre(leftestree);
    printf("\n");
    in(leftestree);
    return 0;
}