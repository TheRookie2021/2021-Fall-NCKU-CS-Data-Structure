#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 1000000

typedef struct{
    int key;//edge //for heap sort
    int v;//for union
    int s;//for union
}element;
typedef struct{
    int vertex;
    int weight;
}Union;

element* CreateMinHeap(int* top);
element RemoveMinHeap(element* target_heap,int *top);
void ChangePrior();
void Insert(element* target_heap,int* top);
void PrintHeap(element* target_heap,int* top);
void ElementSwap(element * arr, int a, int b);

//-------------------------------------------------


int main(){
    //read input
    int top=0;
    element* heap=CreateMinHeap(&top);

    for(int i=0;i<8;i++)
        Insert(heap,&top);
    PrintHeap(heap,&top);
    element x=RemoveMinHeap(heap,&top);
    element y=RemoveMinHeap(heap,&top);
    PrintHeap(heap,&top);
    printf("\n%d %d %d",x.key,x.s,x.v);
    printf("\n%d %d %d",y.key,y.s,y.v);
    return 0;
}
//----------------------main-----------------------------------------


void PrintHeap(element* target_heap,int* top){
    printf("\n");
    for(int i=1;i<*top;i++){
        printf("%d %d %d\n",(target_heap+i)->key,(target_heap+i)->s,(target_heap+i)->v);
        
    }
};

element* CreateMinHeap(int* top){
    static element minheap[MAX_SIZE];//must use static variable when returning pointer
    *top=1;
    return &minheap[0];
};

void Insert(element* target_heap ,int* top){
    int insert_key, insert_s,insert_v;
    scanf("%d%d%d",&insert_key,&insert_s,&insert_v);

    int i=*top;
    (target_heap+(i))->key=insert_key;
    (target_heap+(i))->s=insert_s;
    (target_heap+(i))->v=insert_v;
    
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

element RemoveMinHeap(element* target_heap,int *top){//return the root(min)
    
    int temp;
    element out=*(target_heap+1);

    (target_heap+1)->key=(target_heap+*top-1)->key;
    (target_heap+1)->s=(target_heap+*top-1)->s;
    (target_heap+1)->v=(target_heap+*top-1)->v;
    for(int i=1;i<*top;){

        if((target_heap+i*2)->key==0){
            //left child==0( suggest right child ==0 )
            break;

        }else if((target_heap+i*2)->key!=0 &&(target_heap+i*2+1)->key==0){
            // left child !=0 and right child==0 
            ElementSwap(target_heap,i,i*2);

            //(target_heap+i)->key=(target_heap+i*2)->key;
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
    return out;

};
void ElementSwap(element * arr, int a, int b){
    int temp_k,temp_v,temp_s;
    temp_k=(arr+a)->key;
    (arr+a)->key=(arr+b)->key;
    (arr+b)->key=temp_k;

    temp_v=(arr+a)->v;
    (arr+a)->v=(arr+b)->v;
    (arr+b)->v=temp_v;

    temp_s=(arr+a)->s;
    (arr+a)->s=(arr+b)->s;
    (arr+b)->s=temp_s;
};