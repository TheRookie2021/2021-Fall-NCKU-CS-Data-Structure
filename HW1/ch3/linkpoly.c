#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 50
typedef struct node * node; 
typedef struct {
    float coef;
    int exp;
    node *next;    
}node;

typedef struct {
    char instruction[MAX_LENGTH];
    char targetA[MAX_LENGTH];
    int coef_exp[MAX_LENGTH];
    char targetB[MAX_LENGTH];
    char resultC[MAX_LENGTH];
}Input;


node *add(float coef, int exp){
    node* newnode= (node*)malloc(sizeof(node));
    newnode->coef=coef;
    newnode->exp=exp;
    newnode->next=NULL;
    return newnode;
}
/*
pread . 
Read in a polynomial and convert it to its circular representation. 
Return a pointer to the header node of this polynomial.

pwrite . Output the polynomial using a form that clearly displays it.

padd . Compute . Do not change either or .

psub . Compute . Do not change either or .

pmult . Compute . Do not change either or .

eval . Evaluate a polynomial at some point, where is a floating point constant. 
Return the result as a floating point.

perase . Return the polynomial represented as a circular list to the available space list.
*/

void pread(int number_of_term, node * expressionA, Input coe_exp[] ){
    int coe_exp[2*number_of_term]

    for(int i=0;i<number_of_term;i+=2){
        expressionA->next=add(coe_exp[i],coe_exp[i+1]);


    }
}

int main(){
    node* head;
    //read input
    int n;
    scanf("%d",&n);
    Input input[n];

    for(int i=0;i<n;i++){
        scanf("%s",&input[i].instruction);
        if(input[i].instruction=="pread"){
            scanf("%s",&input[i].targetA);
            int temp =0;
            scanf("%d",&temp);
            for(int j=0;j<temp;j++)
                scanf("%d",&input[i].coef_exp[j]);
            
        }
        if(input[i].instruction=="pwrite"){
            scanf("%s",&input[i].targetA);
        }
        if(input[i].instruction=="padd"){
            scanf("%s",&input[i].resultC);
            scanf("%s",&input[i].targetA);
            scanf("%s",&input[i].targetB);

        }
        if(input[i].instruction=="psub"){
            scanf("%s",&input[i].resultC);
            scanf("%s",&input[i].targetA);
            scanf("%s",&input[i].targetB);
        }
        if(input[i].instruction=="pmult"){
            scanf("%s",&input[i].resultC);
            scanf("%s",&input[i].targetA);
            scanf("%s",&input[i].targetB);
        }
        if(input[i].instruction=="perase"){
            scanf("%s",&input[i].resultC);

        }
    }
    for(int i=0;i<n;i++){
        scanf("%s",&input[i].instruction);

        if(input[i].instruction=="pread"){
                     
        }
        if(input[i].instruction=="pwrite"){
            
        }
        if(input[i].instruction=="padd"){
            

        }
        if(input[i].instruction=="psub"){
            
        }
        if(input[i].instruction=="pmult"){
            
        }
        if(input[i].instruction=="perase"){
            

        }
        }

    return  0;
}