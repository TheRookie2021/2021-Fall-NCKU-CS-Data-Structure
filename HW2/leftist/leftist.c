/*Compare the performance of leftist trees and min heaps under the assumption that the only
operations to be performed are insert and delete min.*/
//leftist trees and min heaps: insert and delete

#include<stdio.h>
#include<stdlib.h>
typedef struct 
{
    int key;
    int shortest_path;
    struct element* lchild;
    struct element* rchild;

}element;


void Insert(element* head, int num);
int  DeleteMin(element* head);
void Meld( element* a_root, element* b_root );
void MinUnion(element* a_root, element* b_root);
void SwapSubTree(element **a,element **b);
element* Initialize(int num){
    element * newnode=malloc(sizeof(element));
    newnode->key=num;
    newnode->shortest_path=1;
    return newnode;
};
void PrintLT(element* head){
    if(head==NULL)return;
    printf("%d ",head->key);
    PrintLT(head->lchild);
    PrintLT(head->rchild);
};

int main(){
    element * head=Initialize(10);
    Insert(head,1);
    Insert(head,3);
    Insert(head,9);
    Insert(head,2);
    /*
    Insert(head,5);
    Insert(head,8);
    Insert(head,7);
    */
    PrintLT(head);
   
   /*
   element* a=Initialize(4);
   element* b=Initialize(6);
   a->shortest_path=19;
   b->shortest_path=10;
   printf("a:%d %d\nb:%d %d\n",a->key,a->shortest_path,b->key,b->shortest_path);
   SwapSubTree(&a,&b);
   element* temp;
    temp=a;
    a=b;
    b=temp;
   printf("a:%d %d\nb:%d %d",a->key,a->shortest_path,b->key,b->shortest_path);
   */

    return 0;
}

void Meld( element* a_root, element* b_root ){
   
    if(a_root==NULL) a_root=b_root;
    else if(b_root!= NULL) MinUnion(a_root,b_root);
    b_root=NULL;

};
void MinUnion(element* a_root, element* b_root){//for Meld
    if(a_root->key > b_root->key)//let a always be the smaller root
    {
        element* temp;
        temp=a_root;
        a_root=b_root;
        b_root=temp;
    }

    if(a_root->rchild==NULL){
        a_root->rchild=b_root;
    }else MinUnion(a_root->rchild,b_root);

    element* temp_L=a_root->lchild;
    element* temp_R=a_root->rchild;

    if(a_root->lchild==NULL){
        a_root->lchild=a_root->rchild;
        a_root=NULL;

    }else if(temp_L->shortest_path < temp_R->shortest_path){
        element* temp;
        temp=a_root;
        a_root=b_root;
        b_root=temp;
        temp=a_root->rchild;
        a_root->shortest_path=(a_root->rchild==NULL)? 
                                1:temp->shortest_path+1;//right child's is alway smaller
    }

};

void Insert(element* head, int num){
    element * newnode= malloc(sizeof(element));
    
    newnode->key=num;
    newnode->shortest_path=0;
    
    Meld(head,newnode);

};
int DeleteMin(element* head){
    int temp=head->key;
    Meld(head->lchild,head->rchild);
    head=head->lchild;
    return temp;

};
void SwapSubTree(element* *a,element* *b){
    element* temp;
    temp=*a;
    *a=*b;
    *b=temp;
};