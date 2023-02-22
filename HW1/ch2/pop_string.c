#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 50

typedef struct {
    char formula[MAX_LENGTH];
}Stack;

Stack stack[MAX_LENGTH];
int top=-1;
void push(char op[MAX_LENGTH]){
    int len_op=strlen(op);
    ++top;
    strcpy(stack[top].formula,op);
        

}
Stack pop(){
    return stack[top--];
}
void printstack(){
    for(int i=0;i<=top;i++){
        printf("%s\n",stack[i].formula);
    }
}
int main(){
    char s1[MAX_LENGTH],s2="j";
    strcpy(s1,"asdf");
    push(s1);
    printstack();
    push(s2);
    printstack();

    char temp[2]="a";
    
    
    puts(temp);
    return 0;
}