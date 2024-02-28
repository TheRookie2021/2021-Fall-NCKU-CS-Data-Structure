/*
    1. insert x : Add an integer x into the SMMH tree.
    2. delete min : Delete the minimum element in the tree.
    3. delete max : Delete the maximum element in the tree.
    4. show : Show your tree.
    5. quit : Terminate your program.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100



int heap[MAX];
int arrayLength= MAX;
int last;
void init_heap(){
    last=1;
    for(int i=0;i<MAX;i++){
        heap[i]=0;
    }
}

void insert(int x);
int deletemin();
int deletemax();
void show();//level by level
void quit();

int main(){
    init_heap();
    char str[30];
    for(;;){
        scanf("%s",str);
        
        if(strcmp(str,"insert")==0){
            int n;
            scanf("%d",&n);
            insert(n);
        }else if(strcmp(str,"delete")==0){
        
            scanf("%s",str);
            if(strcmp(str,"min")==0){
                deletemin();
            }else if(strcmp(str,"max")==0){
                
               deletemax();
            }
            
        
        }else if(strcmp(str,"quit")==0){
            break;
        }else if(strcmp(str,"show")==0){
            show();
        }

    }
    return 0;
}

void insert(int x){
    //1, left node<= right node
    //2, leftchild of grandparent of N <= leftchild in N
    //3,  rightchild of grandparent of N <= rightchild in N
     
    int cur,done,gp,lcgp,rcgp;

    if(last==arrayLength-1){
        realloc(heap,2*arrayLength*sizeof(*heap));
        arrayLength*=2;
    }

    cur= ++last;
    if(last%2 ==1 && x<heap[last-1])
    {
        heap[last]=heap[last-1];
        cur--;
    }
    done=0;
    while(!done&& cur>=4){
        gp=cur/4;
        lcgp=2*gp;
        rcgp=lcgp+1;
        if(x<heap[lcgp])
        {
            heap[cur]=heap[lcgp];
            cur=lcgp;
        }
        else if(x>heap[rcgp])
        {
            heap[cur]=heap[rcgp];
            cur=rcgp;
        }
        else
        {
            done=1;            
        }
    }
    heap[cur]=x;
};

int deletemin(){
    
    //從Root的左子點取出最小值，形成空格E
    //檢查是否滿足: 左兄弟 ≤ 右兄弟
    //找出y = min{E的左子點, E的右兄弟的左子點}，
    //1. 若x ≤ y，則將x置入E；
    //2. 若x > y則將y置入E，E則變到y原先的位置。
    //重複此步驟直到滿足。
    
    if(last<2) return 0;
    if(last==2)return(heap[last--]);
    
    int out=heap[2];
    int x=0,cur_x=0,cur_y=0;
    x=heap[last--];
    heap[2]=x;
    cur_x=2;

    while(last>=cur_x*2)// if last>=4
    {
        //min{left child of cur_x, leftchild of sib of cur_x}
        //cur_x*2 vs. (cur_x+1)*2
        if(last>=(cur_x+1)*2)   
         cur_y=(heap[cur_x*2] < heap[(cur_x+1)*2]) ? (cur_x*2):((cur_x+1)*2);
        else cur_y=cur_x*2;

        // printf("curx:%d, heap[curx]:%d, x:%d\ncury:%d, heap[cury]:%d\n",cur_x,heap[cur_x],x,cur_y,heap[cur_y]);
        if(heap[cur_y]<=heap[cur_x])
        {//interchange
            heap[cur_x]=heap[cur_y];
            heap[cur_y]=x;
            cur_x=cur_y;
            x=heap[cur_x];
        }else
        {// check sib (left sib <= right sib)? interchange : return;

            if(cur_x%2==0){//cur x is left child, and left child is larger
                if(heap[cur_x]>heap[cur_x+1]){//interchang
                    heap[cur_x]=heap[cur_x+1];
                    heap[cur_x+1]=x;
                    ++cur_x;
                    x=heap[cur_x];
                }
            }else {//cur x is right child, and right child is smaller
                if(heap[cur_x]<heap[cur_x-1]){//interchang
                    heap[cur_x]=heap[cur_x-1];
                    heap[cur_x-1]=x;
                    --cur_x;
                    x=heap[cur_x];
                }
            }
        return out;
        }
        
    }   
    
    //last==4 -> last==3 
    if(heap[cur_x]>heap[cur_x+1]){
            //interchange sib data  
            heap[cur_x]=heap[cur_x+1];
            heap[cur_x+1]=x;

    }
    return out;
};
int deletemax(){
    if(last<2) return 0;
    if(last==2)return(heap[last--]);
    //below: if last>=3
    int out=heap[3];
    int x,cur_x,cur_y;
    cur_x=3;
    x=heap[last--];
    heap[cur_x]=x;

    //last>3
    while(last>cur_x){
        //max{rchild of cur_x, right child of cur_x's sib}
        //cur_x*2+1 vs. (cur_x-1)*2
        if(last>=(cur_x-1)*2+1)
        cur_y=(heap[cur_x*2+1]>heap[(cur_x-1)*2+1])? cur_x*2+1:(cur_x-1)*2+1;
        else cur_y=cur_x*2+1;
        if(heap[cur_y]>heap[cur_x])
        {//check child and nephew   
            heap[cur_x]=heap[cur_y];
            heap[cur_y]=x;
            cur_x=cur_y;
            x=heap[cur_x];
        }else
        {//check sib
           if(cur_x%2==0){//cur x is left child, and left child is larger
                if(heap[cur_x]>heap[cur_x+1]){//interchang
                    heap[cur_x]=heap[cur_x+1];
                    heap[cur_x+1]=x;
                    ++cur_x;
                    x=heap[cur_x];
                }
            }else {//cur x is right child, and right child is smaller
                if(heap[cur_x]<heap[cur_x-1]){//interchang
                    heap[cur_x]=heap[cur_x-1];
                    heap[cur_x-1]=x;
                    --cur_x;
                    x=heap[cur_x];
                }
            }
        return out;
        }
    }
    //last==3
     if(heap[cur_x]<heap[cur_x-1]){
            //interchange sib data  
            heap[cur_x]=heap[cur_x-1];
            heap[cur_x-1]=x;

    }

return out;
};
void show(){
    printf("NULL\n");
    int flag=2;
    int exp=1;
    for(int i =2;i<last+1;i++) {
        printf("%d ",heap[i]);
        /*
        0
        1 2  //2
        3 4 5 6 //4+2
        7 8 9 10   //8+4+2   
        */
       if(i-1==flag&& i!=last){
           printf("\n");
           exp*=2;
           flag+=exp*2;
       }
    }
        printf("\n");

};//level by level
void quit();
