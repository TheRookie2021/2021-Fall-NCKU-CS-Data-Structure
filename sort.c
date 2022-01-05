#include <stdio.h>
#include <stdlib.h>
#define MAX 10

void printarr(int *arr)
{

    for (int i = 0; i < MAX; i++)
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

void insertion_sort(int **arr)
{
    int j;
    int temp;
    for (int i = 0; i < MAX; i++)
    {
        for (j = i - 1; j > -1; j--)
        {
            if ((*arr)[j + 1] < (*arr)[j])
            {
                swap(&(*arr)[j + 1], &(*arr)[j]);
            }
            else
                break;
        }
    }
}

int median_of_tree(int a, int b, int c)
{
    if ((a <= b && a >= c) || (a <= c && a >= b))
    {
        return a;
    }
    if ((b <= a && b >= c) || (b <= c && b >= a))
    {
        return b;
    }
    if ((c <= a && c >= b) || (c <= b && c >= a))
    {
        return c;
    }
}

void quick_sort(int **arr, int left_index, int right_index)
{
    // method1. use two arr
    // method2. in place partitioning (only original arr)
    // select pivot: median of three
    if (left_index < right_index)
    {
        // use two arr
        int temp[MAX];
        // median-of-tree
        int pivot;
        int mid;
        if ((left_index + right_index) % 2 == 0)
        {
            pivot = median_of_tree((*arr)[left_index], (*arr)[(left_index + right_index) / 2], (*arr)[right_index]);
            mid = (left_index + right_index) / 2;
        }
        else
        {
            pivot = median_of_tree((*arr)[left_index], (*arr)[(left_index + right_index) / 2 + 1], (*arr)[right_index]);
            mid = (left_index + right_index) / 2 + 1;
        }
        int pivot_ind;
        int L, R;
        L = left_index;
        R = right_index;
        if (pivot == (*arr)[left_index])
        {
            pivot_ind = left_index;
        }
        else if (pivot == (*arr)[mid])
        {
            pivot_ind = mid;
        }
        else if (pivot == (*arr)[right_index])
        {
            pivot_ind = right_index;
        }

        int i = L;
        // start sorting
        do
        {
            if (pivot < (*arr)[i])
            {
                temp[R--] = (*arr)[i];
            }
            else if (pivot >= (*arr)[i] && pivot_ind != i)
            {
                temp[L++] = (*arr)[i];
            }
            i++;

            // will stop when L==R, where is the place for pivot
        } while (L < R);

        temp[R] = pivot;
        printf("temp\n");
        printarr(temp);

        for (i = left_index; i < right_index + 1; i++)
        {
            (*arr)[i] = temp[i];
        }

        printarr((*arr));

        quick_sort(arr, left_index, R - 1);
        quick_sort(arr, R + 1, right_index);
    }
    // debug note: when processing dynamicly moving index, be aware of the boundry setting in each variable
    //(expecialy looping variable)
}

void mergeing(int *arr, int left_index,int mid, int right_index)
{
    int num = right_index-left_index+1;
    int l_start = left_index;
    int r_start = mid+1;
    int r_end = right_index;
    int temp[MAX];
    for(int i=0;i<MAX;i++)
        temp[i]=0;

    // notice !! upper bound is not num!!!!!
    for (int i = left_index; i < right_index+1; i++)
    {
        //if one of them is already done
        if(l_start > mid)
        {
            temp[i] = arr[r_start++];
            continue;
        }
        if (r_start > right_index)
        {
            temp[i] = arr[l_start++];
            continue;
        }

        //if both of them are not done
        if (arr[l_start] <= arr[r_start])
        {
            temp[i] = arr[l_start++];
        }
        else
        {
            temp[i] = arr[r_start++];
        }
    }
    
    printf("temp\n");
    printarr(temp);
    printf("arr\n");
    printarr(arr);
    for (int i = left_index; i < right_index+1; i++)
    {
        arr[i] = temp[i];
    }

    printarr(arr);
}

void rmerge_sort(int *arr, int left_index, int right_index)
{
    if(left_index<right_index)
    {
        int mid_index = (right_index + left_index) / 2;
        rmerge_sort(arr, left_index, mid_index);
        rmerge_sort(arr, mid_index + 1, right_index);
        mergeing(arr, left_index, mid_index, right_index);
        //post order traversal

    }
}

void heapify(int *arr, int top)
{
    // mid heap
    // bottom up order
    // heap: 0~MAX-1
    for (int i = top; i > -1; i--)
    {
        for (int j = i; j <= top;)
        {
            if ((j * 2) + 2 <= top) // parent with 2 children
            {
                if ((arr)[j * 2 + 1] < (arr)[j * 2 + 2]) // left child
                {
                    if ((arr)[j] > (arr)[j * 2 + 1])
                    {
                        swap(&(arr)[j], &(arr)[j * 2 + 1]);
                        j = j * 2 + 1;
                    }
                    else
                        break;
                }
                else if ((arr)[j * 2 + 1] >= (arr)[j * 2 + 2]) // right child
                {
                    if ((arr)[j] > (arr)[j * 2 + 2])
                    {
                        swap(&(arr)[j], &(arr)[j * 2 + 2]);
                        j = j * 2 + 2;
                    }
                    else
                        break;
                }
                else
                    break;
            }
            else if ((j * 2) + 1 <= top) // parent with 1 children
            {
                if ((arr)[j] > (arr)[j * 2 + 1])
                {
                    swap(&(arr)[j], &(arr)[j * 2 + 1]);
                    j = j * 2 + 1;
                }
                else
                    break;
            }
            else // else: leaf nodes, skip.`
                break;
        }

    } // heapify done!
}
void printheap(int *arr, int top)
{
    // passing copy of arr (do not change the value)
    int temp[MAX];
    for (int i = 0; i < MAX; i++)
        temp[i] = arr[i];
    for (int i = top; i > -1;)
    {
        printf("%d ", temp[0]);
        temp[0] = temp[i--];
        // top down heapify
        for (int j = 0; j <= i;)
        {
            if ((j * 2) + 2 <= i) // parent with 2 children
            {
                if (temp[j * 2 + 1] < temp[j * 2 + 2]) // left child
                {
                    if ((temp)[j] > (temp)[j * 2 + 1])
                    {
                        swap(&(temp)[j], &(temp)[j * 2 + 1]);
                        j = j * 2 + 1;
                    }
                    else
                        break;
                }
                else if ((temp)[j * 2 + 1] >= (temp)[j * 2 + 2]) // right child
                {
                    if ((temp)[j] > (temp)[j * 2 + 2])
                    {
                        swap(&(temp)[j], &(temp)[j * 2 + 2]);
                        j = j * 2 + 2;
                    }
                    else
                        break;
                }
                else
                    break;
            }
            else if ((j * 2) + 1 <= i) // parent with 1 children
            {
                if ((temp)[j] > (temp)[j * 2 + 1])
                {
                    swap(&(temp)[j], &(temp)[j * 2 + 1]);
                    j = j * 2 + 1;
                }
                else
                    break;
            }
            else // else: leaf nodes, skip.`
                break;
        }
    }
}
void heap_sort(int *arr, int top)
{
    heapify(arr, top); // O (n log n)
}
void radix_sort()
{
    // bucket sort: catagorize the data
}

void test_arr_cp(int *arr)
{
    for (int i = 0; i < MAX; i++)
    {
        arr[i] = 0;
    }
}
int main()
{

    srand(time(NULL));
    // srand(10);

    // int arr[MAX];
    int arr[MAX]; // = malloc(MAX* sizeof(int)); // why ? what's different between int arr[]? isn't arr[] also a pointer?
    // ans: arr is always pass by reference!
    for (int i = 0; i < MAX; i++)
    {
        arr[i] = rand() % 100;
    }

    /*insertion sort
     printarr(arr);
     insertion_sort(&arr);
     printf("result\n");
     printarr(arr);
    */
    /* quick sort
    printarr(arr);
    quick_sort(&arr, 0, MAX - 1);
    printf("result\n");
    printarr(arr);
    */
    /*heap sort
     printarr(arr);
     heap_sort(arr,MAX-1);
     printf("heapify\n");
     printarr(arr);
     printf("result\n");
     printheap(arr,MAX-1);//why modify the original arr?
     // test_arr_cp(arr);
     // printarr(arr);//why not the same as above heapified arr?
     printf("\nheapify\n");
     printarr(arr);//why not the same as above heapified arr?
    */
    printarr(arr);
    rmerge_sort(arr, 0, MAX - 1);
    printf("result\n");
    printarr(arr);
   /*
   */
    return 0;
}
