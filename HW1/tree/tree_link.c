#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 50
char string[MAX_LENGTH];

typedef struct Node *Nextnode;
typedef struct{
    char c;
    struct Node * next;
    struct Node * down;
}Node;
typedef struct{
    int ID;
    struct Node* Treehead;
}Tree;

struct Node* stack[MAX_LENGTH];
int top=-1;

void push(struct Node* newnode){
    top++;
    stack[top]=newnode;
};

struct Node* pop(){
    return stack[top--];
}



void read(int ID);

int main(){
    gets(string);
    puts(string);
    read(0);

    return 0;
}

void read(int ID ){
    Tree tree;  tree.ID=ID;
    
    Node* cur=NULL;
    Node* newnode;
    newnode= (Node*) malloc (sizeof(Node));
    //( A ( B ( E ( L , K ),F),C(G),D(H(M),I,J))) : 
    //0 1 2 3 4 5 6 7 8 9 ...
    Node* node;
    Node* next_node;
    Node* down_node;
    newnode->c=string[1];
    tree.Treehead=newnode;
    cur=tree.Treehead;
    for(int i =2;i<strlen(string)-1;i++)//ignore the first and last "( )"
    {

        if(string[i]=='('){//build the new node of i+1 (leftchild) and record the current node into stack
            push(cur);//record the current position
            
            node=(Node*) malloc (sizeof(Node));//build new node(down)
                node->c=string[i+1];
                node->down=NULL;
                node->next=NULL;
            cur->down=node;
            cur=cur->down;
printf("%c ",cur->c);

        }else if(string[i]==','){//when ",", pop and build rightchild,  (A(B,C)) L L R
            cur=pop();
            next_node=(Node*) malloc (sizeof(Node));//build new node(next)
                next_node->down=NULL;
                next_node->next=NULL;
            down_node=(Node*) malloc (sizeof(Node));//build new node(down)
                down_node->c=string[i+1];
                down_node->down=NULL;
                down_node->next=NULL;        
            cur->next=next_node;//connect

            next_node->down=down_node;//connect
            cur=cur->next;
printf("%c -",cur->c);
            cur=cur->down;//when right subtree exists
printf("%c ",cur->c);
        }
            
    }

   printtree(tree);
   
};

void printtree(Tree tree){
    printf("\nID: %d\n",tree.ID);
    
    //traverse: down fist then next
    Node* cur=tree.Treehead;
    //printf("%c\n",cur->c);
    for(int i=0;i<MAX_LENGTH;i++)
        stack[i]=NULL;
    top=-1;    
    push(cur);
    //cur=cur->down;

    for(;top>-1;cur=cur->down){
        
        //push(cur);
        printf(" %c\n",cur->c);
        
        if(cur->down==NULL){
            //printf("cur.down ==null,pop1\n");
            //printf("before pop: %c\n",cur->c);
            //pop();
            cur=pop();//printf("after pop: %c\n",cur->c);
                
            if(cur->next==NULL){
                //printf("cur->next==NULL,pop2\n");
                //printf("before pop: %c\n",cur->c);
                
                cur=pop();//printf("after pop: %c\n",cur->c);
                if(cur->next!=NULL) cur=cur->next;
                else pop();
         
            }else if(cur->next!=NULL){
                //printf("cur->next!=NULL\n");
                
                cur=cur->next;                
               // push(cur);printf("push: %c\n",cur->c);

            }
        }else if(cur->down!=NULL) push(cur);
    }


};