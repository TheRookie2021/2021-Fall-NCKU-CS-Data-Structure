#include<stdio.h>
#include<stdbool.h>
#define MAX_SIZE 100

typedef struct{
    int key;
    int height;

}element;//for union

typedef struct{
    int arr[MAX_SIZE+1][MAX_SIZE+1];
    int vertices;
    int startpoint;
}Input;


void Union(int * arr,int a1, int b1);
int Find  (int * arr,int a1);
bool Same  (element * arr,int a1,int b1);
void DFS(Input  input );

int main(){
    int n;
    int vertices,enterpoint;
    scanf("%d",&n);
    Input input[n];
//------------------------read input-------------------------
for(int k=0;k<n;k++){
    scanf("%d%d",&vertices,&enterpoint);
    input[k].startpoint=enterpoint;
    input[k].vertices=vertices;
    for(int i=0;i<vertices;i++)
        for(int j=0;j<vertices;j++)
            scanf("%d",&input[k].arr[i][j]);
}

//------------------------print output-------------------------
    for(int i=0;i<n;i++){
        DFS(input[i]);
        printf("\n");
    }
/*
 */
    
   return 0;
}
int stack[MAX_SIZE];
int stack_top=-1;
void push(int num){
    stack[++stack_top]=num;
}   
int pop(){
    return stack[stack_top--];
}
void DFS(Input  input ){
    int v=input.vertices;
    int s=input.startpoint;
    int status[v];
    int arr_count[v];
    int record[v];//union 0~ v-1
    for(int j=0;j<v;j++){
        record[j]=-1;
        arr_count[j]=0;
    }

    //DFS
    int i=0;
    int top=0, counter=0,cur=0;
    status[top]=s;//set start pt
    push(s);
    
    for(stack_top;stack_top!=-1 && top!=v-1;){
        if(arr_count[i]==v){
            if(stack_top==-1)break;
            i=pop();
        }
        else i=status[cur++];

        for(int j=arr_count[i];j<v;j++){
            ++arr_count[i];
            if(input.arr[i][j]==1){
                //see if visited, if not add into status and record
                            //and go change the cur spot
                if(Find(&record[0],j)==Find(&record[0],status[0])){//already visited
                    continue;
                }else{//haven't visited
                    status[++top]=j; //record the node
                    push(j);
                    Union(&record[0],status[0],j);
                    break;//leave the loop and go to the node
                }
            }
        }
    }
    //printf
    
    for(int k=0;k<v;k++){
        printf("%d ",status[k]);
    }

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