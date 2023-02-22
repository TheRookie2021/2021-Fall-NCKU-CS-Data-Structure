#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MAX 100

void printarr(int *arr,int num)
{

    for (int i = 0; i < num; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void insertion_sort(int *arr,int num)
{
    int j;
    int temp;
    for (int i = 0; i < num; i++)
    {
        for (j = i - 1; j > -1; j--)
        {
            if ((arr)[j + 1] < (arr)[j])
            {
                swap(&(arr)[j + 1], &(arr)[j]);
            }
            else
                break;
        }
    }
}
int main(){
    int test[10];
    for (int i = 0; i < 10; i++)
    {
        test[i] = rand() % 100;
    }
    printarr(test,10);
    insertion_sort(test,10);
    printf("after insertion sort\n");
    printarr(test,10);

}