#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 1000

typedef struct {
    int key;
    struct Node* lchild;
    struct Node* rchild;
}Node;
int arr[MAX_LENGTH];
Node* BT;

Node* stack[MAX_LENGTH];//stack that record the traversal
int top=-1;
void push(Node* node){
    stack[++top]=node;
};
Node* pop (){
   return stack[top--];
};

void MakeTree(int num){
    Node* cur;
    Node* newnode;
    newnode=(Node*)malloc(sizeof(Node));
    newnode->lchild=NULL;
    newnode->rchild=NULL;    
    BT=newnode;
    BT->key=arr[0];
    cur=BT;
    push(cur);
    //printf("%d ",cur->key);
    //store arr into BT tree
    for(int i=1;i<num;i++){
        if(arr[i]==-1){//pop to create rchild
            if(top==-1)break;

            newnode=(Node*)malloc(sizeof(Node));//setup 
                    newnode->key=arr[i];
                    newnode->lchild=NULL;
                    newnode->rchild=NULL;
            if(cur->lchild==NULL) cur->lchild=newnode;
            else if(cur->rchild==NULL) cur->rchild=newnode;
            cur=pop();
            continue;
    
        }else  if(cur->lchild==NULL ){//create lchild            
                
            newnode=(Node*)malloc(sizeof(Node));//setup 
                    newnode->key=arr[i];
                    newnode->lchild=NULL;
                    newnode->rchild=NULL;
                
                    cur->lchild=newnode;//link
                    cur=cur->lchild;//move
                    push(cur);//record
            continue;

        }else if(cur->rchild==NULL){
            newnode=(Node*)malloc(sizeof(Node));//setup 
                    newnode->key=arr[i];
                    newnode->lchild=NULL;
                    newnode->rchild=NULL;

                    cur->rchild=newnode;//link
                    cur=cur->rchild;//move
                    push(cur);//record
        }
    }
};

void preorder(int num){
    Node* cur=BT;
    top=-1;
    push(cur);
    //printf("push cur:%d \n",cur->key);

    for(int i=0; i<num&&stack[top]!=NULL;i++){
        if(cur->key!=-1)
        printf("%d ",cur->key);
        if(cur->lchild==NULL){
            //printf("pop cur:%d \n",cur->key);
            cur=pop();
//printf("2 cur: %d cur->lchild==NULL\n",cur->key);

            if(cur->rchild==NULL&&cur->lchild==NULL){
//printf("2.1 cur:%d cur->rchild==NULL\n",cur->key);
                //printf("pop cur:%d \n",cur->key);
                if(top==-1)break;//!!!最後一終止條件 當stack==empty 無法pop
                cur=pop();
                cur=cur->rchild;
                push(cur);
                //printf("push cur:%d \n",cur->key);
            }else if(cur->rchild!=NULL){
//printf("2.2  cur:%d cur->rchild!=NULL\n",cur->key);
                cur=cur->rchild;
                
                push(cur);
                //printf("push cur:%d \n",cur->key);
                
            }
        }else
        if(cur->lchild!=NULL){
            //printf("3. cur:%d cur->lchild!=NULL\n",cur->key);
            cur=cur->lchild;
            push(cur);
            //printf("push cur:%d \n",cur->key);
        }
    }
};

void swaptree(Node* cur){
    Node* left;
    Node* right;
    if(cur==NULL)return;
    else{
        left=cur->lchild;
        right=cur->rchild;
        
        cur->lchild=right;
        cur->rchild=left;
        swaptree(cur->lchild);
        swaptree(cur->rchild);    
    }
};
/* original one
void inorder(int num){
    Node* cur=BT;
    Node* left;
    Node* right;
    top=-1;
    //left mid right
    //printf("%d",cur->key);

    for(int i=0;i<num;i++){
        push(cur);
        if (cur->lchild!=NULL)
        {
            cur=cur->lchild;
            continue;
        }else
        if(cur->lchild==NULL)
        {//pop and print
            if(top==-1)break;
            cur=pop();
            if(cur->key!=-1)
            printf("%d ",cur->key);
        }

        if (cur->rchild!=NULL)
        {
            cur=cur->rchild;
            continue;
        }else        
        if (cur->rchild==NULL)
        {//pop and print and goto right sib
            if(top==-1)break;
            cur=pop();
            if(cur->key!=-1)
            printf("%d ",cur->key);
            cur=cur->rchild;
        } 
        
    
    }
};
*/

void inorder(Node* root){
    Node* cur=root;
    top=-1;
    push(cur);
    while(stack[top]!=NULL){

        if (cur->lchild!=NULL)
        {
            cur=cur->lchild;
            push(cur);
            continue;
        }else
        if(cur->lchild==NULL)
        {//pop and print
            if(top==-1)break;
            cur=pop();

            if(cur->key!=-1)
            printf("%d ",cur->key);

            if (cur->rchild!=NULL)
            {
                cur=cur->rchild;
                push(cur);
            }else        
            if (cur->rchild==NULL)
            {//pop and print and goto right sib
                if(top==-1)break;
                cur=pop();

                if(cur->key!=-1)
                printf("%d ",cur->key);

                cur=cur->rchild;
                push(cur);
        } 
        
        }
    
    }
};

void pre_recur(Node* cur){
    if(cur==NULL) return;
    else{
    if(cur->key!=-1)
        printf("%d ",cur->key);
    pre_recur(cur->lchild);
    pre_recur(cur->rchild);
}
}
void in_recur(Node* cur){
    if(cur==NULL) return;
    else{    
    in_recur(cur->lchild);
    if(cur->key!=-1)
        printf("%d ",cur->key);
    in_recur(cur->rchild);
    }
}
    

int main(){
    int num_of_input;
    scanf("%d",&num_of_input);
    
    for(int i=0; i<num_of_input; i++)
        scanf("%d",&arr[i]);
        /*
    for(int i=0; i<num_of_input; i++)
        printf("%d ",arr[i]);
        
    printf("\n");
*/  
    MakeTree(num_of_input);
    
    swaptree(BT);
    //preorder(num_of_input);
    pre_recur(BT);
    printf("\n");
    inorder(BT);
    //in_recur(BT);
    printf("\n");
    return 0;
}