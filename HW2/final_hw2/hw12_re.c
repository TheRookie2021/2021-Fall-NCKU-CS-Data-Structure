#include<stdio.h>
#include<stdbool.h>
#define MAX_SIZE 50


int* CreateMinHeap(int* top);
int RemoveMinHeap(int* target_heap,int *top);
void ChangePrior(int* target_heap,int*top);
void Insert(int* target_heap,int* top);
void PrintHeap(int* target_heap,int* top);
void swap(int* a, int * b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
//---------------------------main-------------------------------------
int main(){
    int* heap;
    int top;
    heap=CreateMinHeap(&top);
    for(int i=0;i<5;i++)
        Insert(heap,&top);        
    PrintHeap(heap,&top);
/*
    for(int i=0;i<3;i++)
        RemoveMinHeap(heap,&top);
    PrintHeap(heap,&top);

*/
    ChangePrior(heap,&top);
    PrintHeap(heap,&top);
    return 0;
}
//---------------------------main-------------------------------------
void PrintHeap(int* target_heap,int* top){
    printf("\n");
    for(int i=1;i<*top;i++){
        printf("%d ",*(target_heap+i));
        if(i==1)printf("\n");
        if(i==3)printf("\n");
        if(i==7)printf("\n");
        if(i==15)printf("\n");

    }
};

int* CreateMinHeap(int* top){
    static int minheap[MAX_SIZE];//must use static variable when returning pointer
    *top=1;
    return &minheap[0];
};

void Insert(int* target_heap ,int* top){
    int insert_key;
    printf("enter a num:");
    scanf("%d",&insert_key);

    int i=*top;
    *(target_heap+(i))=insert_key;
    //printf("top:%d insertion seccess\n",*top);

    int temp;
    for(;i>1;){
        if(i%2==1){//insert to the right child
            if(*(target_heap+i)<*(target_heap+(i-1)/2))
            {
                swap((target_heap+i),(target_heap+(i-1)/2));
                i=(i-1)/2;
            }else{break;}
        
        }else
        if(i%2==0){//insert to the left child
            if(*(target_heap+i)<*(target_heap+i/2))
            {
                swap((target_heap+i),(target_heap+(i)/2));
                i/=2;
            }else{break;}
        }
    }
    ++*top;
};
void Insert_private(int* target_heap ,int* top,int insert_key){
    

    int i=*top;
    *(target_heap+(i))=insert_key;
    //printf("top:%d insertion seccess\n",*top);

    int temp;
    for(;i>1;){
        if(i%2==1){//insert to the right child
            if(*(target_heap+i)<*(target_heap+(i-1)/2))
            {
                swap((target_heap+i),(target_heap+(i-1)/2));
                i=(i-1)/2;
            }else{break;}
        
        }else
        if(i%2==0){//insert to the left child
            if(*(target_heap+i)<*(target_heap+i/2))
            { 
                swap((target_heap+i),(target_heap+(i)/2));
                i/=2;
            }else{break;}
        }
    }
    ++*top;
};

int RemoveMinHeap(int* target_heap,int *top){
    
    int temp,min_result=*(target_heap+1);

    *(target_heap+1)=*(target_heap+*top-1);
    for(int i=1;i<*top;){

        if(*(target_heap+i*2)==0){
            //left child==0( suggest right child ==0 )
            break;

        }else if(*(target_heap+i*2)!=0 &&*(target_heap+i*2+1)==0){
            // left child !=0 and right child==0 
            *(target_heap+i)=*(target_heap+i*2);
            i=2*i;
        }
        else if(*(target_heap+i*2)!=0 &&*(target_heap+i*2+1)!=0){
            //right and left both !=0

            if( *(target_heap+i*2)<*(target_heap+i*2+1)){
                //when left child is smaller
                if(*(target_heap+i*2) < *(target_heap+i)){
                    //and the parent is larger than left
                    //swape parent and left child
                    
                    swap( (target_heap+i),(target_heap+i*2));
                    i=i*2;
                }//if left child is smaller and the parent is smaller than left child, 
                else break;//do nothing

            }else if( *(target_heap+i*2)>= *(target_heap+i*2+1)){
                //when right child is smaller
                if(*(target_heap+i*2+1) <*(target_heap+i)){
                    //and the parent is largert than right
                    //swape parent and right child
                    swap( (target_heap+i),(target_heap+i*2+1));
                   
                    i=i*2+1;
                }else break;
            }
        }
    }
    --*top;
    *(target_heap+*top)=0;
    return min_result;
};
int IsExisted(int* target_heap,int top,int key){
    int position=1;
    for(;position<top;position++)
        if(*(target_heap+position)==key) {
            return position;
            break;}
    return 0;
};
void ChangePrior(int* target_heap,int*top){

    int change_key, priority;
    printf("\nenter the num to change priority:");
    scanf("%d",&change_key);
    int cur=IsExisted(target_heap,*top,change_key);
    printf("position of change key:%d\n",cur);
    if(cur==0) 
    {
        printf("no such num existed\n");
        return;
    }

    printf("enter the priority to change to:");
    scanf("%d",&priority);
    int copy[MAX_SIZE];

    int arr[*top];
    int counter=*top;
    int cp_top=counter;
    for(int i=1;i<counter;i++){
        copy[i]=*(target_heap+i);
    }

    for(int i=1;i<counter;i++){
        arr[i]=RemoveMinHeap(&copy[0],&cp_top);
    }
      for(int i=1;i<counter;i++){
         printf("arr[i]=%d\n",arr[i]);
    }
    int prio_value=arr[priority];
    int prior_index;
    for(int i=1;i<counter;i++)
        if(*(target_heap+i)==prio_value){ prior_index=i;break;}

     swap( (target_heap+cur),(target_heap+prior_index));
           
};

