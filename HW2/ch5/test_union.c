#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_SIZE 10000


typedef struct{
    char string[10];
    int a1,b1;
    int a2;
    int a3,b3;
}input;

typedef struct{
    int key;//1 for Find, 2 for Same
    int find;
    bool same;
}output;

void Union(int * arr,int a1, int b1);
int Find  (int * arr,int a1);
bool Same  (int * arr,int a1,int b1);


int main(){
   int arr[10];
    for(int i=0;i<10;i++)arr[i]=-1;
    Union(&arr[0],0,1);
    Union(&arr[0],2,0);

   for(int i=0;i<10;i++)
       printf("%d ",arr[i]);
    
    printf("\nfind 2: %d ",Find(&arr[0],2));
    
    return 0;
}

void Union(int * arr,int a1, int b1){
    int root_a,root_b;
    root_a=Find(arr,a1);
    root_b=Find(arr,b1);
    if(root_a==root_b)return;
    
    if( *(arr+root_a) <= *(arr+root_b)){//if weight of tree a is larger
        //count weight
        *(arr+root_a) = *(arr+root_b)+*(arr+root_a) ;

        *(arr+root_b) =root_a;//let the right variable point to the left one

    }else if( *(arr+root_a) > *(arr+root_b)){//if weight a is smaller
        //count weight
        *(arr+root_b) = *(arr+root_a)+*(arr+root_b);
        
        *(arr+root_a)=root_b;
    }

};
int Find  (int * arr,int a1){
    int i=*(arr+a1) ;
    if(i<0) return a1;

    while (*(arr+i)>-1)
    {
        i= *(arr+i);
    }
    return i;
};
bool Same  (int * arr,int a1,int b1){
    if(Find(arr,a1)==Find(arr,b1))return true;
    else return false;
};