#include<stdio.h>
#include<stdlib.h>
#include <time.h>

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
void Topology(Graph* graph,int start);

int main(){
  /*
    clock_t t;
    t = clock();
*/
    int vertices;
    scanf("%d",&vertices);
    Graph *graph=CreatGraph(vertices+1);
    
    int u,v,w;
    int start;
    for(int i=0;i<vertices-1;i++){
        scanf("%d%d%d",&u,&v,&w);
        AddEdge(graph,u,v,w);
    }
    scanf("%d",&start);
    /*
    t = clock() - t;
   double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
   printf("The program took %f seconds to execute", time_taken);
*/
    PrintGraph(graph);
    Topology(graph,start);
    
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

void Topology(Graph* graph,int start){
    int vertices=graph->size;
    int record_length[vertices];
    int counter=vertices;//for ending the traversal
    int stack[vertices];int top=-1;
    int cur;
    for(int i=0;i<vertices;i++)
        record_length[i]=-1;
    record_length[start]=0;

    //traverse
    List* temp_arr=graph->arr;
    Node* temp_node;
    int parent=start;
    temp_node=temp_arr[parent].head;
    while(counter>0){
        //printf("%d ",counter);
        if(temp_node==NULL){
            //pop and change the parent
            if(top==-1)break;
            parent=stack[top--];//pop
           // printf("parent: %d\n",parent);
            temp_node=temp_arr[parent].head;
             continue;
        }
        
        
        cur=temp_node->adj_v;
        if(record_length[cur]==-1){//not recorded 1. directly connected to start 2. undirectly 
            record_length[cur]=record_length[parent]+temp_node->weight;//record
            counter--;

            stack[++top]=cur;
            //printf("push: %d\n",cur);
            temp_node=temp_node->next;

        }else if(record_length[cur]!=-1){//visited
            temp_node=temp_node->next;
        }
    }
    //print
    for(int i=1;i<vertices;i++)
        printf("%d %d\n",i,record_length[i]);

};
    
