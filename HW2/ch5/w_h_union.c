#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_SIZE 10000

typedef struct{
    int key;
    int height;
    int weight;


}element;

void initialize(element *element,int size);
void Height_Union(element * arr,int a, int b);
void Weight_Union(element * arr,int a, int b);
int Find_Root  (element * arr,int a1);
int Collapsing_Find(element * arr,int a);

int main(){
    element arr_w[10];
    initialize(&arr_w,10);
    Weight_Union(&arr_w,1,2);
    Weight_Union(&arr_w,3,1);
    Weight_Union(&arr_w,3,5);
    
    Weight_Union(&arr_w,6,7);
    Weight_Union(&arr_w,1,6);

    for(int i=0;i<10;i++){
        if(arr_w[i].key!=-1)
        printf("i: %d\nkey: %d\nweight: %d\n",i,arr_w[i].key,arr_w[i].weight);
    }

        printf("Collapsing Find 5: %d\n",Collapsing_Find(&arr_w,5));
    printf("Collapsing Find 7: %d\n",Collapsing_Find(&arr_w,7));


    for(int i=0;i<10;i++){
        if(arr_w[i].key!=-1)
        printf("i: %d\nkey: %d\nweight: %d\n",i,arr_w[i].key,arr_w[i].weight);
    }

    return 0;
}

void initialize(element *element,int size){
    for(int i=0;i<size;i++){
        (element+i)->key=-1;
        (element+i)->height=0;
        (element+i)->weight=1;
    }
}
void Height_Union(element * arr,int a, int b){
//new node 
    if((arr+a)->height==0&& (arr+b)->height==0){
        (arr+a)->key=-1;
        (arr+b)->key=a;
        (arr+b)->height=1;
        (arr+a)->height=(arr+b)->height+1;
        return;

    }else if((arr+a)->height==0){
        (arr+a)->key=b;
        (arr+a)->height=1;
        return;
    }else if((arr+b)->height==0){
        (arr+b)->key=a;
        (arr+b)->height=1;
        return;
    }

//two exist tree
    if((arr+a)->height>=(arr+b)->height){
        (arr+b)->key=a;
        return;
    }else{
        (arr+a)->key=b;
        return;
    }
    
};

void Weight_Union(element * arr,int a, int b){
    // two new node or two trees with same weight
    int root_a=Find_Root(arr,a);
    int root_b=Find_Root(arr,b);
    

    if((arr+root_a)->weight==1 &&(arr+root_b)->weight==1){
        (arr+b)->key=a;
        (arr+root_a)->weight+=(arr+root_b)->weight;
        return;
    }else if((arr+root_a)->weight == (arr+root_b)->weight){
        (arr+b)->key=a;
        (arr+root_a)->weight+=(arr+root_b)->weight;
        return;
    }
    else //tree with different weight 
    if((arr+root_a)->weight> (arr+root_b)->weight){
        (arr+b)->key=a;
        (arr+root_a)->weight+=(arr+root_b)->weight;
        return;   
    }else if((arr+root_a)->weight < (arr+root_b)->weight)
    {
        (arr+a)->key=b;
        (arr+root_b)->weight+=(arr+root_a)->weight; 
        return;
    }
};


int Find_Root  (element * arr,int a1){
    int i=(arr+a1)->key ;
    if(i==-1) return a1;

    while ((arr+i)->key!=-1)
    {
        i=(arr+i)->key;
    }
    return i;
    
};
int Collapsing_Find(element * arr,int a){
    int temp[MAX_SIZE];
    int counter=0;
    int i,find;
    for(i=a;i!=-1;counter++){
        temp[counter]=i;
        find=i;
        i=(arr+i)->key;
    }

    for(int j=0;j<counter-1;j++){
        (arr+temp[j])->key=find;
    }
    return find;
};

