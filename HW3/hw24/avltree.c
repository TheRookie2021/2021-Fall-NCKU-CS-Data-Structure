#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    int key;
    int height;     //subtree height, start at 1;
    int BF;         // BF= height(L)-height(R); -1<BF<1;
    struct node *lchild,*rchild,*parent;
}Node;

typedef struct avl{
    int height;
    Node* root;

}AVL; //kind of bts, l<mid<R

AVL* creat_avl(){
    AVL* new=malloc(sizeof(AVL));
    new->height=0;
    new->root=NULL;
    return new;
};
Node* creat_node(int n){
    Node* new=malloc(sizeof(Node));
    new->key=n;
    new->height=1;//height=1
    new->BF=0;
    new->lchild=NULL;
    new->rchild=NULL;
    new->parent=NULL;
    return new;
}
void find_min(AVL *tree){
    Node* cur=tree->root;
    while(cur->lchild!=NULL){
        cur=cur->lchild;
    }
    printf("min: %d, height: %d, bf: %d\n",cur->key,cur->height,cur->BF);
    
}
void find_max(AVL* tree){

    Node* cur=tree->root;
    while(cur->rchild!=NULL){
        cur=cur->rchild;
    }
    printf("max: %d, height: %d, bf: %d\n",cur->key,cur->height,cur->BF);
    
}
void preorder(Node* cur){
    if(cur==NULL)return;

    printf("%d ",cur->key);
    preorder(cur->lchild);
    preorder(cur->rchild);

}
void preorder_height(Node* cur){
    if(cur==NULL)return;

    printf("%d ",cur->height);
    preorder(cur->lchild);
    preorder(cur->rchild);

}


//use when the cur node has two NULL child, bottom up count
void plus_height(AVL* tree, Node*cur){
    if(cur==NULL)return;
    ++cur->height;
    plus_height(tree,cur->parent);
}

void update_height(AVL* tree,Node*root_node,int* max_height){
    if(root_node==NULL || (*max_height)<1 )return;
    if(root_node->lchild==NULL &&root_node->rchild==NULL)
    {
        root_node->height=1;
    }else
    {
        root_node->height=(*max_height);
    }
    --(*max_height) ;

    update_height(tree,root_node->lchild,max_height);
    update_height(tree,root_node->rchild,max_height);

}
/*right rotate on LL
                P bf=2
              /
            C  bf=1    non
          /
        Lc(new)
*/
void LL_rotate(AVL* tree, Node*target){
    Node *mid,*small,*large,*temp;
    large=target;
    mid=target->lchild;
    small=mid->lchild;
    temp=mid->rchild;
    if(tree->root==target){
        tree->root=mid;
    }

    if(large->parent!=NULL)
        large->parent->lchild=mid;
    mid->parent=large->parent;//may be null

    mid->rchild=large;
    large->parent=mid;
    
    mid->lchild=small;
    small->parent=mid;

    large->lchild=temp;
    if(temp!=NULL)
        temp->parent=large;
}

/*LR
                P bf=2, L
              /
            C   bf=-1   S  
              \
              Rc(new)   M
*/
void LR_rotate(AVL* tree, Node*target){
    Node *mid,*small,*large,*temp;
    large=target;
    small=target->lchild;
    mid=small->rchild;

    if(mid->lchild!=NULL)
        temp=mid->lchild;
    else if(mid->rchild!=NULL)
        temp=mid->rchild;

    //mid and small rotate
    
    large->lchild=mid;
    mid->parent=large;

    mid->lchild=small;
    small->parent=mid;

    small->rchild=temp;
    if(temp!=NULL)
        temp->parent=small;

    //right rotate
    LL_rotate(tree,target);

}
/*left rotate on RR
            P bf=-2
              \
               C bf=-1
                  \
                    Rc(new)
*/
void RR_rotate(AVL* tree, Node*target){
    printf("RR\n");
    Node *mid,*small,*large,*temp;
    small=target;
    mid=small->rchild;
    large=mid->rchild;
    temp=mid->lchild;
    if(tree->root==target){
        tree->root=mid;
    }

    if(small->parent!=NULL)
        small->parent->rchild=mid;

    mid->parent=small->parent;//may be null

    mid->rchild=large;
    large->parent=mid;
    
    mid->lchild=small;
    small->parent=mid;

    small->rchild=temp;
    if(temp!=NULL)
        temp->parent=small;   

}

/*
            P bf=-2
              \
               C bf=1
              / 
            Rc(new)
        */
void RL_rotate(AVL* tree, Node*target){
    Node *mid,*small,*large,*temp;  
    small=target;
    large=small->rchild;
    mid=large->lchild;
    

    if(mid->lchild!=NULL)
        temp=mid->lchild;
    else if(mid->rchild!=NULL)
        temp=mid->rchild;

    //large and mid rotate
    small->rchild=mid;
    mid->parent=small;
    
    mid->rchild=large;
    large->parent=mid;

    large->lchild=temp;
    if(temp!=NULL)
        temp->parent=large; 

    RR_rotate(tree,target);
}
//no rotate, LL/RR, LR/RL
void rotate_checker(AVL* tree, Node*cur, int balance){
    //cur's parent, or grandparent would be the node with BF >1 || BF<-1
    
    if(cur==NULL)return;
    if(balance==1)return;
    
    //find the node imbalance
    while(cur->BF<=1 && cur->BF>=-1){
        cur=cur->parent;//end until find the imbalance one
    }

    
    //distiguish ll rr lr rl
    //LL,LR: bf=2
    //  LL: 2,1; LR: 2, -1
    //RR,RL: bf=-2
    //  RR: -2,-1; RL:-2,1
    //p.s: bf=0, balance(lsub=rsub)

    if(cur->BF==2)
    {//L
        if(cur->lchild->BF== -1)
        {//LR
        /*LR
                P bf=2
              /
            C   bf=-1   non  
              \
              Rc(new)

        */
            LR_rotate(tree,cur);
        
        }
        else if(cur->lchild->BF== 1)
        {//LL
        /*LL
                P bf=2
              /
            C  bf=1    non
          /
        Lc(new)
        */
        
            LL_rotate(tree,cur);
        }
    }
    else if(cur->BF== -2)
    {//R

        if(cur->rchild->BF== -1)
        {//RR
        /*
            P bf=-2
              \
          ?     C bf=-1
                  \
                    Rc(new)
        */
            RR_rotate(tree,cur);
        }
        else if(cur->rchild->BF== 1)
        {//RL
        /*
            P bf=-2
              \
         ?      C bf=1
              / 
            Rc(new)
        */
            RL_rotate(tree,cur);
        }
    }
    //update height and bf
    --tree->height;
    int max_h=tree->height;
    update_height(tree,tree->root,&max_h);

    //count bf

}

//premise: height calculated already,top down recursively count
void count_bf(AVL* tree, Node*cur,int* balance){
    if(cur==NULL) return;
    if(cur->lchild==NULL && cur->rchild==NULL)
    {
        cur->BF = 0;    
    
    }else if(cur->rchild==NULL)
    {
        cur->BF = cur->lchild->height - 0;    
    
    }else if(cur->lchild==NULL)
    {
        cur->BF = 0 - cur->rchild->height;    
    
    }else
    {
        cur->BF = cur->lchild->height - cur->rchild->height;
    }

    if(cur->BF>1 ||cur->BF<-1)    
        (*balance)=0;
    count_bf(tree,cur->lchild,balance);
    count_bf(tree,cur->rchild,balance);

};


void insert(AVL*tree, int n){
   
    if(tree->root==NULL)
    {
        tree->root=creat_node(n);
        tree->height=tree->root->height;
    }
    else
    {
        //1. insert like a bst
        //2. count height
        //3. count bf
        //4. rotate if needed
        Node* cur=tree->root;
        int h;
        //1. 2.
        while(cur!=NULL){
            if(cur->key<=n)
            { //new > cur, to right
                if(cur->rchild==NULL){
                    //count height
                    if(cur->lchild==NULL &&cur->rchild==NULL)





                        plus_height(tree,cur);
                    
                    //make connection
                    cur->rchild=creat_node(n);
                    cur->rchild->parent=cur;
                    break;                    
                }else{
                    cur=cur->rchild;
                }
            }
            else
            {//new < cur, to left
                if(cur->lchild==NULL){
                    //count height
                    if(cur->lchild==NULL &&cur->rchild==NULL)
                        plus_height(tree,cur);
                    
                    //make connection
                    cur->lchild=creat_node(n);
                    cur->lchild->parent=cur;

                    break;
                }else{
                    cur=cur->lchild;
                }
            }
        }
        
        //update root info
        tree->height=tree->root->height;

        int balance=1;
        //3. count bf
        count_bf(tree,tree->root,&balance);
    
        preorder(tree->root);
        printf("\n");
        printf("height\n");
        preorder_height(tree->root);
        printf("\n");
        printf("insert %d, balance:%d\n",n,balance);
        //4. rotate if needed
        //if inbalance, it occurs in cur node
        //( its child, its parent and itself )
        rotate_checker(tree,cur,balance);
        printf("after rotate checker\n");
        preorder(tree->root);
        printf("height\n");
        preorder_height(tree->root);
        printf("\n");
    
    }//if tree !=NULL

}


int main(){
    AVL* tree=creat_avl();
    for(int i =0; i<20;i++)
        insert(tree,i+1);
//problem: counting and update height!
    find_max(tree);
    find_min(tree);
    preorder(tree->root);
    return 0;
}
