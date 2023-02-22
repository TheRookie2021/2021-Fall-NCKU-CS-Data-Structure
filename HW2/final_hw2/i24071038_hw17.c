#include<stdio.h>
#include<stdbool.h>
#define MAX_SIZE 100

typedef struct{
    int key;
    int height;

}element;//for union

typedef struct{
    int arr[MAX_SIZE][MAX_SIZE];
    int vertices;
    int startpoint;
}Input;

void Union (element * arr,int a1, int b1);
int Find  (element * arr,int a1);
bool Same  (element * arr,int a1,int b1);
void BFS(Input  input );

int main(){
    int n;
    int vertices,enterpoint;
    scanf("%d",&n);
    Input input[n];
for(int k=0;k<n;k++){
    scanf("%d%d",&vertices,&enterpoint);
    input[k].startpoint=enterpoint;
    input[k].vertices=vertices;
    for(int i=0;i<vertices;i++)
        for(int j=0;j<vertices;j++)
            scanf("%d",&input[k].arr[i][j]);
}
//------------------------read input-------------------------



//------------------------print output-------------------------
/*
for(int k=0;k<n;k++){
    enterpoint=input[k].startpoint;
    vertices=input[k].vertices;
    for(int i=0;i<vertices;i++){
        for(int j=0;j<vertices;j++)
            printf("%d ",input[k].arr[i][j]);
        printf("\n");
    }
}
*/    
    for(int i=0;i<n;i++){
        BFS(input[i]);
     printf("\n");
    }
    return 0;
}
void BFS(Input  input ){
    int v=input.vertices;
    int s=input.startpoint;
    int status[v];
    
    element record[v];//0~ v-1
    for(int j=0;j<v;j++){
        record[j].key=-1;
        record[j].height=0;
    }

    //BFS
    int i=0;
    int top=0, cur=0;
    status[cur]=s;//set start pt
    for(cur=0;cur<v ;cur++){
        i=status[cur];
        for(int j=0;j<v;j++){
            if(input.arr[i][j]==1){
                //see if visited, if not add into status and record
                if(Find(&record[0],j)==status[0]){//already visited
                    continue;
                }else{//haven't visited
                    status[++top]=j;
                    Union(&record[0],status[0],j);
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
