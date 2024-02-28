#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define MAX_LEN 10
#define MAX_RECORD 200
#define MAX_MEMORY 30000
#define MAX_UPDATE 10000
#define BIT_VECTOR_ENTRY MAX_MEMORY/32
#define QUERY 1000000
#define NUM_OF_HASH_FUNC 3



// h= 0.693*(m/u)
// let m/u=2
// test: 0.69*2~=1.4 (best case, least p(u))
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
        sum += hash_results[i];
    }
    return sum % MAX_MEMORY;
}

void insert_hash(Element *arr, unsigned int *bloom_filter, char *str)
{
    if (num_of_data == MAX_MEMORY)
    {
        printf("hash table is full\n");
        return;
    }

    // filter algo: var num of hash function
    int filter_index;
    int entry;
    int bit_index;
    for (int i = 0; i < NUM_OF_HASH_FUNC; i++)
    {
        filter_index = hash(i, str);
        entry=filter_index/32;
        bit_index=filter_index%32;
        //the actual index is [(filter_index[i]*32)+(filter_index[i]%32)]
        bloom_filter[entry] |= 1<<bit_index;
    }

    // insert : linear probing
    int index = hash_to_record_index(filter_index);
    while (arr[index].str[0] != '\0')
    { // while not null
        if (strcmp(arr[index].str, "nope") == 0)
        {
            strcpy(arr[index].str, str);
            //printf("%s is inserted\n", arr[index].str);
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
    //printf("%s is inserted\n", arr[index].str);
}

int search_key_hash(Element *arr, unsigned int *bloom_filter, char *str)
{
    // calculate ACIII
    // filter algo: var num of hash function
    int filter_index[NUM_OF_HASH_FUNC];
    int entry;
    int bit_index;
    bool existed = true;
    for (int i = 0; i < NUM_OF_HASH_FUNC; i++)
    {
        filter_index[i] = hash(i, str);
        entry=filter_index[i]/32;
        bit_index=filter_index[i]%32;
        unsigned int flag=1<<bit_index;
        if ( (bloom_filter[entry]  & flag) == 0 )
        {
            existed = false;
            break;
        }
    }
  
    //nope!
    if (existed == false)
    {
        //printf("%s do not exist\n", str);
        return 0;
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
                //printf("search key of str %s in index: %d\n", str, index);
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
        //printf("%s do not exist\n", str);
        return -1;
    }
}

void delete_hash(Element *arr, unsigned int *bloom_filter, char *str)
{
    int key = search_key_hash(arr, bloom_filter,str);
    if (key == -1)
    {
        //printf("%s do not exist\n", str);
        return;
    }
    // arr[key].str[0]='\0';//nope
    strcpy(arr[key].str, "nope");
    //printf("%s is deleted\n", str);
    num_of_data--;
}

int main()
{
    char str[MAX_LEN];
    Element hashtable[MAX_MEMORY];
    unsigned int filter[BIT_VECTOR_ENTRY];

    init_hashtable(hashtable);
    init_filter(filter);

    srand(time(NULL));
    //print_hashtable(hashtable);
    for (int i = 0; i < MAX_RECORD; i++)
    {
        sprintf(str, "%d", rand());  //int to string
        strcmp(hashtable[i].str,str);
    }
    //print_hashtable(hashtable);
    for (int i = 0; i < MAX_UPDATE; i++)
    {
        sprintf(str, "%d", rand());  //int to string
        insert_hash(hashtable, filter, str);
    }

for (int i = 0; i < QUERY; i++)
    {
        sprintf(str, "%d", rand());  //int to string
        search_key_hash(hashtable, filter, str);
    }
    printf("Filter Error: %d, Num of query: %d\n",filter_error,QUERY);
    printf("U: %d, M:%d,  #hash function: %d \n",MAX_UPDATE,MAX_MEMORY,NUM_OF_HASH_FUNC);
    printf("P(u):(filter error/Num of query)= %f\n",((float)filter_error/(float)QUERY));


    return 0;
}
