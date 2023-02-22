#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct  element
{
    char str[MAX];
}Element;

int num_of_data=0;
void init_hashtable(Element *arr){

    for(int i=0;i<MAX;i++)
    {
        arr[i].str[0]='\0';
    }
}
void print_hashtable(const Element* arr)
{
    for(int i = 0 ; i < MAX ; i ++)
    {
        printf("key: %d, str: %s\n",i ,arr[i].str);
    }

}
 
void insert_hash(Element *arr, char* str)
{
    if (num_of_data==MAX)
    {
        printf("hash table is full\n");
        return;
    }
    
    //hash algo
    int sum;
    for(int i=0;i<strlen(str);i++){
        sum+=str[i];
    }
    int index=sum%MAX;
    

    //insert 
    while(arr[index].str[0] !='\0')
    {//while not null
        if(strcmp(arr[index].str,"nope")==0)
        {
            strcpy(arr[index].str,str);
            printf("%s is inserted\n",arr[index].str);
            num_of_data++;
            return;
        }
        if(index!=MAX-1)
        {
            index++;
        }
        else
        {
            index=0;
        }
       
    }
    strcpy(arr[index].str,str);
    num_of_data++;
    printf("%s is inserted\n",arr[index].str);
}


int search_key_hash(Element *arr, char* str)
{
    //calculate ACIII
    int sum;
    for(int i=0;i<strlen(str);i++){
        sum+=str[i];
    }
    int index=sum%MAX;
    int max_iter=MAX;
    //Find it
    while(arr[index].str[0]!='\0'&&max_iter>0)//worst case: O(n)
    {//prob here: it take O(n) to know that str do not exist
        //fix
        if(strcmp(str,arr[index].str)==0)
        {
            printf("search key of str %s in index: %d\n",str,index);
             return index;
        }
        if (index != MAX - 1)
        {
            index++;
        }
        else
        {
            index=0;
        }
        max_iter--;
    }
    printf("%s do not exist\n",str);
    return -1;
}


void delete_hash(Element *arr, char *str)
{
    int key=search_key_hash(arr,str);
    if(key==-1)
    {
        printf("%s do not exist\n",str);
        return;
    }
    //arr[key].str[0]='\0';//nope
    strcpy(arr[key].str,"nope");
    printf("%s is deleted\n",str);
    num_of_data--;
}

int main()
{
    char str[MAX];
    Element hashtable[MAX];
    init_hashtable(hashtable);
    print_hashtable(hashtable);
    for(int i=0;i<MAX;i++)
    {
        scanf("%s",str);
        insert_hash(hashtable,str);
    }
    print_hashtable(hashtable);
    while(1)
    {
        scanf("%s",str);
        if(strcmp(str,"q")==0)
        {
            exit(0);
        }
        else if (strcmp(str,"s")==0)
        {
           scanf("%s",str);
           search_key_hash(hashtable,str);
        }
        else if (strcmp(str,"d")==0)
        {
           scanf("%s",str);
           delete_hash(hashtable,str);
        }
        else if (strcmp(str,"p")==0)
        {
           print_hashtable(hashtable);
        }
        else if (strcmp(str,"i")==0)
        {
            scanf("%s", str);
            insert_hash(hashtable, str);
        }
        else
            break;
        
    }
    /*

    */

    return 0;
}
