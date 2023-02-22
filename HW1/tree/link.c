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


int main(){
    Node* headnode;
    Node* newnode=(Node*) malloc (sizeof(Node));
    newnode->c='a';
    push(newnode);
    printf("%c",newnode->c);
    
    Node* newnode2=(Node*) malloc (sizeof(Node));
newnode2=pop();printf("%c",newnode2->c);

    return 0;
}