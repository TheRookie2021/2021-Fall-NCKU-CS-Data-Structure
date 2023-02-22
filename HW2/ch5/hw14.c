#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_SIZE 20

void Weight_Union(int * arr,int a1, int b1);
void Height_Union(int * arr,int a1, int b1);
int Collapsing_Find(int * arr,int a);
int Find  (int * arr,int a1);
bool Same  (int * arr,int a1,int b1);

int main(){
    int arr_h[MAX_SIZE];
    int arr_w[MAX_SIZE];
    for(int i=0;i<MAX_SIZE;i++){
        arr_h[i]=-1;
        arr_w[i]=-1;
    }
   printf("\n--------------------Height_Union-------------------------\n");
 
    //set with height =4
    Height_Union(&arr_h[0],0,1);
    Height_Union(&arr_h[0],2,3);
    Height_Union(&arr_h[0],0,2);
    Height_Union(&arr_h[0],4,5);
    Height_Union(&arr_h[0],6,7);
    Height_Union(&arr_h[0],6,4);

    Height_Union(&arr_h[0],0,6);
/*
*/
    printf("height of root: %d\n",arr_h[Find(&arr_h[0],0)] );
    printf("array of height rule union:");
    for(int i=0;i<MAX_SIZE;i++){
        printf("%d ",arr_h[i]);
    } 
    Collapsing_Find(&arr_h[0],7);
    Collapsing_Find(&arr_h[0],5);
    printf("\nafter collapsing find (the leaf nodes), height of root did not change : %d\n"
            ,arr_h[Find(&arr_h[0],0)]                                         );
    printf("but array of height rule union change:");
    for(int i=0;i<MAX_SIZE;i++){
        printf("%d ",arr_h[i]);
    } 

    printf("\n--------------------Weight_Union-------------------------\n");
    //on the other hand, in weight rule with collapsing find
    Weight_Union(&arr_w[0],0,1);
    Weight_Union(&arr_w[0],2,3);
    Weight_Union(&arr_w[0],0,2);
    Weight_Union(&arr_w[0],4,5);
    Weight_Union(&arr_w[0],6,7);
    Weight_Union(&arr_w[0],6,4);

    Weight_Union(&arr_w[0],0,6);
    printf("weight of root: %d\n",arr_w[Find(&arr_w[0],0)] );
    printf("array of weight rule union:");
    for(int i=0;i<MAX_SIZE;i++){
        printf("%d ",arr_w[i]);
    } 
    Collapsing_Find(&arr_w[0],7);
    Collapsing_Find(&arr_w[0],5);
    printf("\nafter collapsing find (the leaf nodes), weight of root did not change : %d\n"
            ,arr_w[Find(&arr_w[0],0)]                                         );
    printf("array of weight rule union :");
    for(int i=0;i<MAX_SIZE;i++){
        printf("%d ",arr_w[i]);
    } 
    return 0;
}

void Weight_Union(int * arr,int a1, int b1){
    int root_a,root_b;
    root_a=Find(arr,a1);
    root_b=Find(arr,b1);
    if(root_a==root_b)return;
    
    if( *(arr+root_a) <= *(arr+root_b)){//if weight of tree a is larger
        //count weight
        *(arr+root_a) = *(arr+root_b)+*(arr+root_a) ;

        *(arr+root_b) =root_a;//let the right variable point to the left one

    }else if( *(arr+root_a) > *(arr+root_b)){//if weight a is smaller
        //count weight
        *(arr+root_b) = *(arr+root_a)+*(arr+root_b);
        
        *(arr+root_a)=root_b;
    }

};

void Height_Union(int * arr,int a1, int b1){
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


int Collapsing_Find(int * arr,int a){
    int temp[MAX_SIZE];
    int counter=0;
    int i,find;

    for(i=a;i>-1;counter++){
        temp[counter]=i;//record the node on the way
        find=i;
        i=*(arr+i);
    }

    for(int j=0;j<counter-1;j++){
        *(arr+temp[j])=find;//after finding the root, point them to the root
    }

    return find;
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