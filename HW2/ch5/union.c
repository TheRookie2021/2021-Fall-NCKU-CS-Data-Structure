/*
n1: number of union 
n2: size of union arr
op: num of operation to use

union a1 b1 : a1 is root(parent of b1) if a1 b1 are in same height
find a2: return the root of a2
same a3 b3: if a3 and b3 are in the same union
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_SIZE 10000

typedef struct{
    int key;
    int height;

}element;

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

void Union(element * arr,int a1, int b1);
int Find  (element * arr,int a1);
bool Same  (element * arr,int a1,int b1);


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
        element arr[size];
        for(int j=0;j<size;j++){
            arr[j].key=-1;
            arr[j].height=0;
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
                Union(  &arr[0],  Find(&arr[0],a),
                                  Find(&arr[0],b) );
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
void Union(element * arr,int root_a, int root_b){
    //new node exist
  //printf("root a:%d root b:%d\n",root_a,root_b);
//Root of each tree must record either its height or the number of elements in the tree   

    //two exist tree
    if((arr+root_a)->height>=(arr+root_b)->height){
        (arr+root_b)->key=root_a;
        (arr+root_a)->key=-1;
        if((arr+root_a)->height==(arr+root_b)->height)
            (arr+root_a)->height++;

        return;
    }else if((arr+root_a)->height < (arr+root_b)->height){
        (arr+root_a)->key=root_b;
        (arr+root_b)->key=-1;
        return;
    }
};

int Find  (element * arr,int a1){
    int i=(arr+a1)->key ;
    if(i==-1) return a1;

    while ((arr+i)->key!=-1)
    {
        i=(arr+i)->key;
    }
    return i;
    
};

bool Same  (element * arr,int a1,int b1){
    if(Find(arr,a1)==Find(arr,b1)){
        return true;
    }else return false;

};