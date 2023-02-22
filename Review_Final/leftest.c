#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    int shortest;
    struct node* left,*right;
}Node;

typedef struct leftest{
    Node* root;
}Leftest;

Leftest* create_leftest()
{
    Leftest* new=malloc(sizeof (Leftest));
    new->root=NULL;
    return new;
}
Node * create_Node(int data)
{
    Node* new=malloc(sizeof(Node));
    new->data=data;
    new->shortest=0;
    new->left=NULL;
    new->right=NULL;
    return new;
}

void insert(Leftest *tree, int data)
{
    if(tree->root==NULL)
    {
        tree->root=create_Node(data);
        return;
    }
    
    Node* cur=tree->root;
        

}


int main()
{

    return 0;
}