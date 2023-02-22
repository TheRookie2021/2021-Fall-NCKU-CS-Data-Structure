
#include<stdio.h>
#define MAX_SIZE 20
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

int main(){
    push(4,5,6);
    push(1,2,3);
    printstack();
    element a=pop();
    printstack();
    printf("%d %d %d\n",a.row,a.col,a.next_dir);
    return 0;
}