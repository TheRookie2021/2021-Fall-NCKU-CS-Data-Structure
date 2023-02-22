#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int adj_v;
    int weight;
    struct Node * next; 
}Node;

typedef struct{
    struct Node *head; 
}List;

typedef struct{
    int size;
    struct List* arr;
}Graph;

Node* CreatNode(int v, int weight);
Graph* CreatGraph(int size);
void AddEdge(Graph* graph,int u,int v, int weight);
void PrintGraph(Graph* graph);

int main(){
   Graph *graph=CreatGraph(5);
    AddEdge(graph, 0, 1,10);
    AddEdge(graph, 0, 4,20);
    AddEdge(graph, 1, 2,30);
    AddEdge(graph, 1, 3,40);
    AddEdge(graph, 1, 4,50);
    AddEdge(graph, 2, 3,60);
    AddEdge(graph, 3, 4,70);
    /*
    */
    PrintGraph(graph);
    return 0;
}

Node* CreatNode(int v, int weight){
    Node * newnode= malloc(sizeof(Node));
    newnode->adj_v=v;
    newnode->weight=weight;
    newnode->next=NULL;
    return newnode;

};

Graph* CreatGraph(int size){
    Graph* graph= malloc( sizeof(Graph));
    graph->arr= malloc(size* sizeof(List));
    graph->size=size;

    List* temp_arr=graph->arr;
    for(int i=0;i<size;i++){
        (temp_arr+i)->head=NULL;
        //printf("creatgraph arr:%d %d\n",i,(temp_arr+i)->head);
    }
    return graph;

};
void AddEdge(Graph* graph,int u,int v, int weight){//by insert behind the head!
    //one direction
    List * temp_arr= graph->arr;
    Node* newnode =CreatNode(v,weight);
    newnode->next=temp_arr[u].head;
    temp_arr[u].head=newnode;

    //Node* temp=(temp_arr+u)->head;
    // printf("head of u= %d, v: %d weight: %d\n",u,temp->adj_v,temp->weight);
    
    //the other
    Node* othernode=CreatNode(u,weight);
    othernode->next=temp_arr[v].head;
    temp_arr[v].head=othernode;
    
    //temp=(temp_arr+v)->head;
    //printf("head of v= %d, u: %d weight: %d\n",v,temp->adj_v,temp->weight);
};

void PrintGraph(Graph* graph){
    List* temp_arr=graph->arr;
    Node* cur;
    for(int i=0;i<graph->size;i++){
        cur=temp_arr[i].head;
        if (cur!=NULL)
            printf("the #%d \n",i);
        while (cur!=NULL){
            printf("\tv: %d  weight: %d\n",cur->adj_v,cur->weight);
            cur=cur->next;
        }

    }

};