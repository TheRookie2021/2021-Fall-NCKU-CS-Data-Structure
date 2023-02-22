#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_SIZE 10000


typedef struct{
    char string[10];
    int a1,b1;
    int a2;
    int a3,b3;
}input;

typedef struct{
    int key;//1 for Find, 2 for Same
    int find;
    bool same;
}output;

void Union(int * arr,int a1, int b1);
int Find  (int * arr,int a1);
bool Same  (int * arr,int a1,int b1);


int main(){
    int n; scanf("%d",&n);//first input
    int size, num_op;
    int a,b;
    output store[MAX_SIZE];  
    int store_counter=0;

    for(int i=0;i<n;i++){ //read input
        // scan size of arr and num of operation
        scanf("%d%d",&size,&num_op);
        //creat union arr
        int arr[size];
        for(int j=0;j<size;j++){
            arr[j]=-1;//initial height=1 , represent in -1
        }

        for(int j=0;j<num_op;j++){
            //get operation name
            char string[10];
            scanf("%s",string);
            //puts(string);
    
            //switch(): union, find, same
            if      (strcmp(string,"union")==0){
                //input
                scanf("%d%d",&a,&b);
                Union(  &arr[0], a,b);
                continue;
                
            }else if(strcmp(string,"find")==0){
                //input
                scanf("%d",&a);
                store[store_counter].key=1;
                store[store_counter].find=Find(&arr[0],a) ;
                store_counter++;
                continue;

            }else if(strcmp(string,"same")==0){
                //input
                scanf("%d%d",&a,&b);
                //printf("Same:%d",Same(&arr,a,b));
                store[store_counter].key=2;
                store[store_counter].same=Same(&arr[0],a,b) ;
                store_counter++;
                continue;
            }
        }
    }//read input
            
    //output
    for(int i=0;i<store_counter;i++){

        if(store[i].key==1)
            printf("%d\n",store[i].find);
        if(store[i].key==2)
            if(store[i].same==1)
                printf("true\n");
            else  printf("false\n");
        }
    
    return 0;
}

void Union(int * arr,int a1, int b1){
    int root_a,root_b;
    root_a=Find(arr,a1);
    root_b=Find(arr,b1);
    if(root_a==root_b)return;
    
    if( *(arr+root_a) == *(arr+root_b)){//the height was store in the root
        *(arr+root_b)=root_a;//let the right variable point to the left one
        //count height
        *(arr+root_a)-=1 ;
    }else if( *(arr+root_a) > *(arr+root_b)){//if height a is lower
        *(arr+root_a)=root_b;
        //height not change
    }else if( *(arr+root_a) < *(arr+root_b)){
        *(arr+root_b)=root_a;//let the right variable point to the left one
        //height not change
    }

};
int Find  (int * arr,int a1){
    int i=*(arr+a1) ;
    if(i<0) return a1;

    while (*(arr+i)>-1)
    {
        i= *(arr+i);
    }
    return i;
};
bool Same  (int * arr,int a1,int b1){
    if(Find(arr,a1)==Find(arr,b1))return true;
    else return false;
};