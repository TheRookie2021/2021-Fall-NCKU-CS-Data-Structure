#include <stdio.h>
#include<stdlib.h>
//print out the sequence of  moves

void HanoiTower(int num_of_disk, char A,char B,char C,int* moves );

int main(){
    int num;
    //printf("the number of disk: ");
    scanf("%d",&num);

    char a='1';
    char b='2';
    char c='3';    
    int* moves=malloc(sizeof(int*));
    *moves= 0;
    

    //printf("Moving order of Hanoi Tower : \n");
    HanoiTower(num,a,b,c,moves);

    //printf("We move the disk in 2^%d-1= %d times.",num,*moves);
    return 0;
}
void HanoiTower(int num_of_disk,char A,char B,char C,int *moves){
    ++*moves;
    //print out the seq of moves
    if(num_of_disk==1){
        //printf("Move disk on top # %d from %c to %c \n",num_of_disk,A,C);
        printf("%d %c %c\n",num_of_disk,A,C);
    }else{

    HanoiTower(num_of_disk-1,A,C,B,moves);
    //printf("Move disk on top # %d from %c to %c \n",num_of_disk,A,C);
    printf("%d %c %c\n",num_of_disk,A,C);
    HanoiTower(num_of_disk-1,B,A,C,moves);
    }
};


