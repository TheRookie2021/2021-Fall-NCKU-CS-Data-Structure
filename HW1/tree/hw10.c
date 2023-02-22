#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 50
int arr[MAX_LENGTH];

typedef struct {
    int key;
    struct Node* lchild;
    struct Node* rchild;
}Node;

Node* BT;
Node* stack[MAX_LENGTH];//stack that record the traversal
int top=-1;
void push(Node* node){
    stack[++top]=node;
};
Node* pop (){
    if(top==-1){
        printf("empty!");
        return NULL;
    }
   return stack[top--];
};

void MakeTree(int num){
    Node* cur;
    Node* newnode;
    newnode=(Node*)malloc(sizeof(Node));
    newnode->lchild=NULL;
    newnode->rchild=NULL;    
    BT=newnode;
    cur=BT;
    cur->key=arr[0];
    push(cur);push(cur);
    //printf("%d ",cur->key);
    //store arr into BT tree
    for(int i=1;i<num;i++){
        if(arr[i]==-1){//pop to create rchild
    //printf("arr[i]==-1, pop \n");
            cur=pop();
            if(arr[i+1]==-1){
                cur=pop();
                i++;
                if(arr[i+1]==-1){
                    if(top=-1)break;
                    cur=pop();}
            }else{
                newnode=(Node*)malloc(sizeof(Node));//setup 
                    newnode->key=arr[++i];
                    newnode->lchild=NULL;
                    newnode->rchild=NULL;
                cur->rchild=newnode;
                cur=cur->rchild;
                push(cur);
                
    //printf("cur->rchild==NULL\n");
    //printf("%d ",cur->key);
                }
        /*if(cur->rchild!=NULL)
            cur=pop();
*/        }else{//create lchild            
            newnode=(Node*)malloc(sizeof(Node));//setup 
                newnode->key=arr[i];
                newnode->lchild=NULL;
                newnode->rchild=NULL;
            if(cur->lchild==NULL){
                cur->lchild=newnode;//link
                cur=cur->lchild;//move
                push(cur);//record
                
    //printf("cur->lchild==NULL\n");
    //printf("%d ",cur->key);
            }else
            if(cur->rchild==NULL){
                cur->rchild=newnode;//link
                cur=cur->rchild;//move
                push(cur);//record
    //printf("cur->rchild==NULL\n");
    //printf("%d ",cur->key);
            }
        }
    }

};
void preorder(int num){
    Node* cur=BT;
    top=-1;
    push(cur);
    //printf("push cur:%d \n",cur->key);

    for(int i=0; i<num&&stack[top]!=NULL;i++){
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
    Node* temp;
    Node* left;
    Node* right;
    if(cur==NULL)return;
    
        left=cur->lchild;
        right=cur->rchild;
        temp=left;
        left=right;
        right=temp;
        cur->lchild=left;
        cur->rchild=right;
        swaptree(left);
        swaptree(right);    
    
};
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
            printf("%d ",cur->key);
            cur=cur->rchild;
        } 
        
    
    }
};
int main(){
    int num_of_input;
    scanf("%d",&num_of_input);
    
    for(int i=0; i<num_of_input; i++)
        scanf("%d",&arr[i]);
        /*
    for(int i=0; i<num_of_input; i++)
        printf("%d ",arr[i]);
*/  
    MakeTree(num_of_input);
    
    swaptree(BT);
    preorder(num_of_input);
    printf("\n");
    inorder(num_of_input);
    
    printf("\n");
    return 0;
}