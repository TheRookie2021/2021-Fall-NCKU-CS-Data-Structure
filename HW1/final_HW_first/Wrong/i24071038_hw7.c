#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 100
typedef struct{
    float coef;
    int expon;
    struct Node* link;
}Node;
typedef struct{
    char operation[MAX_SIZE];
    char expression[MAX_SIZE];
    int num_term;
    int term_arr[MAX_SIZE];
    float x;
    //-----------------------
    char operandA[MAX_SIZE]; 
    char operandB[MAX_SIZE]; 
    char operandC[MAX_SIZE]; 

}Input;
typedef struct{
    char name;
    struct Node* expression;
}Express;


Node* pread(int num, int arr[]){
     Node* head;
    Node* cur=NULL;
    Node* newnode;
    /*
    printf("OK\n");
    for(int i=0;i<num*2;i++)
        printf("arr %d\n",arr[i]);
    */
    
    for(int i=0;i<num*2-1;){
        newnode=malloc(sizeof(Node));
        newnode->coef=arr[i++];
        newnode->expon=arr[i++];
        newnode->link=NULL;

        if(cur==NULL){
            head=newnode;
            cur=head;
        }else {
            cur->link=newnode;
            cur=cur->link;
        }
        //printf("%2f %d\n",cur->coef,cur->expon);
    }
    
    printf("OK\n");

    return head;
}

void pwrite(Node * expression ){
    Node* cur;
    cur=expression;
    //printf("%2f %d",cur->coef,cur->expon);

    int counter=0;
    while (cur!=NULL){
        if(counter==0)
            printf("%.0fx^%d",cur->coef,cur->expon);
        else if(cur->coef<0) printf("%.0fx^%d",cur->coef,cur->expon);
        else if(cur->coef>0) printf("+%.0fx^%d",cur->coef,cur->expon);
        else if(cur->expon==0){return;}
        counter++;
        cur=cur->link;
    }
    printf("\n");
/*
*/
}
Node* padd(Node* expA, Node* expB){
    if(expA==NULL) return expB;
    Node* curA=expA;
    Node* curB=expB;
    Node* result=NULL;
    Node* cur_result=NULL;
    Node* newnode;
    while(curA!=NULL || curB !=NULL)
    {
        newnode=malloc(sizeof(Node));
            
        if(curA==NULL){
                newnode->coef=curB->coef;
                newnode->expon=curB->expon;
                newnode->link=NULL;
                curB=curB->link;
            }
        else if(curB==NULL){
                newnode->coef=curA->coef;
                newnode->expon=curA->expon;
                newnode->link=NULL;
                curA=curA->link;

            }
        else{

                if(curA->expon==curB->expon){
                    newnode->coef=curA->coef+curB->coef;
                    newnode->expon=curB->expon;
                    newnode->link=NULL;
                    curA=curA->link;
                    curB=curB->link;
                }
                else if(curA->expon>curB->expon){
                    newnode->coef=curA->coef;
                    newnode->expon=curA->expon;
                    newnode->link=NULL;
                    curA=curA->link;
                }
                else if(curA->expon<curB->expon){
                    newnode->coef=curB->coef;
                    newnode->expon=curB->expon;
                    newnode->link=NULL;
                    curB=curB->link;
                }
            }//AB null or not 

        if(cur_result==NULL){
                result=newnode;
                cur_result=result;
        }else {
                cur_result->link=newnode;
                cur_result=cur_result->link;
        }  
    }//while
     printf("added\n");
    return result;
}
Node* psub(Node* expA, Node* expB){
    Node* curA=expA;
    Node* curB=expB;
    Node* result=NULL;
    Node* cur_result=NULL;
    Node* newnode;
    while(curA!=NULL || curB !=NULL)
    {
        newnode=malloc(sizeof(Node));
            
        if(curA==NULL){
                newnode->coef= -curB->coef;
                newnode->expon=curB->expon;
                newnode->link=NULL;
                curB=curB->link;
            }
        else if(curB==NULL){
                newnode->coef=curA->coef;
                newnode->expon=curA->expon;
                newnode->link=NULL;
                curA=curA->link;

            }
        else{

                if(curA->expon==curB->expon){
                    newnode->coef=curA->coef-curB->coef;
                    newnode->expon=curB->expon;
                    newnode->link=NULL;
                    curA=curA->link;
                    curB=curB->link;
                }
                else if(curA->expon>curB->expon){
                    newnode->coef=curA->coef;
                    newnode->expon=curA->expon;
                    newnode->link=NULL;
                    curA=curA->link;
                }
                else if(curA->expon<curB->expon){
                    newnode->coef= -curB->coef;
                    newnode->expon=curB->expon;
                    newnode->link=NULL;
                    curB=curB->link;
                }
        }//AB null or not 

        if(cur_result==NULL){
                result=newnode;
                cur_result=result;
        }else {
                cur_result->link=newnode;
                cur_result=cur_result->link;
        }  
    }//while
     printf("subed\n");
    return result;
}
Node* single_multi(Node* expA, Node * exp_single){
    Node* curA=expA;
    Node* result=NULL;
    Node* cur_result=NULL;
    Node* newnode;
        
    while(curA!=NULL){

        newnode=malloc(sizeof(Node));
        newnode->coef=curA->coef * exp_single->coef;
        newnode->expon=curA->expon + exp_single->expon;

        if(cur_result==NULL){
            result=newnode;
            cur_result=result;
        }else {
            cur_result->link=newnode;
            cur_result=cur_result->link;
        }

        curA=curA->link;
    }
    //pwrite(result);
    return result;
}

Node* pmult(Node* expA, Node* expB){
    Node* curA=expA;
    Node* curB=expB;
    Node* result=NULL;
    Node* cur_result=NULL;

    //multi part 1: all of A and one of B
    Node* temp_result=NULL;

    while (curB!=NULL){
        temp_result=single_multi(curA,curB);
        //pwrite(temp_result);
        result=padd(result,temp_result);
        //pwrite(result);
        curB=curB->link;
    }
    
    printf("mult\n");
    return result;
}
float eval(float x, Node* expression){
    float result=0;
    float tempx=1;
    Node* cur=expression;
    //pwrite(cur);
    while(cur!=NULL){
        for(int i=0;i<cur->expon;i++){
            tempx=tempx* x;      
        }
        tempx = tempx * cur->coef;
        result+=tempx;
        printf("%f\n",tempx);
        tempx=1;
      
        cur=cur->link;
    }
    printf("%.2f\n",result);
    
    return result;
}
Node* perase(Node* expression){
    free (expression);
    printf("erased\n");
    return NULL;
}

int main(){
    int n;
    scanf("%d",&n);
    Input input[n];
   
    for(int i=0;i<n;i++){
        
        scanf("%s", &input[i].operation);
        
        if(strcmp(input[i].operation,"pread")==0){
            scanf("%s",&input[i].expression);
            scanf("%d",&input[i].num_term);
            for(int j=0;j<2*input[i].num_term;j++){
                scanf("%d",&input[i].term_arr[j]);
            }
        }else if(strcmp(input[i].operation,"pwrite")==0){
            scanf("%s",&input[i].expression);
        
        }else if(strcmp(input[i].operation,"padd")==0){
            scanf("%s",&input[i].operandC);
            scanf("%s",&input[i].operandA);
            scanf("%s",&input[i].operandB);
            
        }else if(strcmp(input[i].operation,"psub")==0){
            scanf("%s",&input[i].operandC);
            scanf("%s",&input[i].operandA);
            scanf("%s",&input[i].operandB);

        }else if(strcmp(input[i].operation,"pmult")==0){
            scanf("%s",&input[i].operandC);
            scanf("%s",&input[i].operandA);
            scanf("%s",&input[i].operandB);

        }else if(strcmp(input[i].operation,"eval")==0){
            scanf("%s",&input[i].expression);
            scanf("%f",&input[i].x);

        }else if(strcmp(input[i].operation,"perase")==0){
            scanf("%s",&input[i].expression);
        }
    }
      //printf("OK\n");
    Node* A=NULL;
    Node* B=NULL;
    Node* result=NULL;
    for(int i=0;i<n;i++){

        if(strcmp(input[i].operation,"pread")==0){
            if(A==NULL) A=pread(input[i].num_term,input[i].term_arr);
            else        B=pread(input[i].num_term,input[i].term_arr);
        
        }else if(strcmp(input[i].operation,"pwrite")==0){
            
    //printf("OK\n");
            if(strcmp(input[i].expression,"expressionA")==0){
                pwrite(A);     
            }else if(strcmp(input[i].expression,"expressionB")==0){
                pwrite(B);
            }else if(strcmp(input[i].expression,"resultC")==0){
                pwrite(result);
            }
        
        }else if(strcmp(input[i].operation,"padd")==0){
            result=padd(A,B);
            
        }else if(strcmp(input[i].operation,"psub")==0){
            result=psub(A,B);

        }else if(strcmp(input[i].operation,"pmult")==0){
            result=pmult(A,B);

        }else if(strcmp(input[i].operation,"eval")==0){
            float r=eval(input[i].x,result);
            printf("%.2f",r);
        }else if(strcmp(input[i].operation,"perase")==0){
            perase(result);
        }
    }

    /*
    */
    return 0;
}

