#include <stdio.h>
#include <stdlib.h>
#define MAX 10
void arra(int *arr){
    for(int i=0;i<MAX;i++)
    {
        *(arr+i)=0;
    }
}
void arrb(int arr[]){
    
    for(int i=0;i<MAX;i++)
    {
        arr[i]=1;
    }
}
void arrc(int **arr){
    
    for(int i=0;i<MAX;i++)
    {
        (*arr)[i]=2;
    }
}

void printarr(int *arr)
{

    for (int i = 0; i < MAX; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(){
    int arr[MAX];
    srand(time(NULL));
    
    for(int i=0;i<MAX;i++)
    {
        arr[i]=rand()%10;
    }
printf("original\n");
    printarr(arr);

    arra(&arr);

printf("arra\n");    
    printarr(arr);

    arrb(&arr);

printf("arrb\n");    
    printarr(arr);

    arrc(&arr);

printf("arrc\n");    
    printarr(arr);
    
    return 0;
}