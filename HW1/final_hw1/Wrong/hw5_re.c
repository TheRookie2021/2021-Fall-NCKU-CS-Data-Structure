#include<stdio.h>
#include<stdbool.h>
#define MAX_SIZE 50

int map[MAX_SIZE][MAX_SIZE];

typedef struct{
    int next_row;
    int next_col;
}Offset;

typedef struct{
    int row;
    int col;
    int dir;
}Stack;

Offset direction[8];
Stack stack[MAX_SIZE*MAX_SIZE];
int top=-1;

void push(int row,int col,int dir){
    ++top;
    stack[top].row=row;
    stack[top].col=col;
    stack[top].dir=dir;
}
void pop(int * row,int* col,int* dir){
    *row=stack[top].row;
    *col=stack[top].col;
    *dir=stack[top].dir;
    --top;
}

void printstack(){
    for(int i=0;i<=top;i++){
        printf("%d %d\n",stack[i].row-1,stack[i].col-1);
    }
}
void initialize_dir(){
    
    direction[0].next_row=-1;//LU
    direction[0].next_col=-1;
    
    direction[1].next_row=-1;//U
    direction[1].next_col=0;
    
    direction[2].next_row=-1;//RU
    direction[2].next_col=1;
    
    direction[3].next_row=0;//L
    direction[3].next_col=-1;
    
    direction[4].next_row=0;//R
    direction[4].next_col=1;
    
    direction[5].next_row=1;//LD
    direction[5].next_col=-1;
    
    direction[6].next_row=1;//D
    direction[6].next_col=0;
    
    direction[7].next_row=1;//RD
    direction[7].next_col=1;
    
}

void SolveMaze(int n,int m){
    int enlargeMap[n+2][m+2];
    int mark[n+2][m+2];

    for(int i=0;i<n+2;i++){
        for(int j=0;j<m+2;j++){
            mark[i][j]=0;
            if(i==0 || i==n+1 ||j==0 ||j==m+1){
                enlargeMap[i][j]=1;
            }else{
                enlargeMap[i][j]=map[i-1][j-1];

            }
        }
    }//enlarge map 
/*
    for(int i=0;i<n+2;i++){
        for(int j=0;j<m+2;j++){
        printf("%d ",map[i][j]);        
        }
        printf("\n");
    }
*/  push(1,1,0);
    push(1,1,0);//start at (0,0), next dir will be direction[0]=LR
    int x_cur=1,y_cur=1;
    int x_next=0, y_next=0;
    int dir=0;
    bool found=false;
    mark[1][1]=-1;

    while(top!=-1){

        pop(&x_cur,&y_cur,&dir);

        while(dir<8 ){
        //printf("%d %d %d\n",x_cur,y_cur,dir);

            x_next=x_cur+direction[dir].next_row;
            y_next=y_cur+direction[dir].next_col;

            if(x_next==n+1 && y_next==m+1) {//下一步是終點
                push(x_cur,y_cur,dir);//record the cur position, and direction to next step 
                printf("Exit!");
                found=true;
                break;// find the ans, print stack
            }
            if(enlargeMap[x_next][y_next]==0 && mark[x_next][y_next]==0){//下一步可以走

                push(x_cur,y_cur,dir);//record the cur position, and direction to next step 
                x_cur=x_next;
                y_cur=y_next;
                mark[x_next][y_next]=3;//標記走過的
                
                dir=0;
            }else {//下一步不能走  
                mark[x_next][y_next]=3;//標記不能走的            
                dir++;//換方向
            }
        }
        if(found==true)break;
        
    }
    /*
for(int i=0;i<n+2;i++){
        for(int j=0;j<m+2;j++){
        printf("%d ",map[i][j]);        
        }
        printf("\n");
    }
    */
    printstack();
   if(!found) printf("no ans\n");
    /*
    */

}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        for(int j=0; j<m;j++){
            scanf("%d",&map[i][j]);
        }
    }
/*
    for(int i=0;i<n;i++){
        for(int j=0; j<m;j++){
          printf("%d ",map[i][j]);        
        }
        printf("\n");
    }
*/
    initialize_dir();
    SolveMaze(n,m);
    return 0;
}

