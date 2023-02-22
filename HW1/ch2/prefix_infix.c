/*First-line contains one string. It represent the prefix expression .
Second-line contains one string. It represent the postfix expression */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 100
void ToPrefix(char postfix[MAX_LENGTH]);
void ToPostfix(char prefix[MAX_LENGTH]);

typedef struct {
    char formula[MAX_LENGTH];
}Stack;

Stack stack[MAX_LENGTH];
int top=-1;

void push(char op[]){
    
    ++top;
    strcpy(stack[top].formula,op);
}
Stack pop(){
    if(top==-1){
        printf("empty");
        return ;
    }
    return stack[top--];
}
void printstack(){
    for(int i=0;i<=top;i++){
        printf("%s\n",stack[i].formula);
    }
}
//-----------------------------------main--------------------------------------
int main(){
    char post[MAX_LENGTH],pre[MAX_LENGTH];
    //gets(s1);
    gets(pre);
    ToPostfix(pre);
    //printstack();
   
    return 0;

}
//-----------------------------------main--------------------------------------


bool isOperator(char x)
{
    switch (x) {
    case '+':
    case '-':
    case '/':
    case '*':
    case '^':
        return true;
    }
    return false;
}



void ToPrefix(char postfix[MAX_LENGTH]){
   //to infix 
   char infix[MAX_LENGTH],operand,operator;
   
   //to prefix


puts(infix);
  

};

void ToPostfix(char prefix[MAX_LENGTH]){
    //intialize stack
    top=-1;

    //pre to infix
    int len_pre=strlen(prefix);    
    char temp[2];
    char op1[MAX_LENGTH],op2[MAX_LENGTH];
printf("len:%d\n",len_pre);

    
    char string[MAX_LENGTH];

    //scan for back of pre to front
    for( int i = len_pre-1 ;i >= 0 ; i-- ){
        
        
        temp[0]=prefix[i];
        temp[1]="\0";



        if(isOperator(prefix[i])==true){//運算子
            for(i=0;i<MAX_LENGTH;i++)
            string[i]=0;

            strcpy(op1, pop().formula);
            strcpy(op2, pop().formula);

           
           strcpy(string, "(");
           strcat(string, op1);
           
           strcat(string, temp);

           strcat(string, op2);
           strcat(string, ")");

           puts(string);
           push(string);

        }else if(isOperator(prefix[i])==false){ push(temp);}//數字

    }
//puts(prefix);

    //infix to postfix


};
  