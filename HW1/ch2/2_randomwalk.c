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

void RandomWalk_A(int row, int col);
void RandomWalk_B(int plan);

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
    /*check input/*
    for(int i=0;i<MAX_LINE;i++){
        printf("%c ",walk[i].instruction);
        
        if(walk[i].instruction=='q')
            break;
        if(walk[i].instruction=='a')
            printf( "%d %d ",walk[i].row,walk[i].col);
        if(walk[i].instruction=='b')
            printf( "%d ",walk[i].plan);
        
    } */
    

    for(int i=0;i<MAX_LINE;i++){
        if(walk[i].instruction=='q')
            i=MAX_LINE;           
        if(walk[i].instruction=='a')
            RandomWalk_A(walk[i].row,walk[i].col);
        if(walk[i].instruction=='b')
            RandomWalk_B(walk[i].plan);
    }
    
        return 0;
}

void RandomWalk_A(int row, int col){
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

            // (a). handle all values of 0<n<40, 0<m<20 and , ;
            /* 設定亂數種子 */
    srand( time(NULL) );
    int table_counts= row*col;//for quit condition
            
    for(int j=0;j<row;j++)//initialize
        for(int k=0;k<col;k++)
            map[j][k]=0;

    int row_bugstart=0,col_bugstart=0;
    
            
    //prepare
    //--------------------------------------------------------------------
    //simulation
    for(int steps=0;steps<MAX_STEP;steps++){
                // 產生亂數 
        int rnd_next = rand()%8;

                //邊界判斷
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

            if(map[row_bugstart][col_bugstart]==0)
                --table_counts;
            ++map[row_bugstart][col_bugstart];//count the steps 
                
            //quit condition
            if( table_counts==0){
               //print out
                printf("\n%d\n",steps+1);
                for(int j=0;j<row;j++){
                    for(int k=0;k<col;k++)
                        printf("%d ",map[j][k]);
                    printf("\n");
                    } 
                break;// breakkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk!
            }
            }//for loop: ;walk[i].steps<MAX_STEP;walk[i].steps++



};


void RandomWalk_B(int plan){
    Direction next[8];
    next[0].row_direction=-1; next[0].col_direction=0;// 上
    next[1].row_direction=1; next[1].col_direction=0;// 下
    next[2].row_direction=0; next[2].col_direction=-1;// 左
    next[3].row_direction=0; next[3].col_direction=1;// 右

    next[4].row_direction=-1; next[4].col_direction=-1;// 左上
    next[5].row_direction=-1; next[5].col_direction=1;// 右上
    next[6].row_direction=1; next[6].col_direction=-1;// 左下
    next[7].row_direction=1; next[7].col_direction=1;// 右下
    /*
    (b). perform the experiment for :
        (1) n=15, m=15, starting point (10, 10), and 
        (2) n=39, m=19, starting point(1,1) .
    */
    if(plan==1){
        int row=15,col=15;
        int map[row][col];
        for(int j=0;j<row;j++)//initialize
        for(int k=0;k<col;k++)
            map[j][k]=0;
        int table_counts=row*col;
        int row_bugstart=10,col_bugstart=10;
        /* 設定亂數種子 */
        srand( time(NULL) );
    //prepare
    //--------------------------------------------------------------------
    //simulation
    for(int steps=0;steps<MAX_STEP;steps++){
        // 產生亂數 
        int rnd_next = rand()%8;

                //邊界判斷
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

            if(map[row_bugstart][col_bugstart]==0)
                --table_counts;
            ++map[row_bugstart][col_bugstart];//count the steps 
                
            //quit condition
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

    }
    else if (plan==2){
        int row=39,col=19;
        int map[row][col];
        for(int j=0;j<row;j++)//initialize
        for(int k=0;k<col;k++)
            map[j][k]=0;
        int table_counts=row*col;
        int row_bugstart=1,col_bugstart=1;
        /* 設定亂數種子 */
        srand( time(NULL) );
         //prepare
    //--------------------------------------------------------------------
    //simulation
    for(int steps=0;steps<MAX_STEP;steps++){
                // 產生亂數 
        int rnd_next = rand()%8;

                //邊界判斷
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

            if(map[row_bugstart][col_bugstart]==0)
                --table_counts;
            ++map[row_bugstart][col_bugstart];//count the steps 
                
            //quit condition
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

    

    }
}