#include <stdio.h>
#define MAX 10

void printarr (int * arr ,int size){
    for(int i=0;i<size;i++){
        printf("%d ",*(arr+i));
    }
};



int main(){
    int arr[5]={1,2,3,4,5};
    printf("arr[i]");
   for(int i=0;i<5;i++){
        printf("%d ",arr[i]);
    } 
    printf("\n*(arr+i)");
   for(int i=0;i<5;i++){
        printf("%d ",*(arr+i));
    }
    //-------------------------------
    printf("\narr,5\n");
    printarr(arr,5);

    printf("\n&arr,5\n");
    printarr(&arr,5);
    return 0;
}

