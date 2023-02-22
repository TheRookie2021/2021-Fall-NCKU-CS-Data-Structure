#include<stdio.h>
#include<string.h>
typedef struct{
    char instruction[20];
    int n;
}Input;

int Fibonacci_interative(int i);

int Fibonacci_recursion(int i);



int main (){
    //input iteration time, i
    int n;
    
    //printf("give a number for # of inptut: ");
    scanf("%d ",&n);
    Input input[n];

    for(int i=0;i<n;i++){
        scanf("%s",&input[i].instruction);
        scanf("%d",&input[i].n);
    }

    /*for(int i=0;i<input;i++){
        printf("%s ",string_arr[i]);
        printf("%d\n",f[i]);
    }*/
    //output fi
    for(int i=0;i<n;i++){

         if( strcmp(input[i].instruction,"recursive"))
        {
            //printf("recursive fibo function: ");
            printf("%d\n",Fibonacci_recursion(input[i].n));
        }
        if( strcmp(input[i].instruction,"iterative"))
        {
            //printf("iterative fibo function: ");
            printf("%d\n",Fibonacci_interative(input[i].n));
        }
    }

    return 0;
}

int Fibonacci_interative(int i){
    if (i==0) return 0;
    if (i==1) return 1; 
    int f0=0,f1=1,fn=0;    
    //f2= f1 + f0
    for (int j=1;j<i;j++){
        fn=f1+f0;
        f0=f1;
        f1=fn;
    
    }
    return f1;
};

int Fibonacci_recursion(int i){
    
    if(i==0) return 0;
    if(i==1) return 1;

    return Fibonacci_recursion(i-1)+Fibonacci_recursion(i-2);

};