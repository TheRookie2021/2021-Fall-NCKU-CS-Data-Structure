#include<stdio.h>
#include<stdlib.h>
#define ORDER 3
#define MAX 2    /* 每一節點內至多可放資料筆數 */
#define MIN 1    /* 每一節點內至少需放資料筆數 */
//root's child>=2
//other node's child>=m/2
//at most m-1 keys in a node

typedef struct node {   
	int key[ORDER-1];            
	struct node *child[ORDER];   
} Node;
typedef struct btree{
    Node* root;
    //root's child>=2
}Btree;


void add(Btree* btree, int n);
int get(Btree* btree, int n){
    Node* cur=btree->root;
    
    while(cur!=NULL){

        for(int i=0;i<MAX-1;i++){
            if(cur->key[i]==n)return n;
            if(cur->key[i]> n)
            {// n may be in the left child 
                cur=cur->child[i];
                break;
            }   
        }
        




    }
    return 0;//not found
};
int get_k(Btree* btree, int k);
int remove(Btree* btree, int n);
int remove_k(Btree* btree, int k);

Node* creatnode(int n){
    Node* new=malloc(sizeof(Node));
    for(int i =0;i<ORDER;i++){
        new->child[i]=NULL;
    }
    new->key[0]=n;
    return new;
};

//----------------------------------------
//add node 
void add(Btree* btree, int n){
//1. search n , return or continue
//2. 


};

//get node
int get(Btree* btree, int n);
int get_k(Btree* btree, int k);

//remove node
int remove(Btree* btree, int n);
int remove_k(Btree* btree, int k);

//------------------main------------------
int main(){

    return 0;
}