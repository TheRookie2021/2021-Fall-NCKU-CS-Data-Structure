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

void Union (element * arr,int a1, int b1);
int Find  (element * arr,int a1);
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
    element record[v];//0~ v-1
    for(int j=0;j<v;j++){
        record[j].key=-1;
        record[j].height=0;
    }

    //DFS
    int i=0;
    int top=0, counter=0,cur=0;
    status[top]=s;//set start pt
    push(s);
    
    for(stack_top;stack_top!=-1 ||top!=v-1;){
        if(counter==v){
            if(stack_top==-1)break;
            i=pop();
        }
        else i=status[cur++];

        counter=0;
        for(int j=0;j<v;j++){
            ++counter;
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


//union 
void Union (element * arr,int a1, int b1){
    //new node exist
    if((arr+a1)->height==0&& (arr+b1)->height==0){
        (arr+a1)->key=-1;
        (arr+b1)->key=a1;
        (arr+b1)->height=1;
        (arr+a1)->height=(arr+b1)->height+1;
        return;

    }else if((arr+a1)->height==0){
        (arr+a1)->key=b1;
        (arr+a1)->height=1;
        return;
    }else if((arr+b1)->height==0){
        (arr+b1)->key=a1;
        (arr+b1)->height=1;
        return;
    }

    //two exist tree
    if((arr+a1)->height>=(arr+b1)->height){
        (arr+b1)->key=a1;
        return;
    }else{
        (arr+a1)->key=b1;
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
