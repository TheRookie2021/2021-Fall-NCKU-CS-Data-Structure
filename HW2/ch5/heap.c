#include<stdio.h>
#define MAX_SIZE 50

typedef struct{
    int key;
}element;

element* CreateMinHeap(int* top);
void RemoveMinHeap(element* target_heap,int *top);
void ChangePrior();
void Insert(element* target_heap,int* top);
void PrintHeap(element* target_heap,int* top);
void ElementSwap(element * arr, int a, int b);
//---------------------------main-------------------------------------
int main(){
    element* heap;
    int top;
    heap=CreateMinHeap(&top);
    for(int i=0;i<5;i++)
        Insert(heap,&top);
        
    PrintHeap(heap,&top);
    for(int i=0;i<2;i++)
        RemoveMinHeap(heap,&top);
    PrintHeap(heap,&top);
//Insert(heap,&top);Insert(heap,&top);
//PrintHeap(heap,&top);
    return 0;
}
//---------------------------main-------------------------------------
void PrintHeap(element* target_heap,int* top){
    printf("\n");
    for(int i=1;i<*top;i++){
        printf("%d ",(target_heap+i)->key);
        if(i==1)printf("\n");
        if(i==3)printf("\n");
        if(i==7)printf("\n");
        if(i==15)printf("\n");
    }
};

element* CreateMinHeap(int* top){
    static element minheap[MAX_SIZE];//must use static variable when returning pointer
    *top=1;
    return &minheap[0];
};

void Insert(element* target_heap ,int* top){
    int insert_key;
    printf("enter a num:");
    scanf("%d",&insert_key);

    int i=*top;
    (target_heap+(i))->key=insert_key;
    printf("top:%d insertion seccess\n",*top);

    int temp;
    for(;i>1;){
        if(i%2==1){//insert to the right child
            if((target_heap+i)->key<(target_heap+(i-1)/2)->key)
            {
                ElementSwap(target_heap,i,(i-1)/2);
                i=(i-1)/2;
            }else{break;}
        
        }else
        if(i%2==0){//insert to the left child
            if((target_heap+i)->key<(target_heap+i/2)->key)
            {
                ElementSwap(target_heap,i,i/2);
                i/=2;
            }else{break;}
        }
    }
    ++*top;
};

void RemoveMinHeap(element* target_heap,int *top){
    
    int temp;
    
    (target_heap+1)->key=(target_heap+*top-1)->key;
    for(int i=1;i<*top;){

        if((target_heap+i*2)->key==0){
            //left child==0( suggest right child ==0 )
            break;

        }else if((target_heap+i*2)->key!=0 &&(target_heap+i*2+1)->key==0){
            // left child !=0 and right child==0 
            ElementSwap(target_heap,i,i*2);
            i=2*i;
        }
        else if((target_heap+i*2)->key!=0 &&(target_heap+i*2+1)->key!=0){
            //right and left both !=0

            if( (target_heap+i*2)->key<(target_heap+i*2+1)->key){
                //when left child is smaller
                if((target_heap+i*2)->key < (target_heap+i)->key){
                    //and the parent is larger than left
                    //swape parent and left child
                    ElementSwap(target_heap,i,i*2);
                    i=i*2;
                }//if left child is smaller and the parent is smaller than left child, 
                else break;//do nothing

            }else if( (target_heap+i*2)->key>= (target_heap+i*2+1)->key){
                //when right child is smaller
                if((target_heap+i*2+1)->key < (target_heap+i)->key){
                    //and the parent is largert than right
                    //swape parent and right child
                    ElementSwap(target_heap,i,i*2+1);
                    i=i*2+1;
                }else break;
            }
        }
    }
    --*top;
    (target_heap+*top)->key=0;
};

void ElementSwap(element * arr, int a, int b){
    int temp;
    temp=(arr+a)->key;
    (arr+a)->key=(arr+b)->key;
    (arr+b)->key=temp;
};
