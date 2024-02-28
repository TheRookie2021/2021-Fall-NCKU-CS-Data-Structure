#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#define MAX_SIZE 50

const int M = 3;
const int N = 5;

typedef struct{
    int row_direction;
    int col_direction;
}Direction;//for walking directions

typedef struct 
{
    int row;
    int col;
    int next_dir;
}element;

element stack[MAX_SIZE];
int top=-1;

void push(int row,int col,int next_dir)
{
   ++top;
   stack[top].row=row;
   stack[top].col=col;
   stack[top].next_dir=next_dir;

}

element pop()
{
   return stack[top--];
}

void printstack(){  
    for(int i=0;i<=top;i++){
        printf("%d %d\n",stack[i].row,stack[i].col);
    }
}

void MazeStack(int map[M][N], int n,int m);


int main(){
    int row,col;
    scanf("%d%d",&row,&col);
    int map[row][col];
    
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++)
            scanf("%d",&map[i][j]);
    }
   
    /*
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++)
         printf("%d ",map[i][j]);
        printf("\n");

    }    */

    MazeStack(map ,row, col);
    
    printstack();
    
    return 0;

}

  
void MazeStack(int map[M][N],int n, int m){

    Direction next[8];
    //initialize next;
    next[0].row_direction=-1; next[0].col_direction=0;// 上
    next[1].row_direction=-1; next[1].col_direction=-1;// 左上
    next[2].row_direction=-1; next[2].col_direction=1;// 右上
    next[3].row_direction=0; next[3].col_direction=-1;// 左

    next[4].row_direction=0; next[4].col_direction=1;// 右
    next[5].row_direction=1; next[5].col_direction=0;// 下
    next[6].row_direction=1; next[6].col_direction=-1;// 左下
    next[7].row_direction=1; next[7].col_direction=1;// 右下
 /* 
for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
         printf("%d ",map[i][j]);
        printf("\n");

    }  
*/
    //initialize stack 0
    push(0,0,8);
    top=0;
    int mark[n][m];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        mark[i][j]=0;
    mark[0][0]=1;
  
    bool found=false;
    element position;
//printf("top: %d \n",top);
    while(top>-1 && !found){

        // 走回頭路
        //printstack();
        position=pop();
        
        //printstack();
        int temp_row = position.row;
        int temp_col = position.col;
        int temp_dir = position.next_dir;
//printf("top: %d \n",top);
        
        // 嘗試每個方向
        while(temp_dir-- >0)
        {
            // 下一步的位置
            int next_row = temp_row + next[temp_dir].row_direction;
            int next_col = temp_col + next[temp_dir].col_direction; 
//printf("temp_dir: %d \n",temp_dir);         

/*
printf("temp_row: %d \n",temp_row);            
printf("temp_col: %d \n",temp_col);  
printf("next_row: %d \n",next_row);            
printf("next_col: %d \n",next_col);            
*/
            //邊界判斷
            if( next_row>=0 && next_row<n&&
                next_col>=0 && next_col<m  )
            {//{邊界判斷
                // 下一步可以通行
                if(mark[next_row][next_col]==0)//下一步沒走過
                { 
                    if( (next_row==n-1) && (next_col==m-1)){// 沒走過 是終點
                        
                        push(next_row,next_col,0);
                        printf("0 0\n");
                        found = true;
                        return;
                        } 
                    else             
                    if( map[next_row][next_col] ==0)//沒走過 不是終點 有路  
                    {           
                        // 把這步塞進堆疊

                        // 移動到下一步
                        temp_row = next_row;
                        temp_col = next_col;
                        mark[temp_row][temp_col] = 1;
                        push(temp_row,temp_col,temp_dir);//printstack();
                        temp_dir=8;

                    }//else temp_dir--;//沒走過 不是終點 沒路 >換方向
   
                }
            
            }//邊界判斷}
            //else temp_dir--;//超出邊界 換方向
  
        }//完全沒路 離開 while loop
    }        if (found==false)
            printf("no answer\n");

};