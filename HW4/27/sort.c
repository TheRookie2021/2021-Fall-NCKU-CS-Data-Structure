#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MAX 5000
void printarr(int *arr, int num)
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

void permute(int a[], int n)
{
    /* random permutation generator */
    int i, j;
    int temp;
    for (i = n; i >= 2; i--)
    {
        j = rand() % i + 1;
        swap(&a[j], &a[i]);
    }
}

void insertion_sort(int *arr, int num)
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

void quick_sort(int *arr, int left_index, int right_index)
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
            pivot = median_of_tree((arr)[left_index], (arr)[(left_index + right_index) / 2], (arr)[right_index]);
            mid = (left_index + right_index) / 2;
        }
        else
        {
            pivot = median_of_tree((arr)[left_index], (arr)[(left_index + right_index) / 2 + 1], (arr)[right_index]);
            mid = (left_index + right_index) / 2 + 1;
        }
        int pivot_ind;
        int L, R;
        L = left_index;
        R = right_index;
        if (pivot == (arr)[left_index])
        {
            pivot_ind = left_index;
        }
        else if (pivot == (arr)[mid])
        {
            pivot_ind = mid;
        }
        else if (pivot == (arr)[right_index])
        {
            pivot_ind = right_index;
        }

        int i = L;
        // start sorting
        do
        {
            if (pivot < (arr)[i])
            {
                temp[R--] = (arr)[i];
            }
            else if (pivot >= (arr)[i] && pivot_ind != i)
            {
                temp[L++] = (arr)[i];
            }
            i++;

            // will stop when L==R, where is the place for pivot
        } while (L < R);

        temp[R] = pivot;

        for (i = left_index; i < right_index + 1; i++)
        {
            (arr)[i] = temp[i];
        }

        quick_sort(arr, left_index, R - 1);
        quick_sort(arr, R + 1, right_index);
    }
    // debug note: when processing dynamicly moving index, be aware of the boundry setting in each variable
    //(expecialy looping variable)
}

void mergeing(int *arr, int left_index, int mid, int right_index)
{
    int num = right_index - left_index + 1;
    int l_start = left_index;
    int r_start = mid + 1;
    int r_end = right_index;
    int temp[MAX];

    // notice !! upper bound is not num!!!!!
    for (int i = left_index; i < right_index + 1; i++)
    {
        // if one of them is already done
        if (l_start > mid)
        {
            temp[i] = arr[r_start++];
            continue;
        }
        if (r_start > right_index)
        {
            temp[i] = arr[l_start++];
            continue;
        }

        // if both of them are not done
        if (arr[l_start] <= arr[r_start])
        {
            temp[i] = arr[l_start++];
        }
        else
        {
            temp[i] = arr[r_start++];
        }
    }

    for (int i = left_index; i < right_index + 1; i++)
    {
        arr[i] = temp[i];
    }
}

void rmerge_sort(int *arr, int left_index, int right_index)
{
    if (left_index < right_index)
    {
        int mid_index = (right_index + left_index) / 2;
        rmerge_sort(arr, left_index, mid_index);
        rmerge_sort(arr, mid_index + 1, right_index);
        mergeing(arr, left_index, mid_index, right_index);
        // post order traversal
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
                       // passing copy of arr (do not change the value)
    int temp[MAX];
    for (int i = 0; i < MAX; i++)
        temp[i] = arr[i];
    for (int i = top, counter = 0; i > -1;)
    {
        arr[counter++] = temp[0];
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
    clock_t start, end;
    srand(time(NULL));
    /*
    int test[10];
    for (int i = 0; i < 10; i++)
    {
        test[i] = rand() % 100;
    }
    printf("check out correctness:");
    printf("\nrandom arr\n");
    printarr(test,10);
    insertion_sort(test,10);
    printf("after insertion sort\n");
    printarr(test,10);

    for (int i = 0; i < 10; i++)
    {
        test[i] = rand() % 100;
    }
    printf("\nrandom arr\n");
    printarr(test,10);
    printf("after quick sort\n");
    quick_sort(test, 0, 9);
    printarr(test,10);

    for (int i = 0; i < 10; i++)
    {
        test[i] = rand() % 100;
    }
    printf("\nrandom arr\n");
    printarr(test,10);
    printf("after merge sort\n");
    rmerge_sort(test, 0, 9);
    printarr(test,10);

    for (int i = 0; i < 10; i++)
    {
        test[i] = rand() % 100;
    }
    printf("\nrandom arr\n");
    printarr(test,10);
    printf("after heap sort\n");
    heap_sort(test, 9);
    printarr(test,10);
    */
    //--------------------------------------------------------------------
    int n[5] = {500, 1000, 2000, 3000, 5000};
    for (int trial = 0; trial < 5; trial++)
    {

        printf("let n= %d\n", n[trial]);
        int *arr = malloc(n[trial] * sizeof(int)); // why ? what's different between int arr[]? isn't arr[] also a pointer?
        // ans: arr is always pass by reference!

        double sum_insert = 0, sum_merge = 0;
        int maxtimes = 4;
        for (int time = 0; time < maxtimes; time++)
        {
            /*insertion sort*/
            for (int i = 0; i < n[trial]; i++)
            {
                arr[i] = n[trial] - i;
            }
            switch (time)
            {
            case 0:
                start = clock();
                insertion_sort(arr, n[trial]);
                end = clock();
                
            sum_insert = (double)(end - start) / CLOCKS_PER_SEC;
            printf("insertion sort time:\t %f\n", sum_insert);
                break;

            case 1:
                start = clock();
                quick_sort(arr, 0, n[trial] - 1);
                end = clock();
                
            sum_insert = (double)(end - start) / CLOCKS_PER_SEC;
            printf("quick sort time:\t %f\n", sum_insert);
                break;

            case 2:
                start = clock();
                heap_sort(arr, n[trial] - 1);
                end = clock();
                
            sum_insert = (double)(end - start) / CLOCKS_PER_SEC;
            printf("heap sort time:\t %f\n", sum_insert);
                break;

            case 3:
                start = clock();
                rmerge_sort(arr, 0, n[trial] - 1);
                end = clock();
                
            sum_insert = (double)(end - start) / CLOCKS_PER_SEC;
            printf("merge sort time:\t %f\n", sum_insert);
                break;

            default:
                break;
            }

             /* quick sort
            for (int i = 0; i < MAX; i++)
            {
                arr[i] = i;
            }
            permute(arr,MAX);
            // printf("random arr\n");
            // printarr(arr);
            start = clock();
            quick_sort(arr, 0, MAX - 1);
            end = clock();
            // printf("result\n");
            // printarr(arr);
            printf("quick sort time:\t %f\n", (double)(end - start) / CLOCKS_PER_SEC);
            */

            /*heap sort
            for (int i = 0; i < MAX; i++)
            {
                arr[i] = i;
            }
            permute(arr,MAX);
            // printf("random arr\n");
            // printarr(arr);
            start = clock();
            heap_sort(arr, MAX - 1);
            end = clock();
            // printf("result\n");
            // printarr(arr);
            printf("heap sort time: \t %f\n", (double)(end - start) / CLOCKS_PER_SEC);
            */

            /*merge sort
            for (int i = 0; i < n[trial]; i += 2)
            {
                if (i + 1 < n[trial])
                {
                    arr[i] = i+10 ;
                    arr[i + 1] = i+ 5;
                    // 5,10,7,12,9,14,11,16,13,18,15,
                }
                else
                {
                    arr[i] = i + 1;
                }
            }
            // printf("random arr\n");
            // printarr(arr);
            start = clock();
            rmerge_sort(arr, 0, n[trial] - 1);
            end = clock();
            // printf("result\n");
            // printarr(arr);
            sum_merge += (double)(end - start) / CLOCKS_PER_SEC;
            */
        }

           free(arr);
        // printf("merge sort time:\t %f\n", sum_merge / maxtimes);
        
    }
    return 0;
}
