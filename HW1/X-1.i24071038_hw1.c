#include<stdio.h>

int Fibonacci_interative(int i);

int Fibonacci_recursion(int i);


int main (){
    //input iteration time, i
    int input;
    
    printf("give a number for fibonacci fucntion to run: ");
    scanf("%d",&input);

    //output fi
    printf("iterative fibo function: ");
    printf("%d\n",Fibonacci_interative(input));
    
    printf("recursive fibo function: ");
    printf("%d",Fibonacci_recursion(input));


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