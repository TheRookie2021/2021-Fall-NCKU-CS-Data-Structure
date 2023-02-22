#include<stdio.h>

void pt2d(int *arr,int size){
    for(int i=0;i<size;i++)
        printf("\n%d ",*(arr+i));
}

int main(){
   int arr[2][2]={1,2,3,4};
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            printf("%d ",arr[i][j]);

    pt2d(&arr,4);
/*
    int *p;
    p=arr;
    for(int i=0;i<4;i++)
        printf("\n%d ",*(p+i));*/

    return 0;
}