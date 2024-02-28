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

    while(stack[top]!=NULL){

    
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

void postorder(int num){
    Node* cur=BT;
    top=-1;
 
  // Check for empty tree
    if (cur == NULL)
        return;
    
    do
    {
        // Move to leftmost node
        while (cur!=NULL)
        {
            // Push root's right child and then root to stack.
            if (cur->rchild)
                push(cur->rchild);
            push( cur);
 
            // Set root as root's left child
            cur = cur->lchild;
        }
 
        // Pop an item from stack and set it as root    
        cur = pop();
 
        // If the popped item has a right child and the right child is not
        // processed yet, then make sure right child is processed before root
        if (cur->rchild && stack[top] == cur->rchild)
        {
            pop(); // remove right child from stack
            push(cur); // push root back to stack
            cur = cur->rchild; // change root so that the right
                                // child is processed next
        }
        else // Else print root's data and set root as NULL
        {
            if(cur->key!=-1)
            printf("%d ", cur->key);
            cur = NULL;
        }
    } while (top!=-1);
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
    postorder(num_of_input);
    printf("\n");
    return 0;
}