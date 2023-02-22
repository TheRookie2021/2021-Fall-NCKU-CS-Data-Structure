#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 10000000

typedef struct{
    int key;//edge //for heap sort
    int v;//for union
    int s;//for union
}element;
typedef struct{
    int vertex;
}check_cycle;

element* CreateMinHeap(int* top);
element RemoveMinHeap(element* target_heap,int *top);
void ChangePrior();
void Insert(element* target_heap,int* top);
void PrintHeap(element* target_heap,int* top);
void ElementSwap(element * arr, int a, int b);
//-------------------------------------------------
void Initialize_Union(check_cycle* arr,int num_v);
void Union(check_cycle* arr,int a,int b);
int Find(check_cycle * arr, int a);
bool Same(check_cycle* arr,int a,int b);

//-------------------------------------------------
void Kruskal();
void ElementSwap(element * arr, int a, int b);


int main(){
    
   
   
    //kruskal
    Kruskal();

    return 0;
}
//----------------------main-----------------------------------------

void Kruskal(){
    int vertices,edges;//num of v and e
    //read input: sort edge by min heap
    scanf("%d%d",&vertices,&edges);
        //creat heap
    int top;
    element *heap=CreateMinHeap(&top);
        //insert element
    for(int i=0;i<edges;i++){
        Insert(heap,&top);
    }
    //`PrintHeap(heap,&top);//for debug
        //creat union
    check_cycle arr[vertices];
    Initialize_Union(&arr[0],vertices);

    //start: 1.start at mini 2. check cycle 3. merge into union and tree and count cost
    element temp;
    long int cost=0;
    int record_order_edge[vertices];//for debug
    //int record_order_s[vertices];//for debug
    //int record_order_v[vertices];//for debug
    for(int i=0;i<edges;i++){
        temp=RemoveMinHeap(heap,&top);
        if( !Same(&arr[0],temp.s,temp.v) ){//1.s,v in the same set:ignore 
                                        //2.s,v both new: union them  
                                        //3.s,v in diff set: union them
            Union(&arr[0],temp.s,temp.v);
            //record_order_s[i]=temp.s;//for debug
            //record_order_v[i]=temp.v;//for debug
            //printf("%d\n",temp.key);
            cost+=temp.key;
        }
    }
    printf("%ld\n",cost);
};
//--------------------------heap--------------------------------
void PrintHeap(element* target_heap,int* top){
    printf("\n");
    for(int i=1;i<*top;i++){
        printf("edge:%d s:%d v:%d\n",(target_heap+i)->key,(target_heap+i)->s,(target_heap+i)->v);
        
    }
};
element* CreateMinHeap(int* top){
    static element minheap[MAX_SIZE];//must use static variable when returning pointer
    *top=1;
    return &minheap[0];
};
void Insert(element* target_heap ,int* top){
    int insert_key, insert_s,insert_v;
    //printf("enter v1 v2 edge");
    scanf("%d%d%d",&insert_s,&insert_v,&insert_key);//input order: v v e_cost

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
//-------------------------union-------------------
void Initialize_Union(check_cycle* arr,int num_v){
    for(int i=0;i<num_v;i++){
        (arr+i)->vertex=-1;//not point to any set
    }
}
void Union(check_cycle* arr,int a,int b){
    if(Same(arr,a,b))return;
    else (arr+Find(arr,b))->vertex=Find(arr,a);
    //printf("%d %d\n",Find(arr,a),Find(arr,b));
};

int Find(check_cycle * arr, int a){

    int i=(arr+a)->vertex;
    if(i==-1) return a;//i==-1: root 
    else {
        int find;
        while(i!=-1){
            find=i;
            i=(arr+i)->vertex;
        }
        return find;
    }
}

bool Same(check_cycle* arr,int a,int b){
    
    if(Find(arr,a)==Find(arr,b))return true;
    else return false;
}