#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */
#define MAX_LINE 10
#define MAX_STEP 50000
/*A random walk to any one of the eight neighbor squares is simulated 
by generating a random value for k , 0<=k<8.
When every square has been entered at least once, the experiment is complete
*/
void RandomWalk();

int main(){
    
    RandomWalk();
    return 0;
}

typedef struct{
    char instruction;
    int row;
    int col;
    int plan;
    int steps;
}Input;//for scanning input
typedef struct{
    int row_direction;
    int col_direction;
}Direction;//for walking directions


void RandomWalk(){
/*
(a). handle all values of 0<n<40, 0<m<20 and , ;
(b). perform the experiment for :
    (1) n=15, m=15, starting point (10, 10), and 
    (2) n=39, m=19, starting point(1,1) .
(c). have an iteration limit, that is, a maximum 
number of squares that the bug may enter during
the experiment. 
This ensures that your program will terminate. 
A maximum of is 50,000 appropriate for this exercise.
*/
//A line consists of one character 'q'. 

Input walk[MAX_LINE];
Direction next[8];

//initialize next;
next[0].row_direction=-1; next[0].col_direction=0;// 上
next[1].row_direction=1; next[1].col_direction=0;// 下
next[2].row_direction=0; next[2].col_direction=-1;// 左
next[3].row_direction=0; next[3].col_direction=1;// 右

next[4].row_direction=-1; next[4].col_direction=-1;// 左上
next[5].row_direction=-1; next[5].col_direction=1;// 右上
next[6].row_direction=1; next[6].col_direction=-1;// 左下
next[7].row_direction=1; next[7].col_direction=1;// 右下


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

int map[40][20]={0};
for(int i=0;i<MAX_LINE;i++){
    
    switch( walk[i].instruction ){
        
        case 'a':
            // (a). handle all values of 0<n<40, 0<m<20 and , ;
            /* 設定亂數種子 */
            srand( time(NULL) );
            int table_counts=walk[i].row*walk[i].col;//for quit condition
            
            for(int j=0;j<walk[i].row;j++)//initialize
                for(int k=0;k<walk[i].col;k++)
                    map[j][k]=0;

            int row_bugstart=rand()%walk[i].row,col_bugstart=rand()%walk[i].col;
            walk[i].steps=0;
            
            //prepare
            //--------------------------------------------------------------------
            //simulation

            for(;walk[i].steps<MAX_STEP;walk[i].steps++){
                // 產生亂數 
                int rnd_next = rand()%8;

                //邊界判斷
                if( row_bugstart+next[rnd_next].row_direction <0 ||
                    row_bugstart+next[rnd_next].row_direction >walk[i].row ||
                    col_bugstart+next[rnd_next].col_direction <0 ||
                    col_bugstart+next[rnd_next].col_direction <walk[i].col 
                ){
                    --walk[i].steps;
                    continue;
                }

                //walking
                row_bugstart+=next[rnd_next].row_direction;
                col_bugstart+=next[rnd_next].col_direction;
                if(map[row_bugstart][col_bugstart]==0)
                    --table_counts;
                map[row_bugstart][col_bugstart]++;//count the steps 
                
            //quit condition
            if( table_counts==0){
               //print out
                printf("\n%d\n",walk[i].steps);
                for(int j=0;j<walk[i].row;j++){
                    for(int k=0;k<walk[i].col;k++)
                        printf("%d ",map[j][k]);
                    printf("\n");
                    } 
                }
            }//for loop: ;walk[i].steps<MAX_STEP;walk[i].steps++

            
            break;
        case 'b':
            //(b). perform the experiment for :
                // (1) n=15, m=15, starting point (10, 10), and 
                // (2) n=39, m=19, starting point(1,1) .
            if(walk[i].plan==1){
                walk[i].row=15;
                walk[i].col=15;
                int row_bugstart=10,col_bugstart=10;
            //prepare b1
            //--------------------------------------------------------------------
            //simulation
            
                for(walk[i].steps=0;walk[i].steps<MAX_STEP;walk[i].steps++){
                    // 產生亂數 
                    int rnd_next = rand()%8;

                    //邊界判斷
                    if( row_bugstart+next[rnd_next].row_direction <0 ||
                        row_bugstart+next[rnd_next].row_direction >walk[i].row ||
                        col_bugstart+next[rnd_next].col_direction <0 ||
                        col_bugstart+next[rnd_next].col_direction <walk[i].col 
                    ){
                        --walk[i].steps;
                        continue;
                    }

                    //walking
                    row_bugstart+=next[rnd_next].row_direction;
                    col_bugstart+=next[rnd_next].col_direction;
                    if(map[row_bugstart][col_bugstart]==0)
                        --table_counts;
                    map[row_bugstart][col_bugstart]++;//count the steps 
                    
                //quit condition
                if( table_counts==0){
                    printf("%d\n",walk[i].steps);
                    for(int j=0;j<walk[i].row;j++){
                        for(int k=0;k<walk[i].col;k++)
                            printf("%d ",map[j][k]);
                        printf("\n");
                        }
                    }
                }//for loop: ;walk[i].steps<MAX_STEP;walk[i].steps++

                //print out
                
            }//if b1
            //********************************************************************
            else if(walk[i].plan==2){
                walk[i].row=39;
                walk[i].col=19;
                int row_bugstart=1,col_bugstart=1;
            //prepare b2
            //--------------------------------------------------------------------
            //simulation
                for(walk[i].steps=0;walk[i].steps<MAX_STEP;walk[i].steps++){
                    // 產生亂數 
                    int rnd_next = rand()%8;

                    //邊界判斷
                    if( row_bugstart+next[rnd_next].row_direction <0 ||
                        row_bugstart+next[rnd_next].row_direction >walk[i].row ||
                        col_bugstart+next[rnd_next].col_direction <0 ||
                        col_bugstart+next[rnd_next].col_direction <walk[i].col 
                    ){
                        --walk[i].steps;
                        continue;
                    }

                    //walking
                    row_bugstart+=next[rnd_next].row_direction;
                    col_bugstart+=next[rnd_next].col_direction;
                    if(map[row_bugstart][col_bugstart]==0)
                        --table_counts;
                    map[row_bugstart][col_bugstart]++;//count the steps 
                    
                //quit condition
                if( table_counts==0){
                    printf("%d\n",walk[i].steps);
                    for(int j=0;j<walk[i].row;j++){
                        for(int k=0;k<walk[i].col;k++)
                            printf("%d ",map[j][k]);
                        printf("\n");
                        }
                }//for loop: ;walk[i].steps<MAX_STEP;walk[i].steps++

                //print out
                

            }//if b2

            break;
        case 'q':
            i=MAX_LINE;
            break;
        default:
            break;
    }//switch: {walk[i].instruction}

/*
print
    (1) total number of legal moves that the cockroach makes and 
    (2) the final count array
*/


}//for loop:{switch}

}
}