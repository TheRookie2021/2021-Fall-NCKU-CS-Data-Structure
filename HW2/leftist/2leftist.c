#include <stdio.h>
#include <stdlib.h>

typedef struct Node* Nodeptr;
typedef struct 
{
    int key;
    int shortest_path;
    struct Node* lchild;
    struct Node* rchild;
}Node;

typedef struct{
    struct  Node * head;
}Leftist;


void Insert(Leftist* tree, int num);
int  DeleteMin(Leftist* tree);
void Meld( Node** a_root,Node** b_root );

void MinUnion( Node** a_root, Node** b_root);

Node* Initialize(int num){
    Node * newnode=malloc(sizeof(Node));
    newnode->key=num;
    newnode->shortest_path=1;
    return newnode;
};
void PrintLT(Node* head){
    Node* cur=head;
    if(cur==NULL){
        printf("return");
        return;
    }
    /*
    */
    printf("%d \n",cur->key);
    if(cur->lchild!=NULL)
        {printf("L");
        PrintLT(cur->lchild);
        }
    if(cur->rchild!=NULL)
    {    printf("R");
        PrintLT(cur->rchild);
    }
};



int main(){
    Leftist *tree=malloc(sizeof(Leftist));
    Insert(tree,1);
    Insert(tree,3);
    Insert(tree,85);
    Insert(tree,2);
    Insert(tree,7);
    Insert(tree,11);
    Insert(tree,22);
    Insert(tree,27);
    
    
    /*   
    //PrintLT(tree->head);
    Node* cur=tree->head;
    printf("%d ",cur->key);
    cur=cur->rchild;
    printf("%d ",cur->key);
    cur=cur->lchild;
    printf("%d ",cur->key);
    cur=cur->lchild;
    
    printf("%d ",cur->key);
    cur=cur->rchild;
    //PrintLT(head);
    Node *head =malloc;
    

    */
    return 0;
}

void Meld( Node** a_root, Node** b_root ){
    printf("meld\n");

    if((*a_root)==NULL){ 
        printf("a root null\n"); 
        (*a_root)=(*b_root);
    }
    else if((*b_root)!=NULL){
        
        MinUnion(a_root,b_root);
    }
    (*b_root)=NULL;
};

void MinUnion( Node** a_root, Node** b_root){
    printf("minunion\n");
    if((*a_root)->key>(*b_root)->key){//keep a root the smaller one
        printf("\tswap\n");
        Node*temp;
        temp=(*a_root);
        (*a_root)=(*b_root);
        (*b_root)=(*a_root);
        
        //now a is the smaller one
    }
    if( (*a_root)->rchild==NULL){
        printf("\trchild==NULL\n");

        (*a_root)->rchild=(*b_root);
        (*b_root)=NULL;
    }  else MinUnion(&(*a_root)->rchild,b_root);

    Node* L=(*a_root)->lchild;
    Node* R=(*a_root)->rchild;
    
    if((*a_root)->lchild==NULL)
    {   printf("\tlchild==NULL\n");
        (*a_root)->lchild=(*a_root)->rchild;
        (*a_root)->rchild=NULL;

    }else if(L->shortest_path < R->shortest_path){
        //if left subset is shorter
        printf("\tleft subset is shorter\n");
        Node* temp;
        temp=(*a_root)->lchild;
        (*a_root)->lchild=(*a_root)->rchild;
        (*a_root)->rchild=temp;
    }
        (*a_root)->shortest_path=((*a_root)->rchild==NULL)?
                                    1 : R->shortest_path+1;

};


void Insert(Leftist* tree, int num){
    printf("insert %d\n",num);
    Node* newnode=malloc(sizeof(Node));
    newnode->key=num;
    newnode->shortest_path=0;
    newnode->lchild=NULL;
    newnode->rchild=NULL;
    Meld(&(tree->head),&newnode);
};
int  DeleteMin(Leftist* tree);
