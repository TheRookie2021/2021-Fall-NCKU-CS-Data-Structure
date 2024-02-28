#include<stdio.h>
#define MAX_SIZE 100 //注意:開大一點 避免segmentation fault
typedef struct{
    int row;
    int col;
    int value;
}Matrix;

void FastTranspose(Matrix a[],Matrix b[] );//注意: 如果要避免call by ref 的麻煩 把output 的工作交給function

int main (){

    int num_row, num_col, num_value;

    scanf("%d%d%d",&num_row,&num_col,&num_value);
    Matrix arr[MAX_SIZE], trans[MAX_SIZE];//注意: 讀取順序!
    
        
    for(int i=1; i< num_value+1;i++){
        scanf("%d%d%d",&arr[i].row,&arr[i].col,&arr[i].value);//注意: 不要有空格!
    }
        arr[0].row=num_row;
        arr[0].col=num_col;
        arr[0].value=num_value;
    for(int i=0; i< num_value+1;i++)
    {
        trans[i].row=0;
        trans[i].col=0;
        trans[i].value=0;
    }
/*
6 6 8
0 0 15
0 3 22
0 5 -15
1 1 11
1 2 3
2 3 -6
4 0 91
5 1 5555
*/
   
    FastTranspose(arr,trans);
    
    return 0;
}

typedef struct{
    int rowTerm;
    int starting;
}FTterm;


void FastTranspose(Matrix sparse[], Matrix b[]){
   //[0,0] [0,1] [0,2] are starting position

    FTterm calculate[MAX_SIZE];
    int i,j, num_of_col=sparse[0].col;
    int num_of_term=sparse[0].value;
    
    b[0].row=sparse[0].col;
    b[0].col=sparse[0].row;
    b[0].value=sparse[0].value;

    if(num_of_term>0){

        for(i=0;i<num_of_col;i++)//initialize
            calculate[i].rowTerm=0;

        for(i=1;i<=num_of_term;i++)//注意: i=1!! //counting number of rows
           calculate[sparse[i].col].rowTerm ++;
        calculate[0].starting=1;//initial state caculate[0].st=0,caculate[0].row=0;

        for(i=1;i<num_of_col;i++)//注意: i=1!!!! //counting stpt of each row in spmatrix
            calculate[i].starting= calculate[i-1].starting+calculate[i-1].rowTerm;

        for(i=1;i<=num_of_term;i++){
            j=calculate[sparse[i].col].starting++;
            b[j].row=sparse[i].col;
            b[j].col=sparse[i].row;
            b[j].value=sparse[i].value;
        }
    }

    //printf("\n");
    for(int i=0; i< num_of_term+1 ;i++){
        printf("%d %d %d\n",b[i].row,b[i].col,b[i].value);
    
    }
};