#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */
#define MAX_LINE 100
#define MAX_STEP 50000

typedef struct{
    char instruction;
    int row;
    int col;
    int plan;

}Input;//for scanning input

typedef struct{
    int row_direction;
    int col_direction;
}Direction;//for walking directions

void RandomWalk_A(int row, int col,int startx,int starty);

int main(){

    Input walk[MAX_LINE];
    //input data
    for(int i=0;i<MAX_LINE;i++){
        scanf("%c",&walk[i].instruction);
        
        if(walk[i].instruction=='q')
            break;
        if(walk[i].instruction=='a')
            scanf( "%d%d",&walk[i].row,&walk[i].col);
        if(walk[i].instruction=='b')
            scanf( "%d",&walk[i].plan);
        
    }
    for(int i=0;i<MAX_LINE;i++){
        if(walk[i].instruction=='q')
            break;
        if(walk[i].instruction=='a')
            RandomWalk_A(walk[i].row,walk[i].col,0,0);
        if(walk[i].instruction=='b')
            if(walk[i].plan==1)
            RandomWalk_A(15,15,10,10);
            else if(walk[i].plan==2)
            RandomWalk_A(39,19,1,1);
            
    }
    
        return 0;
}

void RandomWalk_A(int row, int col,int startx,int starty){
    Direction next[8];
    next[0].row_direction=-1; next[0].col_direction=0;// 上
    next[1].row_direction=1; next[1].col_direction=0;// 下
    next[2].row_direction=0; next[2].col_direction=-1;// 左
    next[3].row_direction=0; next[3].col_direction=1;// 右

    next[4].row_direction=-1; next[4].col_direction=-1;// 左上
    next[5].row_direction=-1; next[5].col_direction=1;// 右上
    next[6].row_direction=1; next[6].col_direction=-1;// 左下
    next[7].row_direction=1; next[7].col_direction=1;// 右下

    int map[row][col];

    srand( time(NULL) );
    int table_counts= row*col;//for quit condition
            
    for(int j=0;j<row;j++)//initialize
        for(int k=0;k<col;k++)
            map[j][k]=0;

    int row_bugstart=startx,col_bugstart=starty;
    
            
    //prepare
    //--------------------------------------------------------------------
    //simulation
    for(int steps=1;steps<MAX_STEP;steps++){
                // 產生亂數 
        int rnd_next = rand()%8;

                //1.邊界判斷
                if( row_bugstart+next[rnd_next].row_direction <0 ||
                    row_bugstart+next[rnd_next].row_direction >row-1 ||
                    col_bugstart+next[rnd_next].col_direction <0 ||
                    col_bugstart+next[rnd_next].col_direction >col-1 )//operatorrrrrrrrrrrrrrrrrrrrrr!
                {
                    --steps;
                    continue;
                }


                //walking
            row_bugstart+=next[rnd_next].row_direction;
            col_bugstart+=next[rnd_next].col_direction;

            //2.判斷是否走過
            if(map[row_bugstart][col_bugstart]==0)
                --table_counts;
            ++map[row_bugstart][col_bugstart];//count the steps 
                
            //3.quit condition
            if( table_counts==0){
               //print out
                printf("\n%d\n",steps);
                for(int j=0;j<row;j++){
                    for(int k=0;k<col;k++)
                        printf("%d ",map[j][k]);
                    printf("\n");
                    } 
                break;// breakkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk!
            }
        }//for loop: ;walk[i].steps<MAX_STEP;walk[i].steps++
};

