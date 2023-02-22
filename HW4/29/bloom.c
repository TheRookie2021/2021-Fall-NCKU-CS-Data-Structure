#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LEN 10
#define MAX_RECORD 50
#define MAX_MEMORY 200
#define MAX_UPDATE 100
#define NUM_OF_HASH_FUNC 4
// h= 0.693*(m/u)
// let m/u=2
// test: 0.69*2~=1.4
//       1. # of h=1
//       2. # of h=2
//       3. # of h=3...
// result: compare the probabilities of filter error
//         between various num of hash func used in bloom filter

typedef struct element
{
    char str[MAX_LEN];
} Element;

int num_of_data = 0;
int filter_error = 0;
void init_hashtable(Element *arr)
{

    for (int i = 0; i < MAX_MEMORY; i++)
    {
        arr[i].str[0] = '\0';
    }
}
void init_filter(int *filter)
{
    for (int i = 0; i < MAX_MEMORY; i++)
    {
        filter[i] = 0;
    }
}
void print_hashtable(const Element *arr)
{
    for (int i = 0; i < MAX_MEMORY; i++)
    {
        printf("key: %d, str: %s\n", i, arr[i].str);
    }
    printf("\n");
}
void print_filter(const int *arr)
{
    for (int i = 0; i < MAX_MEMORY; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}
int hash(int hash_num, char *str)
{
    int sum;
    for (int i = 0; i < strlen(str); i++)
    {
        sum += hash_num * str[i];
    }
    return sum % MAX_MEMORY;
}

int hash_to_record_index(int *hash_results)
{
    int sum;
    for (int i = 0; i < NUM_OF_HASH_FUNC; i++)
    {
        sum *= hash_results[i];
    }
    return sum % MAX_MEMORY;
}

void insert_hash(Element *arr, int *bloom_filter, char *str)
{
    if (num_of_data == MAX_MEMORY)
    {
        printf("hash table is full\n");
        return;
    }

    // filter algo: var num of hash function
    int filter_index[NUM_OF_HASH_FUNC];
    for (int i = 0; i < NUM_OF_HASH_FUNC; i++)
    {
        filter_index[i] = hash(i, str);
        bloom_filter[filter_index[i]] = 1;
    }

    // insert : linear probing
    int index = hash_to_record_index(filter_index);
    while (arr[index].str[0] != '\0')
    { // while not null
        if (strcmp(arr[index].str, "nope") == 0)
        {
            strcpy(arr[index].str, str);
            printf("%s is inserted\n", arr[index].str);
            num_of_data++;
            return;
        }
        if (index != MAX_MEMORY - 1)
        {
            index++;
        }
        else
        {
            index = 0;
        }
    }
    strcpy(arr[index].str, str);
    num_of_data++;
    printf("%s is inserted\n", arr[index].str);
}

int search_key_hash(Element *arr, int *bloom_filter, char *str)
{
    // calculate ACIII
    // filter algo: var num of hash function
    int filter_index[NUM_OF_HASH_FUNC];
    bool existed = true;
    for (int i = 0; i < NUM_OF_HASH_FUNC; i++)
    {
        filter_index[i] = hash(i, str);
        if (bloom_filter[filter_index[i]] != 1)
        {
            existed = false;
            break;
        }
    }

    //nope!
    if (existed == false)
    {
        printf("%s do not exist\n", str);
        return;
    }
    //maybe?
    else
    { 
        // 1. existed, 2. filter error: false positive

        int index = hash_to_record_index(filter_index);
        int max_iter = MAX_MEMORY;
        // Find it
        while (arr[index].str[0] != '\0' && max_iter > 0) // worst case: O(n)
        {                                                 // prob here: it take O(n) to know that str do not exist
            // fix
            if (strcmp(str, arr[index].str) == 0)
            {
                // 1. existed
                printf("search key of str %s in index: %d\n", str, index);
                return index;
            }
            if (index != MAX_MEMORY - 1)
            {
                index++;
            }
            else
            {
                index = 0;
            }
            max_iter--;
        }
        //2. filter error: false positive
        filter_error++;
        printf("%s do not exist\n", str);
        return -1;
    }
}

void delete_hash(Element *arr, int *bloom_filter, char *str)
{
    int key = search_key_hash(arr, bloom_filter,str);
    if (key == -1)
    {
        printf("%s do not exist\n", str);
        return;
    }
    // arr[key].str[0]='\0';//nope
    strcpy(arr[key].str, "nope");
    printf("%s is deleted\n", str);
    num_of_data--;
}

int main()
{
    char str[MAX_LEN];
    Element hashtable[MAX_MEMORY];
    int filter[MAX_MEMORY];
    init_hashtable(hashtable);
    init_filter(filter);

    srand(time(NULL));
    //print_hashtable(hashtable);
    for (int i = 0; i < MAX_MEMORY; i++)
    {
        sprintf(str, "%d", rand()%10000);  //int to string
        insert_hash(hashtable, filter, str);
    }
    //print_hashtable(hashtable);
    for (int i = 0; i < MAX_UPDATE; i++)
    {
        sprintf(str, "%d", rand()%10000);  //int to string
        search_key_hash(hashtable,filter, str);
    }

    printf("Filter Error: %d\n",filter_error);
    printf("U: %d, M:%d,  #hash function: %d \n",MAX_UPDATE,MAX_MEMORY,NUM_OF_HASH_FUNC);
    printf("P(u):(filter_error/MAX_UPDATE)= %f\n",((float)filter_error/(float)MAX_UPDATE));


    return 0;
}
