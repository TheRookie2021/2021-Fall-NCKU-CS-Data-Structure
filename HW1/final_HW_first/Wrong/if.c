#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define M 10
int arrop(int* arr, int row,int col){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++)
        printf("%d ",arr[i*col+j]);
        printf("\n");
    }
}

int arr2d(int arr[10][10]){
    for(int i=0;i<10;i++){
        for(int j=0;j<2;j++)
            printf("%d ",arr[i][j]);
        printf("\n");
    }
}
int main(){
    int arr[10][2]={1,2,3,4,5,6,7,8,9,10,
                    1,2,3,4,5,6,7,8,9,10};
    arrop(&arr[0],10,2);

    return 0;
}