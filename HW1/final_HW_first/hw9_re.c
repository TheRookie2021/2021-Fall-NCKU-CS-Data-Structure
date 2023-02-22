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

Node* BT=NULL;
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
    
        }else if(cur->lchild==NULL ){//create lchild            
                
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

void postorder(Node*root){
    Node* cur=root;
    push(cur);
    while (top!=-1){
        
        if(cur->lchild!=NULL){
        //printf("cur->lchild!=NULL\n");
            cur=cur->lchild;
            push(cur);
            continue;
        }else
        
        if(cur->lchild==NULL){

            //printf("%d ",top);
            if(top==-1)break;
            cur=pop();
            printf("%d ",cur->key);
        //printf("cur->lchild==NULL\n");
            
            if(cur->rchild!=NULL){
        //printf("cur->lchild==NULL &&cur->rchild!=NULL\n");
                cur=cur->rchild;
                push(cur);
                continue;
            }
            else
            if(cur->rchild==NULL){
        //printf("cur->lchild==NULL &&cur->rchild==NULL\n");

            while(cur!=NULL && cur->rchild==NULL){
                printf("%d ",cur->key);
                cur=pop();
                //printf("pop\n");

                //printf("seg?\n");
            }

                //printf("seg?\n");
            if(cur==NULL) break;
            continue;
            }

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
    preorder(num_of_input);
    printf("\n");
    postorder(BT);
    printf("\n");
    return 0;
}