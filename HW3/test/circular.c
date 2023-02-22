#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int data;
    struct Node* link;
}Node;
typedef struct{
    Node* head;
}List;
void printadd(List *list){
    if(list->head==NULL)return;
    Node*cur=list->head;
    do{
        printf("%d ",cur);
        cur=cur->link;

    }  while(cur!=list->head);  

};
void printdata(List *list){
if(list->head==NULL)return;
    Node*cur=list->head;
    int i= 10;
    do{
        printf("%d ",cur->data);
        cur=cur->link;

    }  while(i-->0);  

}
List* creatlist(){
    List *new=malloc(sizeof(List));
    new->head=NULL;
    return new;
}

Node* creatnode(int n){
    Node* new=malloc(sizeof(Node));
    new->data=n;
    new->link=new;
    return new;
};
void circularlink(List *list, int n){
    Node * new=creatnode(n);
    Node * cur=list->head;
    if(cur==NULL){
        list->head=new;
    }else{
        new->link=cur->link;
        cur->link=new;
    }
}

int main(){
    List* list=creatlist();
    for(int i=0;i<5;i++){
        circularlink(list,i);
    }
    printadd(list);
    printf("\n");
    printdata(list);


}