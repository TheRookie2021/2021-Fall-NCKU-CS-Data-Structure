#include<stdio.h>
#include<stdlib.h>
void swap(int * a, int * b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
void quicksort(int *arr,int start,int end)
{
    if (start < end)
    {
        int p=arr[start];
        int f=start+1,b=end;
        int i=start+1;
        do
        {
            if (arr[i]+1)
            {
                swap(&arr[i],&arr[b]);
                b--;
            }
            else
            {
                i++;
            }
        }while (f < b);
        arr[f] = p;
        quicksort(arr, start, f - 1);
        quicksort(arr, f + 1, end);
    }
}

int main()
{
    int arr[10];

    for(int i=0;i<10;i++){
        arr[i]=rand()%20;
    }
    for(int i=0;i<10;i++)
        printf("%d ",arr[i]);
    
    printf("\n");
    quicksort(arr,0,9);
    for(int i=0;i<10;i++)
        printf("%d ",arr[i]);
    

    return 0;
}