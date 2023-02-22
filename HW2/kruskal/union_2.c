#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 1000000

typedef struct{
    int vertex;
    int weight;
}check_cycle;
//-------------------------------------------------
void Union(check_cycle* arr,int a,int b);
int Find(check_cycle * arr, int a);
//-------------------------------------------------


int main(){
    //read input
    check_cycle arr[10];
    Initialize_Union(&arr[0],10);
    Union(&arr[0],1,2);
    Union(&arr[0],3,4);
    Union(&arr[0],4,2);
    
    printf("%d %d %d %d",Find(&arr[0],1),Find(&arr[0],2),Find(&arr[0],3),Find(&arr[0],4));

    return 0;
}
//----------------------main-----------------------------------------

void Initialize_Union(check_cycle* arr,int num_v){
    for(int i=0;i<num_v;i++){
        (arr+i)->vertex=-1;//not point to any set
        (arr+i)->weight= 1;
    }
}
void Union(check_cycle* arr,int a,int b){
    if((arr+Find(arr,a))->weight>=(arr+Find(arr,b))->weight){
        (arr+Find(arr,b))->vertex=Find(arr,a);
        (arr+Find(arr,a))->weight++;
    }else{
        (arr+Find(arr,a))->vertex=Find(arr,b);
        (arr+Find(arr,b))->weight++;
    }
};

int Find(check_cycle * arr, int a){
    int i=(arr+a)->vertex;
    if(i==-1) return a;//i==-1: root 
    else {
        int find;
        while(i!=-1){
            find=i;
            i=(arr+i)->vertex;
        }
        return find;
    }
}