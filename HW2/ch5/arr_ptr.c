#include <stdio.h>
typedef struct{
    int key;
}element;

int main(){
    element arr[5];
    for(int i=0;i<5;i++){
        arr[i].key=i;
    }
    
    element *ptr;
    ptr=CreateMinHeap();
    
    printf("%d ", ptr);
    printf("%d ",*ptr);
    printf("%d ",(ptr+2)->key);

}
element* CreateMinHeap(){
    element minheap[10]={0};
    printf("construction done\n");
    
    return &minheap[0];
};